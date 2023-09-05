#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fb.h>
#include <linux/init.h> /* for macroses */
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/vmalloc.h>

#include <linux/mutex.h>
#include <linux/usb.h>

#define WIDTH 320
#define HEIGHT 240
#define BYTE_DEPTH 2
#define FB_SIZE (WIDTH * HEIGHT * BYTE_DEPTH)
#define FP_PAGE_COUNT (PAGE_ALIGN(FB_SIZE) / PAGE_SIZE)
#define PIXELS_IN_PAGE (PAGE_SIZE / BYTE_DEPTH)
// PAGE_SIZE = 4096 => mem pages = 37,5 => 38 for full display

#define DRIVER_AUTHOR "squark"
#define DRIVER_DESC "USB 320x240 16bit display module frame buffer driver"
#define DEVICE_VENDOR_ID 0x1a86
#define DEVICE_PRODUCT_ID 0xdead

//#define TOTAL_BUFFER_SIZE 64 * 100
#define DISP_MINOR_BASE 1
MODULE_INFO(intree, "Y");
// static atomic_t DeviceFree = ATOMIC_INIT(1);

struct videopage {
    int x, y;
    unsigned char* mem;
    unsigned long length;
    atomic_t toUpdate;
}; // 38 * sizeof(videopage) = (4 + 4 + 4 + 4 + 1)=646 (20*38=760)

static struct usb_device_id usblcd_table[] = {
    {USB_DEVICE(DEVICE_VENDOR_ID, DEVICE_PRODUCT_ID)},
    {} /* Terminating entry */
};
// to threat devices from table
MODULE_DEVICE_TABLE(usb, usblcd_table);
//-----------------  callbacks  -----------------------------------------------
static int usblcd_probe(struct usb_interface*, const struct usb_device_id*);
void usblcd_disconnect(struct usb_interface* interface);
static void display_fillrect(struct fb_info* p, const struct fb_fillrect* rect);
// block bits from extern buffer to definite position
static void display_imageblit(struct fb_info* p, const struct fb_image* image);
// block bits from videomemory to definite position
static void display_copyarea(struct fb_info* p, const struct fb_copyarea* area);
static ssize_t display_write(struct fb_info* p, const char __user* buf,
                             size_t count, loff_t* ppos);
static int display_setcolreg(unsigned regno, unsigned red, unsigned green,
                             unsigned blue, unsigned transp,
                             struct fb_info* info);
static void display_update(struct fb_info* info, struct list_head* pagelist);

static struct fb_fix_screeninfo fixed_info = {
    .id = "USB_LCD",
    .type = FB_TYPE_PACKED_PIXELS,
    .visual = FB_VISUAL_TRUECOLOR,
    .accel = FB_ACCEL_NONE,
    .line_length = WIDTH * BYTE_DEPTH,
};

static struct fb_var_screeninfo var_info = {
    .xres = WIDTH,
    .yres = HEIGHT,
    .xres_virtual = WIDTH,
    .yres_virtual = HEIGHT,
    .width = WIDTH,
    .height = HEIGHT,
    .bits_per_pixel = 16,
    // first-offset, second-length_in_bits, third-right_signed_bit
    .red = {11, 5, 0},
    .green = {5, 6, 0},
    .blue = {0, 5, 0},
    .activate = FB_ACTIVATE_NOW,
    .vmode = FB_VMODE_NONINTERLACED,
};

static struct fb_deferred_io display_defio = {
    .delay = HZ / 24,
    .deferred_io = &display_update,
};

static struct fb_ops display_fbops = {
    .owner = THIS_MODULE,
    .fb_read = fb_sys_read,
    .fb_write = display_write,
    .fb_fillrect = display_fillrect,
    .fb_copyarea = display_copyarea,
    .fb_imageblit = display_imageblit,
    .fb_setcolreg = display_setcolreg,
};

// device descriptor
struct usblcd {
    // usb device
    struct usb_device* udev;
    struct usb_interface* interface;
    struct usb_endpoint_descriptor* bulk_out_ep;
    unsigned int bulk_out_packet_size;

    // framebuffer device
    struct device* gdev;
    struct fb_info* info;
    // array of video ram pages descriptors
    // struct videopage videopages[FP_PAGE_COUNT];
    unsigned char* videomemory;
    // for fbcon (fiil in fb_setcolreg callback)
    unsigned long pseudo_palette[17];

    struct mutex io_mutex;
};

struct usblcd* dev;

struct usb_driver usblcd_driver = {
    //.owner = THIS_MODULE,
    .name = "usb_display",
    .probe = usblcd_probe,
    .disconnect = usblcd_disconnect,
    .id_table = usblcd_table,
};

module_usb_driver(usblcd_driver);

static int display_setcolreg(unsigned regno, unsigned red, unsigned green,
                             unsigned blue, unsigned transp,
                             struct fb_info* info)
{
    int ret = 1;
    if (info->var.grayscale)
        red = green = blue = (19595 * red + 38470 * green + 7471 * blue) >> 16;
        // red = green = blue =
        //    (red * 77 + green * 151 + blue * 28) >> 8;
#define CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)
    switch (info->fix.visual) {
    case FB_VISUAL_TRUECOLOR:
        if (regno < 16) {
            u32 value;

            red = CNVT_TOHW(red, info->var.red.length);
            green = CNVT_TOHW(green, info->var.green.length);
            blue = CNVT_TOHW(blue, info->var.blue.length);
            transp = CNVT_TOHW(transp, info->var.transp.length);
#undef CNVT_TOHW
            value = (red << info->var.red.offset) |
                    (green << info->var.green.offset) |
                    (blue << info->var.blue.offset) |
                    (transp << info->var.transp.offset);

            ((u32*)(info->pseudo_palette))[regno] = value;
            ret = 0;
        }
        break;
    case FB_VISUAL_STATIC_PSEUDOCOLOR:
        break;
    case FB_VISUAL_PSEUDOCOLOR:
        break;
    }
    return ret;
}

static void display_touch(struct fb_info* info, int x, int y, int w, int h)
{
    schedule_delayed_work(&info->deferred_work, info->fbdefio->delay);
}

static void display_fillrect(struct fb_info* p, const struct fb_fillrect* rect)
{
    sys_fillrect(p, rect);
    display_touch(p, rect->dx, rect->dy, rect->width, rect->height);
}

static void display_imageblit(struct fb_info* p, const struct fb_image* image)
{
    sys_imageblit(p, image);
    display_touch(p, image->dx, image->dy, image->width, image->height);
}

static void display_copyarea(struct fb_info* p, const struct fb_copyarea* area)
{
    sys_copyarea(p, area);
    display_touch(p, area->dx, area->dy, area->width, area->height);
}

static ssize_t display_write(struct fb_info* p, const char __user* buf,
                             size_t count, loff_t* ppos)
{
    int retval;
    retval = fb_sys_write(p, buf, count, ppos);
    display_touch(p, 0, 0, p->var.xres, p->var.yres);
    return retval;
}

//------------------------  connect usb ---------------------------------------
static int usblcd_probe(struct usb_interface* interface,
                        const struct usb_device_id* id)
{
    /* called when a USB device is connected to the computer. */
    struct usblcd* dev;
    struct usb_host_interface* iface_desc;
    struct usb_endpoint_descriptor* endpoint;
    // unsigned char* videomemory;
    int retval = -ENODEV;
    int i;
    dev_info(&interface->dev, "USB LCD module connected");
    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        dev_err(&interface->dev, "Out of memory\n");
        retval = -ENOMEM;
        goto exit;
    }
    //-----------------  usb  -------------------------------------------------
    dev->udev = interface_to_usbdev(interface);
    mutex_init(&dev->io_mutex);
    dev->interface = interface;
    // get interface description (current)
    iface_desc = interface->cur_altsetting;
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
        goto error_dev;
    }
    //-----------------  graphic  ---------------------------------------------
    dev->gdev = &dev->udev->dev;
    dev->info = framebuffer_alloc(0, dev->gdev);
    dev->info->par = dev;
    dev->info->dev = dev->gdev;
    if (!dev->info) {
        dev_err(&interface->dev,
                "Can not allocate memory for fb_info structure\n");
        retval = -ENOMEM;
        goto error_dev;
    }

    dev->info->fix = fixed_info;
    dev->info->var = var_info;

    usb_set_intfdata(interface, dev);
    // dev->info->fix.smem_len = FP_PAGE_COUNT * PAGE_SIZE;
    dev->info->fix.smem_len = FB_SIZE;

    dev_info(&interface->dev, "Allocating framebuffer: %d bytes [%lu pages]\n",
             dev->info->fix.smem_len, FP_PAGE_COUNT);

    // dev->videomemory = vmalloc(dev->info->fix.smem_len);
    dev->videomemory = kmalloc(FB_SIZE, GFP_KERNEL);
    if (!dev->videomemory) {
        dev_err(&interface->dev, "Can not allocate memory for framebuffer\n");
        retval = -ENOMEM;
        goto error_dev;
    }
    dev->info->fix.smem_start = (unsigned long)(dev->videomemory);
    dev->info->fbops = &display_fbops;
    dev->info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;
    dev->info->screen_base = dev->videomemory;
    // set memory to black
    memset((void*)dev->info->fix.smem_start, 0, dev->info->fix.smem_len);

    dev->info->pseudo_palette = &dev->pseudo_palette;

    dev->info->fbdefio = &display_defio;

    fb_deferred_io_init(dev->info);

    dev_info(
        &interface->dev,
        "info.fix.smem_start=%16lux\ninfo.fix.smem_len=%d\ninfo.screen_size="
        "%lu\n",
        dev->info->fix.smem_start, dev->info->fix.smem_len,
        dev->info->screen_size);

    usb_set_intfdata(interface, dev);
    retval = register_framebuffer(dev->info);
    if (retval < 0) {
        dev_err(dev->gdev, "Unable to register_frambuffer\n");
        goto error_buff;
    }

    return retval;

error_buff:
    // vfree(dev->videomemory);
    dev_err(dev->gdev, "error_buff\n");
    kfree(dev->videomemory);

error_dev:
    kfree(dev);

exit:
    return retval;
}
//---------------------  disconnect  ------------------------------------------
void usblcd_disconnect(struct usb_interface* interface)
{
    struct usblcd* dev;

    dev = usb_get_intfdata(interface);
    usb_set_intfdata(interface, NULL); // to NULL
    // usb_deregister_dev(interface, &usblcd_class);
    framebuffer_release(dev->info);
    // mutex_lock(&dev->io_mutex);
    dev->interface = NULL;
    // mutex_unlock(&dev->io_mutex);
    // TODO: free memory pages
    kfree(dev->videomemory);
    kfree(dev);
    printk(KERN_INFO "USB display DISCONNECTED!\n");
}

//---------------------  write in display  ------------------------------------
static void display_update(struct fb_info* info, struct list_head* pagelist)
{
    struct usblcd* dev = info->par;
    int retval = -ENODEV;
    int usbSent = 0;
    
    //////////  MUTEX   ///////////////////
    mutex_lock(&dev->io_mutex);
    /*
    interface = dev->interface;
    if (!interface) {
        printk(KERN_ERR "usb_display driver error, no device found\n");
        retval = -ENODEV;
        mutex_unlock(&dev->io_mutex);
        return;
    }
    */
    // printk(KERN_INFO "try to sending !!!\n");
    retval = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 4),
                          dev->videomemory, FB_SIZE, &usbSent, HZ);
    // printk(KERN_INFO "sending !!! - %d\n", usbSent);
    //////////  MUTEX   ///////////////////
    mutex_unlock(&dev->io_mutex);
}

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
