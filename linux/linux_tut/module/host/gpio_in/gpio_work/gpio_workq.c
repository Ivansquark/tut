#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>

#define DEVICE_NAME "button_driver"
#define CLASS_NAME "button"

// Number of GPIO buttons
#define NUM_GPIO_BUTTONS 5

// GPIOs for the buttons (EMIO)
static int gpio_pins[NUM_GPIO_BUTTONS] = {54, 55, 56, 57, 58};
static int irq_numbers[NUM_GPIO_BUTTONS]; // IRQ numbers for each GPIO
static pid_t user_pid = 0;                // Process PID to send signals

// Spinlock and workqueue
static spinlock_t irq_spinlock;
static struct workqueue_struct* button_wq;
static struct work_struct button_work[NUM_GPIO_BUTTONS];

// Platform Device and Driver
static struct platform_device* pdev = NULL;

// IOCTL commands
#define BUTTON_IOC_SET_PID _IOW('b', 1, pid_t)

// Sysfs attribute
static ssize_t pid_show(struct kobject* kobj, struct kobj_attribute* attr,
                        char* buf);
static ssize_t pid_store(struct kobject* kobj, struct kobj_attribute* attr,
                         const char* buf, size_t count);
static struct kobj_attribute pid_attribute =
    __ATTR(pid, 0664, pid_show, pid_store);

// Function prototypes
static irqreturn_t button_irq_handler(int irq, void* dev_id);
static void work_handler(struct work_struct* work);
static int dev_open(struct inode* inodep, struct file* filep);
static int dev_release(struct inode* inodep, struct file* filep);
static ssize_t dev_read(struct file* filep, char* buffer, size_t len,
                        loff_t* offset);
static ssize_t dev_write(struct file* filep, const char* buffer, size_t len,
                         loff_t* offset);
static long dev_ioctl(struct file* filep, unsigned int cmd, unsigned long arg);

// File operations struct
static struct file_operations fops = {
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
    .unlocked_ioctl = dev_ioctl,
};

// Interrupt handler for button GPIOs
static irqreturn_t button_irq_handler(int irq, void* dev_id) {
    unsigned long flags;
    int gpio_index = (int)(uintptr_t)dev_id;

    // Lock the spinlock to protect critical section
    spin_lock_irqsave(&irq_spinlock, flags);

    // Queue the work handler for this button GPIO
    queue_work(button_wq, &button_work[gpio_index]);

    spin_unlock_irqrestore(&irq_spinlock, flags);

    return IRQ_HANDLED;
}

// Work handler to send a signal to user-space
static void work_handler(struct work_struct* work) {
    int gpio_index = (int)(uintptr_t)work;
    if (user_pid != 0) {
        // Send signal to user-space process (SIGUSR1)
        printk(KERN_INFO "Button driver: Sending signal for button %d\n",
               gpio_index);
        kill_pid(find_vpid(user_pid), SIGUSR1, 1);
    }
}

// Device open function
static int dev_open(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "Button driver: Device opened\n");
    return 0;
}

// Device release function
static int dev_release(struct inode* inodep, struct file* filep) {
    printk(KERN_INFO "Button driver: Device closed\n");
    return 0;
}

// Device read function (dummy for now)
static ssize_t dev_read(struct file* filep, char* buffer, size_t len,
                        loff_t* offset) {
    int i;
    char msg[64] = {0};
    size_t msg_len = 0;

    // Check which button is currently pressed
    for (i = 0; i < NUM_GPIO_BUTTONS; i++) {
        if (button_state[i] == 1) {
            msg_len += snprintf(msg + msg_len, sizeof(msg) - msg_len,
                                "Button %d pressed\n", i);
        }
    }

    if (msg_len == 0) {
        snprintf(msg, sizeof(msg), "No button pressed\n");
    }

    // Copy the result to user space
    if (copy_to_user(buffer, msg, msg_len)) {
        return -EFAULT;
    }

    return msg_len;
}

// Device write function (handle PID)
static ssize_t dev_write(struct file* filep, const char* buffer, size_t len,
                         loff_t* offset) {
    char msg[64];
    if (len >= sizeof(msg)) return -EINVAL;

    if (copy_from_user(msg, buffer, len)) return -EFAULT;

    // Parse the PID from user-space write
    sscanf(msg, "%d", &user_pid);
    printk(KERN_INFO "Button driver: Received PID %d\n", user_pid);
    return len;
}

// IOCTL function to interact with the driver
static long dev_ioctl(struct file* filep, unsigned int cmd, unsigned long arg) {
    switch (cmd) {
    case BUTTON_IOC_SET_PID:
        if (copy_from_user(&user_pid, (pid_t*)arg, sizeof(pid_t)))
            return -EFAULT;
        printk(KERN_INFO "Button driver: Set user PID to %d\n", user_pid);
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

// Platform device probe function
static int button_driver_probe(struct platform_device* pdev) {
    int result, i;

    // Register the character device
    int major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Button driver failed to register a major number\n");
        return major_number;
    }

    // Create device class
    struct class* button_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(button_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(button_class);
    }

    // Create device
    struct device* button_device = device_create(
        button_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(button_device)) {
        class_destroy(button_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(button_device);
    }

    // Create sysfs directory and attribute
    if (sysfs_create_file(&button_device->kobj, &pid_attribute.attr)) {
        printk(KERN_ALERT "Failed to create sysfs file for pid\n");
        return -ENOMEM;
    }

    // Request GPIOs and set directions
    for (i = 0; i < NUM_GPIO_BUTTONS; i++) {
        if (!gpio_is_valid(gpio_pins[i])) {
            printk(KERN_ALERT "Invalid GPIO pin\n");
            return -1;
        }

        gpio_request(gpio_pins[i], "Button GPIO");
        gpio_direction_input(gpio_pins[i]);
        irq_numbers[i] = gpio_to_irq(gpio_pins[i]);

        result = request_irq(irq_numbers[i], button_irq_handler,
                             IRQF_TRIGGER_FALLING, "button_irq",
                             (void*)(uintptr_t)i);
        if (result) {
            printk(KERN_ALERT "Failed to request IRQ for GPIO%d\n",
                   gpio_pins[i]);
            return result;
        }
    }

    // Initialize spinlock and workqueue
    spin_lock_init(&irq_spinlock);
    button_wq = create_singlethread_workqueue("button_wq");
    for (i = 0; i < NUM_GPIO_BUTTONS; i++) {
        INIT_WORK(&button_work[i], work_handler);
    }

    printk(KERN_INFO "Button driver initialized successfully\n");
    return 0;
}

// Platform device remove function
static int button_driver_remove(struct platform_device* pdev) {
    int i;

    // Free IRQs and GPIOs
    for (i = 0; i < NUM_GPIO_BUTTONS; i++) {
        free_irq(irq_numbers[i], (void*)(uintptr_t)i);
        gpio_free(gpio_pins[i]);
    }

    // Clean up sysfs file and workqueue
    sysfs_remove_file(&pdev->dev.kobj, &pid_attribute.attr);
    destroy_workqueue(button_wq);
    device_destroy(button_class, MKDEV(major_number, 0));
    class_destroy(button_class);
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "Button driver unloaded successfully\n");
    return 0;
}

// Platform driver structure
static struct platform_driver button_driver = {
    .probe = button_driver_probe,
    .remove = button_driver_remove,
    .driver =
        {
            .name = "button_driver",
            .owner = THIS_MODULE,
        },
};

// Module initialization function
static int __init button_driver_init(void) {
    int result;

    result = platform_driver_register(&button_driver);
    if (result < 0) {
        printk(KERN_ALERT
               "Button driver failed to register with platform driver\n");
        return result;
    }

    printk(KERN_INFO "Button driver loaded successfully\n");
    return 0;
}

// Module exit function
static void __exit button_driver_exit(void) {
    platform_driver_unregister(&button_driver);
    printk(KERN_INFO "Button driver unloaded\n");
}

// Sysfs show and store functions for PID
static ssize_t pid_show(struct kobject* kobj, struct kobj_attribute* attr,
                        char* buf) {
    return sprintf(buf, "%d\n", user_pid);
}

static ssize_t pid_store(struct kobject* kobj, struct kobj_attribute* attr,
                         const char* buf, size_t count) {
    if (sscanf(buf, "%d", &user_pid) != 1) return -EINVAL;
    printk(KERN_INFO "Button driver: Set PID to %d via sysfs\n", user_pid);
    return count;
}

module_init(button_driver_init);
module_exit(button_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION(
    "A driver for handling GPIO button presses and signaling to userspace");
MODULE_VERSION("1.0");
