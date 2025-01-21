// buzz_driver.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/slab.h>

// Module metadata
#define DRIVER_NAME "buzz"
#define DRIVER_CLASS_NAME "buzz_class"

// AXI GPIO base address
#define AXI_GPIO_BASE 0x41200000
#define AXI_GPIO_SIZE 0x1000

// Driver private structure
struct buzz_driver {
    struct device *dev;
    void __iomem *gpio_base;  // Mapped GPIO register base
    int major_number;
    struct class *device_class;
    struct device *device;
    wait_queue_head_t wait_queue;
};

// Global driver instance
static struct buzz_driver *buzz_drv;

// File operations prototypes
static int buzz_open(struct inode *inode, struct file *file);
static int buzz_release(struct inode *inode, struct file *file);
static ssize_t buzz_write(struct file *file, const char __user *user_buffer, 
                          size_t count, loff_t *offs);

// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = buzz_open,
    .release = buzz_release,
    .write = buzz_write
};

// PWM implementation function
static void generate_pwm(int frequency, int duration_ms)
{
    int period_us = 1000000 / frequency;
    int half_period_us = period_us / 2;
    unsigned long timeout;

    // Initialize wait queue
    init_waitqueue_head(&buzz_drv->wait_queue);

    // PWM generation loop
    while (duration_ms > 0) {
        // Set GPIO high
        iowrite32(0x1, buzz_drv->gpio_base);
        
        // Wait for half period
        timeout = usecs_to_jiffies(half_period_us);
        wait_event_timeout(buzz_drv->wait_queue, 0, timeout);

        // Set GPIO low
        iowrite32(0x0, buzz_drv->gpio_base);

        // Wait for half period
        timeout = usecs_to_jiffies(half_period_us);
        wait_event_timeout(buzz_drv->wait_queue, 0, timeout);

        duration_ms -= (period_us / 1000);
    }
}

// File open handler
static int buzz_open(struct inode *inode, struct file *file)
{
    pr_info("Buzz device opened\n");
    return 0;
}

// File release handler
static int buzz_release(struct inode *inode, struct file *file)
{
    pr_info("Buzz device closed\n");
    return 0;
}

// Write handler to parse frequency and duration
static ssize_t buzz_write(struct file *file, const char __user *user_buffer, 
                          size_t count, loff_t *offs)
{
    char buffer[64];
    int frequency, duration;

    // Copy user data to kernel space
    if (copy_from_user(buffer, user_buffer, min(count, sizeof(buffer))) != 0) {
        return -EFAULT;
    }

    // Parse frequency and duration
    if (sscanf(buffer, "%d,%d", &frequency, &duration) != 2) {
        return -EINVAL;
    }

    // Generate PWM
    generate_pwm(frequency, duration);

    return count;
}

// Platform probe function
static int buzz_probe(struct platform_device *pdev)
{
    // Allocate driver structure
    buzz_drv = devm_kzalloc(&pdev->dev, sizeof(*buzz_drv), GFP_KERNEL);
    if (!buzz_drv)
        return -ENOMEM;

    // Map GPIO registers
    buzz_drv->gpio_base = devm_ioremap(&pdev->dev, AXI_GPIO_BASE, AXI_GPIO_SIZE);
    if (!buzz_drv->gpio_base)
        return -ENOMEM;

    // Register character device
    buzz_drv->major_number = register_chrdev(0, DRIVER_NAME, &fops);
    if (buzz_drv->major_number < 0)
        return buzz_drv->major_number;

    // Create device class
    buzz_drv->device_class = class_create(DRIVER_CLASS_NAME);
    if (IS_ERR(buzz_drv->device_class)) {
        unregister_chrdev(buzz_drv->major_number, DRIVER_NAME);
        return PTR_ERR(buzz_drv->device_class);
    }

    // Create device
    buzz_drv->device = device_create(buzz_drv->device_class, NULL, 
                                     MKDEV(buzz_drv->major_number, 0), 
                                     NULL, DRIVER_NAME);
    if (IS_ERR(buzz_drv->device)) {
        class_destroy(buzz_drv->device_class);
        unregister_chrdev(buzz_drv->major_number, DRIVER_NAME);
        return PTR_ERR(buzz_drv->device);
    }

    pr_info("Buzz driver initialized\n");
    return 0;
}

// Platform remove function
static int buzz_remove(struct platform_device *pdev)
{
    // Cleanup device
    device_destroy(buzz_drv->device_class, MKDEV(buzz_drv->major_number, 0));
    class_destroy(buzz_drv->device_class);
    unregister_chrdev(buzz_drv->major_number, DRIVER_NAME);

    return 0;
}

// Device tree match table
static const struct of_device_id buzz_of_match[] = {
    { .compatible = "simple-bus" },
    {}
};
MODULE_DEVICE_TABLE(of, buzz_of_match);

// Platform driver structure
static struct platform_driver buzz_driver = {
    .probe = buzz_probe,
    .remove = buzz_remove,
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = buzz_of_match,
    }
};

// Module initialization
static int __init buzz_init(void)
{
    return platform_driver_register(&buzz_driver);
}

// Module cleanup
static void __exit buzz_exit(void)
{
    platform_driver_unregister(&buzz_driver);
}

module_init(buzz_init);
module_exit(buzz_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Zynq-7010 Buzzer Driver");
