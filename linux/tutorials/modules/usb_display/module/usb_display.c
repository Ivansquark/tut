#include <linux/init.h> /* for macroses */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/usb.h>

#define DRIVER_AUTHOR "squark"
#define DRIVER_DESC "USB 320x240 16bit display module driver"
#define DEVICE_VENDOR_ID 0x1a86
#define DEVICE_PRODUCT_ID 0xdead

#define TOTAL_BUFFER_SIZE 64 * 100
#define DISP_MINOR_BASE 1

static atomic_t DeviceFree = ATOMIC_INIT(1);

static struct usb_device_id usb_display_table[] = {
    {USB_DEVICE(DEVICE_VENDOR_ID, DEVICE_PRODUCT_ID)},
    {} /* Terminating entry */
};
// to threat devices from table
MODULE_DEVICE_TABLE(usb, usb_display_table);
//callback
static int usb_display_probe(struct usb_interface*,
                             const struct usb_device_id*);
void usb_display_disconnect(struct usb_interface* interface);

static int usb_display_open(struct inode* inode, struct file* file);
static int usb_display_release(struct inode* inode, struct file* file);
static ssize_t usb_display_write(struct file* file, const char __user* user_buf,
                                 size_t count, loff_t* ppos);

struct usb_display {
    /* One structure for each connected device */
    struct usb_device* udev;
    struct usb_interface* interface;
    unsigned char minor;

    struct usb_endpoint_descriptor* bulk_out_ep;
    unsigned int bulk_out_packet_size;
    unsigned char* videobuffer;
    struct mutex io_mutex;
};

struct usb_display* dev;

struct usb_driver usb_display_driver = {
    //.owner = THIS_MODULE,
    .name = "usb_display",
    .probe = usb_display_probe,
    .disconnect = usb_display_disconnect,
    .id_table = usb_display_table,
};

module_usb_driver(usb_display_driver);

//to execute only through user-space application
static struct file_operations usb_display_fops = {
    .owner = THIS_MODULE,
    .write = usb_display_write, 
    .open = usb_display_open,
    .release = usb_display_release,
    // no read => only for writing
};

static struct usb_class_driver usb_display_class = {
    .name = "usb_disp%d",
    .fops = &usb_display_fops,
    .minor_base = DISP_MINOR_BASE,
};

static int usb_display_probe(struct usb_interface* interface,
                      const struct usb_device_id* id)
{
    /* called when a USB device is connected to the computer. */
    // struct usb_display* dev;
    struct usb_host_interface* iface_desc;
    struct usb_endpoint_descriptor* endpoint;
    int i;
    int retval = -ENODEV;

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);

    if (!dev) {
        dev_err(&interface->dev, "Out of memory\n");
        retval = -ENOMEM;
        return retval;
    }

    dev->udev = interface_to_usbdev(interface);
    mutex_init(&dev->io_mutex);

    dev->interface = interface;
    // get interface description (current)
    iface_desc = interface->cur_altsetting;

    // get endpoints data
    for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
        endpoint = &iface_desc->endpoint[i].desc;
        if (usb_endpoint_is_bulk_out(endpoint)) {
            dev->bulk_out_ep = endpoint;
            // to little endian 16 bits
            dev->bulk_out_packet_size = le16_to_cpu(endpoint->wMaxPacketSize);
            break;
        }
    }
    if (!dev->bulk_out_ep) {
        dev_err(&interface->dev, "Can not find bulk-out endpoint!\n");
        retval = -EIO;
        kfree(dev);
        return retval;
    }

    dev->videobuffer = kmalloc(TOTAL_BUFFER_SIZE, GFP_KERNEL);

    if (!dev->videobuffer) {
        dev_err(&interface->dev, "Out of memory\n");
        retval = -ENOMEM;
        kfree(dev);
        return retval;
    }
    // through kernel callbacks
    usb_set_intfdata(interface, dev);
    // registration device in /dev/usb_disp
    retval = usb_register_dev(interface, &usb_display_class);
    if (retval) {
        dev_err(&interface->dev, "Not able to get a minor for this device.");
        usb_set_intfdata(interface, NULL);
        kfree(dev->videobuffer);
        return retval;
    }
    dev->minor = interface->minor;
    dev_info(&interface->dev, "USB display driver%d\n",
             dev->minor - DISP_MINOR_BASE);

    printk(KERN_INFO "USB display CONNECTED!\n");
    return retval;
}

void usb_display_disconnect(struct usb_interface* interface)
{

    struct usb_display* dev;
    int minor;

    dev = usb_get_intfdata(interface);
    minor = dev->minor;
    usb_set_intfdata(interface, NULL); // to NULL
    usb_deregister_dev(interface, &usb_display_class);

    mutex_lock(&dev->io_mutex);
    dev->interface = NULL;
    mutex_unlock(&dev->io_mutex);

    kfree(dev->videobuffer);
    kfree(dev);
    dev_info(&interface->dev, "USB display riscv-based module%d disconnected\n",
             minor - DISP_MINOR_BASE);
    printk(KERN_INFO "USB display DISCONNECTED!\n");
}

// to do other file operations
static int usb_display_open(struct inode* inode, struct file* file)
{
    /* open syscall */
    struct usb_display* dev;
    struct usb_interface* interface;
    int retval = 0;
    int subminor;
    // file->private_data = NULL;

    if (!atomic_dec_and_test(&DeviceFree)) {
        atomic_inc(&DeviceFree);
        return -EBUSY;
    }

    subminor = iminor(inode);
    interface = usb_find_interface(&usb_display_driver, subminor);
    if (!interface) {
        printk(KERN_ERR "usblcd driver error, can't find device for minor %d\n",
               subminor);
        retval = -ENODEV;
        return retval;
    }

    dev = usb_get_intfdata(interface);
    if (!dev) {
        retval = -ENODEV;
        return retval;
    }

    mutex_lock(&dev->io_mutex);

    if (!dev->interface) {
        retval = -ENODEV;
        mutex_unlock(&dev->io_mutex);
        return retval;
    }

    file->private_data = dev;
    // dev_info(&interface->dev, "usb_display: opened successfuly");

    mutex_unlock(&dev->io_mutex);
    // printk(KERN_INFO "USB display OPENED!\n");
    return 0;
}

static int usb_display_release(struct inode* inode, struct file* file)
{
    /* close syscall */
    // printk(KERN_INFO "USB display released!\n");
    atomic_inc(&DeviceFree);
    file->private_data = NULL;
    return 0;
}

static ssize_t usb_display_write(struct file* file, const char __user* user_buf,
                                 size_t count, loff_t* ppos)
{
    /* write syscall */
    struct usb_display* dev;
    struct usb_interface* interface;
    int retval = -ENODEV;

    int usbSent = 0;
    int writtenCount = count;

    dev = file->private_data;
    //////////  MUTEX   ///////////////////
    mutex_lock(&dev->io_mutex);

    interface = dev->interface;
    if (!interface) {
        printk(KERN_ERR "usb_display driver error, no device found\n");
        retval = -ENODEV;
        mutex_unlock(&dev->io_mutex);
        return retval;
    }

    if (copy_from_user(dev->videobuffer, user_buf, writtenCount)) {
        retval = -EFAULT;
        mutex_unlock(&dev->io_mutex);
        return retval;
    }
    retval = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 4),
                          dev->videobuffer, writtenCount, &usbSent, 1000);
    if (!retval) {
        retval = writtenCount;
        ppos += retval;
    } else {
        retval = -EIO;
        mutex_unlock(&dev->io_mutex);
        return retval;
    }
    //////////  MUTEX   ///////////////////
    mutex_unlock(&dev->io_mutex);
    return retval;
}

// static int __init beepdriver_init(void) {
//    printk(KERN_INFO "Hello, beep!\n");
//    return usb_register(&usb_display_driver);
//}
//
// static void __exit beepdriver_exit(void) {
//    printk(KERN_INFO "Goodbye, beep!\n");
//    usb_deregister(&usb_display_driver);
//}
//
// module_init(beepdriver_init);
// module_exit(beepdriver_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
