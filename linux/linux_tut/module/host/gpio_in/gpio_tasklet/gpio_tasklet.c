#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/slab.h>
// #include <linux/tasklet.h>
#include <linux/uaccess.h>

// Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("Tasklet interrupt interface");

#define DEVICE_NAME "zynq_gpio_buttons"
#define NUM_BUTTONS 5

// GPIO pin configuration
static int gpio_pins[NUM_BUTTONS] = {55, 56, 57, 58, 59};
static int irq_numbers[NUM_BUTTONS];
static int button_states[NUM_BUTTONS] = {0};

// Kernel module management
static struct class* gpio_buttons_class = NULL;
static int major_number;

// User space communication
static pid_t user_pid = -1;
static struct task_struct* user_task = NULL;

// Tasklet for deferred processing
static struct tasklet_struct button_tasklet;

// Tasklet handler
static void button_tasklet_handler(unsigned long data) {
    int i;

    // Read button states
    for (i = 0; i < NUM_BUTTONS; i++) {
        button_states[i] = gpio_get_value(gpio_pins[i]);
    }

    // Send signal to user space
    if (user_pid > 0 && user_task) {
        struct siginfo info;

        memset(&info, 0, sizeof(struct siginfo));
        info.si_signo = SIGUSR1;
        info.si_code = SI_USER;
        info.si_pid = user_pid;

        send_sig_info(SIGUSR1, (struct kernel_siginfo*)&info, user_task);
    }
}

// Interrupt handler
static irqreturn_t gpio_irq_handler(int irq, void* dev_id) {
    // Schedule tasklet for deferred processing
    tasklet_schedule(&button_tasklet);
    return IRQ_HANDLED;
}

// File Operations
static int device_open(struct inode* inodep, struct file* filep) {
    return 0; // No special action needed
}

static int device_release(struct inode* inodep, struct file* filep) {
    return 0; // No special action needed
}

static ssize_t device_read(struct file* filep, char __user* buffer, size_t len,
                           loff_t* offset) {
    if (len < sizeof(button_states)) {
        return -EINVAL;
    }

    if (copy_to_user(buffer, button_states, sizeof(button_states))) {
        return -EFAULT;
    }

    return sizeof(button_states);
}

static long device_ioctl(struct file* file, unsigned int cmd,
                         unsigned long arg) {
    switch (cmd) {
    case 0: // Set user PID
        if (copy_from_user(&user_pid, (pid_t*)arg, sizeof(pid_t))) {
            return -EFAULT;
        }

        // Find task struct for the given PID
        user_task = pid_task(find_vpid(user_pid), PIDTYPE_PID);
        printk(KERN_INFO "User  PID set: %d\n", user_pid);
        break;

    default:
        return -EINVAL;
    }
    return 0;
}

// File operations structure
static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .unlocked_ioctl = device_ioctl,
};

// Module Initialization
static int __init gpio_buttons_init(void) {
    int i, ret;

    // Initialize tasklet
    tasklet_init(&button_tasklet, button_tasklet_handler, 0);

    // Register character device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register device\n");
        return major_number;
    }

    // Create device class
    gpio_buttons_class = class_create(DEVICE_NAME);
    if (IS_ERR(gpio_buttons_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(gpio_buttons_class);
    }

    // Create device
    device_create(gpio_buttons_class, NULL, MKDEV(major_number, 0), NULL,
                  DEVICE_NAME);

    // Configure GPIO and request IRQs
    for (i = 0; i < NUM_BUTTONS; i++) {
        // Request GPIO
        ret = gpio_request(gpio_pins[i], "GPIO_BUTTON");
        if (ret) {
            printk(KERN_ALERT "Failed to request GPIO %d\n", gpio_pins[i]);
            return ret;
        }

        // Set GPIO as input
        gpio_direction_input(gpio_pins[i]);

        // Get IRQ number
        irq_numbers[i] = gpio_to_irq(gpio_pins[i]);
        if (irq_numbers[i] < 0) {
            printk(KERN_ALERT "Failed to get IRQ for GPIO %d\n", gpio_pins[i]);
            return irq_numbers[i];
        }

        // Request IRQ with both edges
        ret = request_irq(irq_numbers[i], gpio_irq_handler,
                          IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                          "gpio_button_handler", NULL);
        if (ret) {
            printk(KERN_ALERT "Failed to request IRQ %d\n", irq_numbers[i]);
            return ret;
        }
    }

    printk(KERN_INFO "GPIO Buttons Module Loaded\n");
    return 0;
}

// Module Exit
static void __exit gpio_buttons_exit(void) {
    int i;

    // Free IRQs and GPIOs
    for (i = 0; i < NUM_BUTTONS; i++) {
        free_irq(irq_numbers[i], NULL);
        gpio_free(gpio_pins[i]);
    }

    // Kill tasklet
    tasklet_kill(&button_tasklet);

    // Destroy device and class
    device_destroy(gpio_buttons_class, MKDEV(major_number, 0));
    class_unregister(gpio_buttons_class);
    class_destroy(gpio_buttons_class);
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "GPIO Buttons Module Unloaded\n");
}

module_init(gpio_buttons_init);
module_exit(gpio_buttons_exit);
