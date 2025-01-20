#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h> //kmalloc
#include <linux/uaccess.h>

// Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("Test chardev module interface");

// Variables for device and device class
static dev_t cd_gpio_num;
static struct class* my_class;
static struct cdev my_device;

static int gpio_open_count = 0;

#define DRIVER_NAME ((const char*)"char_dev")
#define DRIVER_CLASS ((const char*)"MyClass")

#define LED1 55 // EMIO GPIO number
#define LED2 56 // EMIO GPIO number
#define LED3 57 // EMIO GPIO number

static char buf[256];

static int cd_open(struct inode* device_file, struct file* instance) {
    printk(KERN_INFO "Dev nr open was called\n");
    gpio_open_count++;
    pr_info("GPIO device opened %d times\n", gpio_open_count);
    return 0;
}
static int cd_close(struct inode* device_file, struct file* instance) {
    printk(KERN_INFO "Dev nr close was called\n");
    return 0;
}

// Read data out of the buffer
static ssize_t cd_read(struct file* File, char* user_buf, size_t count,
                       loff_t* off) {
    // TODO: get clear about loff off  to repair cat
    // printk(KERN_INFO "Readed count: %lu", count);
    printk(KERN_INFO "Readed count: %lu loff: %lx\n", count,
           (long unsigned)off);
    // count integers
    int to_copy, not_copied, delta;
    // Get amount of data to copy
    to_copy = min(count, sizeof(buf));
    // Copy data to user
    //
    char value;
    // Read GPIO value
    value += gpio_get_value(LED1);
    value += (gpio_get_value(LED2) << 1);
    value += (gpio_get_value(LED3) << 2);
    value += '0';
    buf[0] = value;
    if ((not_copied = copy_to_user(buf, &value, 1))) {
        return -EFAULT;
    }
    printk(KERN_INFO "Readed: %s\n", buf);
    // Calculate data
    delta = to_copy - not_copied;
    return 0;
    // return delta;
}

static ssize_t cd_write(struct file* File, const char* __user user_buf,
                        size_t count, loff_t* off) {
    // count integers
    int to_copy, not_copied, delta;
    // Get amount of data to copy
    to_copy = min(count, sizeof(buf));
    // Copy data to user
    not_copied = copy_from_user(buf, user_buf, to_copy);
    printk(KERN_INFO "Writed: %s\n", buf);
    char val = buf[0];
    gpio_set_value(LED1, val & 0x1);
    gpio_set_value(LED2, (val >> 1) & 0x1);
    gpio_set_value(LED3, (val >> 2) & 0x1);
    // Calculate data
    delta = to_copy - not_copied;
    return delta;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = cd_open,
    .release = cd_close,
    .read = cd_read,
    .write = cd_write, //
};

static int __init char_dev_init(void) {
    printk(KERN_INFO "Char_dev init\n");
    if (alloc_chrdev_region(&cd_gpio_num, 0, 1, DRIVER_NAME) < 0) {
        printk(KERN_ERR "Device canot be allocated");
        return -1;
    }
    printk(KERN_INFO "Major: %d  Minor: %d\n", cd_gpio_num >> 20,
           cd_gpio_num && 0xffff);
    // printk(KERN_INFO "Major: %d  Minor: %d\n", MAJOR(cd_gpio_num),
    // MINOR(cd_gpio_num));

    // create device class
    //if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
    if ((my_class = class_create(DRIVER_CLASS)) == NULL) {
        printk("Device class not created\n");
        goto ClassError;
    }

    // create device file
    if (device_create(my_class, NULL, cd_gpio_num, NULL, DRIVER_NAME) == NULL) {
        printk(KERN_ERR "Cant create device file");
        goto FileError;
    }

    // Initialize device file
    cdev_init(&my_device, &fops);

    // Register device to kernel
    if (cdev_add(&my_device, cd_gpio_num, 1) < 0) {
        printk(KERN_ERR "Registering device to kernel failed\n");
        goto AddError;
    }

    if (!(gpio_is_valid(LED1) && gpio_is_valid(LED2) && gpio_is_valid(LED3))) {
        pr_err("Invalid GPIO\n");
        return -ENODEV;
    }
    // request gpio
    gpio_request(LED1, "sysfs");
    // Set GPIO as output and initial value to 0
    gpio_direction_output(LED1, 0);
    // request gpio
    gpio_request(LED2, "sysfs");
    // Set GPIO as output and initial value to 0
    gpio_direction_output(LED2, 0);
    // request gpio
    gpio_request(LED3, "sysfs");
    // Set GPIO as output and initial value to 0
    gpio_direction_output(LED3, 0);
    return 0;

AddError:
    device_destroy(my_class, cd_gpio_num);
FileError:
    class_destroy(my_class);
ClassError:
    unregister_chrdev_region(cd_gpio_num, 1);
    return -1;
}
static void __exit char_dev_exit(void) {
    cdev_del(&my_device);
    device_destroy(my_class, cd_gpio_num);
    class_destroy(my_class);
    unregister_chrdev_region(cd_gpio_num, 1);
    gpio_free(LED1);
    gpio_free(LED2);
    gpio_free(LED3);
    printk(KERN_INFO "Char_dev exit\n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);
