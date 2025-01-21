#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/io.h>

#define DEVICE_NAME "buzz"
#define AXI_GPIO_BASE 0x41200000
#define PWM_PERIOD_DEFAULT 1000 // Default PWM period in milliseconds

static volatile void __iomem *axi_gpio_base;
static int frequency = 0;
static int duration = 0;
static DECLARE_WAIT_QUEUE_HEAD(pwm_wait_queue);
static int pwm_running = 0;

static int buzz_open(struct inode *inode, struct file *file) {
    return 0;
}

static int buzz_release(struct inode *inode, struct file *file) {
    pwm_running = 0; // Stop PWM when device is closed
    return 0;
}

static ssize_t buzz_write(struct file *file, const char __user *buf, size_t count, loff_t *offset) {
    char input[32];
    int ret;

    if (count > sizeof(input) - 1)
        count = sizeof(input) - 1;

    if (copy_from_user(input, buf, count))
        return -EFAULT;

    input[count] = '\0'; // Null-terminate the string

    ret = sscanf(input, "%d,%d", &frequency, &duration);
    if (ret != 2) {
        printk(KERN_ERR "Invalid input format. Use: frequency,time\n");
        return -EINVAL;
    }

    // Calculate the delay based on frequency (in Hz)
    int high_time = (1000 / frequency) / 2; // High time in milliseconds
    int low_time = (1000 / frequency) / 2;  // Low time in milliseconds

    pwm_running = 1; // Start PWM
    while (pwm_running && duration > 0) {
        gpio_set_value(0, 1); // Set GPIO high
        mdelay(high_time); // Wait for high time
        gpio_set_value(0, 0); // Set GPIO low
        mdelay(low_time); // Wait for low time
        duration -= (high_time + low_time); // Decrease the remaining duration
    }

    return count;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = buzz_open,
    .release = buzz_release,
    .write = buzz_write,
};

static int __init buzz_init(void) {
    int ret;

    // Request GPIO (change the GPIO number as per your setup)
    if (!gpio_is_valid(0)) {
        printk(KERN_ERR "Invalid GPIO\n");
        return -ENODEV;
    }

    ret = gpio_request(0, "buzz_gpio");
    if (ret) {
        printk(KERN_ERR "Failed to request GPIO\n");
        return ret;
    }

    // Set GPIO direction to output
    gpio_direction_output(0, 0);

    // Map AXI GPIO registers
    axi_gpio_base = ioremap(AXI_GPIO_BASE, 0x1000);
    if (!axi_gpio_base) {
        printk(KERN_ERR "Failed to map AXI GPIO registers\n");
        gpio_free(0);
        return -ENOMEM;
    }

    // Register character device
    ret = register_chrdev(0, DEVICE_NAME, &fops);
    if (ret < 0) {
        printk(KERN_ERR "Failed to register character device\n");
        iounmap(axi_gpio_base);
        gpio_free(0);
        return ret;
    }

    printk(KERN_INFO "Buzz module loaded\n");
    return 0;
}

static void __exit buzz_exit(void) {
    pwm_running = 0; // Stop any running PWM
    unregister_chrdev(0, DEVICE_NAME);
    iounmap(axi_gpio_base);
    gpio_free(0);
    printk(KERN_INFO "Buzz module unloaded\n");
}

module_init(buzz_init);
module_exit(buzz_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Buzz Module for Zynq-7010");

