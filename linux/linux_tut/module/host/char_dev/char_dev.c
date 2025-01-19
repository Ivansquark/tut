#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h> //kmalloc
#include <linux/uaccess.h>

// Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("Test chardev module interface");

// Variables for device and device class
static dev_t cd_nr;
static struct class* my_class;
static struct cdev my_device;

#define DRIVER_NAME ((const char*)"char_dev")
#define DRIVER_CLASS ((const char*)"MyClass")

static char buf[256];

static int cd_open(struct inode* device_file, struct file* instance) {
    printk(KERN_INFO "Dev nr open was called\n");
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
    not_copied = copy_to_user(user_buf, buf, to_copy);

    printk(KERN_INFO "Readed: %s\n", buf);
    // Calculate data
    delta = to_copy - not_copied;
    return 0;
    // return delta;
}

static ssize_t cd_write(struct file* File, const char* user_buf, size_t count,
                        loff_t* off) {
    // count integers
    int to_copy, not_copied, delta;
    // Get amount of data to copy
    to_copy = min(count, sizeof(buf));
    // Copy data to user
    not_copied = copy_from_user(buf, user_buf, to_copy);
    printk(KERN_INFO "Writed: %s\n", buf);
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
    if (alloc_chrdev_region(&cd_nr, 0, 1, DRIVER_NAME) < 0) {
        printk(KERN_ERR "Device canot be allocated");
        return -1;
    }
    printk(KERN_INFO "Major: %d  Minor: %d\n", cd_nr >> 20, cd_nr && 0xffff);
    // printk(KERN_INFO "Major: %d  Minor: %d\n", MAJOR(cd_nr), MINOR(cd_nr));

    // create device class
    if ((my_class = class_create(DRIVER_CLASS)) == NULL) {
        printk("Device class not created\n");
        goto ClassError;
    }

    // create device file
    if (device_create(my_class, NULL, cd_nr, NULL, DRIVER_NAME) == NULL) {
        printk(KERN_ERR "Cant create device file");
        goto FileError;
    }

    // Initialize device file
    cdev_init(&my_device, &fops);

    // Register device to kernel
    if (cdev_add(&my_device, cd_nr, 1) < 0) {
        printk(KERN_ERR "Registering device to kernel failed\n");
        goto AddError;
    }

    return 0;

AddError:
    device_destroy(my_class, cd_nr);
FileError:
    class_destroy(my_class);
ClassError:
    unregister_chrdev_region(cd_nr, 1);
    return -1;
}
static void __exit char_dev_exit(void) {
    cdev_del(&my_device);
    device_destroy(my_class, cd_nr);
    class_destroy(my_class);
    unregister_chrdev_region(cd_nr, 1);

    printk(KERN_INFO "Char_dev exit\n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);
