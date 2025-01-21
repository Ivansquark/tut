#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/io.h> // For io32 access
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/spinlock.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "buzz"
// The AXI GPIO base address (device tree will provide the actual address)
#define GPIO_ADDR 0x41200000

static struct platform_device* buzz_pdev;
static spinlock_t buzz_lock; // Spinlock for synchronization

static struct kobject* buzz_kobj;
static int frequency = 0;
static int time_ms = 0;

#define BUZZ_BUF_SIZE 64
static char buzz_buf[BUZZ_BUF_SIZE]; // Static buffer for storing user input

// Function to write to the GPIO (raw memory write using io32)
static inline void buzz_gpio_write(int value) {
    // Use io32 write function to write to GPIO address
    if (value) {
        iowrite32(1, (void __iomem*)GPIO_ADDR); // Set GPIO High
    } else {
        iowrite32(0, (void __iomem*)GPIO_ADDR); // Set GPIO Low
    }
}

// Function to set GPIO PWM
static void buzz_set_pwm(int freq, int time) {
    int high_time, low_time;
    int cycles = (time * freq) / 1000;
    high_time = time * freq / 2;
    low_time = time - high_time;

    spin_lock(&buzz_lock); // Acquire the lock to ensure safe access to GPIO

    for (int i = 0; i < cycles; i++) {
        buzz_gpio_write(1); // Set GPIO high
        mdelay(high_time);
        buzz_gpio_write(0); // Set GPIO low
        mdelay(low_time);
    }

    spin_unlock(&buzz_lock); // Release the lock after GPIO operation
}

// File operations
static int buzz_open(struct inode* inode, struct file* file) {
    pr_info("buzz: open function\n");
    return 0;
}

static int buzz_release(struct inode* inode, struct file* file) {
    pr_info("buzz: release function\n");
    return 0;
}

static ssize_t buzz_read(struct file* file, char __user* buf, size_t len,
                         loff_t* offset) {
    return 0; // No read functionality in this case
}

static ssize_t buzz_write(struct file* file, const char __user* buf, size_t len,
                          loff_t* offset) {
    int ret;

    // Ensure we don't overflow the static buffer
    if (len >= BUZZ_BUF_SIZE) {
        pr_err("buzz: input buffer overflow\n");
        return -EINVAL;
    }

    // Copy the data from user space to the static buffer
    if (copy_from_user(buzz_buf, buf, len)) {
        return -EFAULT;
    }

    buzz_buf[len] = '\0'; // Null terminate the string

    ret = sscanf(buzz_buf, "%d,%d", &frequency, &time_ms);
    if (ret == 2) {
        pr_info("buzz: frequency = %d, time = %d ms\n", frequency, time_ms);
        buzz_set_pwm(frequency, time_ms);
    } else {
        pr_err("buzz: Invalid input format\n");
        return -EINVAL;
    }

    return len;
}

// Define file operations structure
static const struct file_operations buzz_fops = {
    .owner = THIS_MODULE,
    .open = buzz_open,
    .release = buzz_release,
    .read = buzz_read,
    .write = buzz_write,
};

// Sysfs interface: Create attributes to expose frequency and time settings
static ssize_t frequency_show(struct kobject* kobj, struct kobj_attribute* attr,
                              char* buf) {
    return sprintf(buf, "%d\n", frequency);
}

static ssize_t frequency_store(struct kobject* kobj,
                               struct kobj_attribute* attr, const char* buf,
                               size_t count) {
    if (sscanf(buf, "%d", &frequency) == 1) {
        pr_info("buzz: Set frequency = %d\n", frequency);
    }
    return count;
}

static ssize_t time_show(struct kobject* kobj, struct kobj_attribute* attr,
                         char* buf) {
    return sprintf(buf, "%d\n", time_ms);
}

static ssize_t time_store(struct kobject* kobj, struct kobj_attribute* attr,
                          const char* buf, size_t count) {
    if (sscanf(buf, "%d", &time_ms) == 1) {
        pr_info("buzz: Set time = %d ms\n", time_ms);
    }
    return count;
}

static ssize_t start_pwm_store(struct kobject* kobj,
                               struct kobj_attribute* attr, const char* buf,
                               size_t count) {
    int start;

    if (sscanf(buf, "%d", &start) != 1) return -EINVAL;

    if (start == 1) {
        buzz_set_pwm(frequency, time_ms);
    } else if (start == 0) {
        // Add functionality to stop PWM here, if necessary
    } else {
        return -EINVAL;
    }

    return count;
}

// Define sysfs attributes
static struct kobj_attribute frequency_attr =
    __ATTR(frequency, 0660, frequency_show, frequency_store);
static struct kobj_attribute time_attr =
    __ATTR(time, 0660, time_show, time_store);
static struct kobj_attribute start_attr =
    __ATTR(start, 0660, NULL, start_pwm_store);

// Create the sysfs directory and attributes
static int create_sysfs(void) {
    int error;
    buzz_kobj = kobject_create_and_add("buzz", kernel_kobj);
    if (!buzz_kobj) return -ENOMEM;

    error = sysfs_create_file(buzz_kobj, &frequency_attr.attr);
    if (error) pr_err("buzz: failed to create frequency sysfs attribute\n");

    error = sysfs_create_file(buzz_kobj, &time_attr.attr);
    if (error) pr_err("buzz: failed to create time sysfs attribute\n");

    error =
        sysfs_create_file(buzz_kobj, &start_attr.attr); // Add start attribute
    if (error) pr_err("buzz: failed to create start sysfs attribute\n");

    return error;
}

// Remove the sysfs interface
static void remove_sysfs(void) {
    if (buzz_kobj) {
        kobject_put(buzz_kobj);
    }
}

// Platform Driver Initialization
static int buzz_probe(struct platform_device* pdev) {
    int ret;

    pr_info("buzz: Probe function\n");

    buzz_pdev = pdev;

    // Register the device as a char device
    ret = register_chrdev(0, DRIVER_NAME, &buzz_fops);
    if (ret < 0) {
        pr_err("buzz: failed to register character device\n");
        return ret;
    }

    // Create sysfs interface
    ret = create_sysfs();
    if (ret) {
        pr_err("buzz: failed to create sysfs interface\n");
        unregister_chrdev(ret, DRIVER_NAME);
        return ret;
    }

    pr_info("buzz: Driver initialized successfully\n");
    return 0;
}

// Platform Driver Removal
static int buzz_remove(struct platform_device* pdev) {
    pr_info("buzz: Remove function\n");

    // Remove sysfs interface
    remove_sysfs();

    // Unregister character device
    unregister_chrdev(0, DRIVER_NAME);

    pr_info("buzz: Driver removed successfully\n");
    return 0;
}

// Define platform driver structure
static const struct of_device_id buzz_of_match[] = {
    {
        .compatible = "simple-bus",
    },
    {},
};
MODULE_DEVICE_TABLE(of, buzz_of_match);

static struct platform_driver buzz_driver = {
    .probe = buzz_probe,
    .remove = buzz_remove,
    .driver =
        {
            .name = DRIVER_NAME,
            .of_match_table = buzz_of_match,
        },
};

// Initialize the platform driver
static int __init buzz_init(void) {
    spin_lock_init(&buzz_lock); // Initialize the spinlock
    return platform_driver_register(&buzz_driver);
}

// Cleanup the platform driver
static void __exit buzz_exit(void) { platform_driver_unregister(&buzz_driver); }

module_init(buzz_init);
module_exit(buzz_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Buzz driver for Zynq7010 platform using AXI GPIO");
MODULE_VERSION("1.0");
