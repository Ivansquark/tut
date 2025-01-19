#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h> /* Needed for Platform Driver Functions */
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/uaccess.h>  /* Needed for copy_from_user */
#include <asm/uaccess.h>  /* Needed for copy_from_user */
#include <asm/io.h> /* Needed for IO Read/Write Functions */
#include <linux/proc_fs.h> /* Needed for Proc File System Functions */
#include <linux/seq_file.h> /* Needed for Sequence File Operations */

MODULE_INFO(intree, "Y");

#define DRIVER_NAME "buzz"

unsigned long *base_addr;   /* Virtual Base Address*/ 
struct resource *res;       /* Device Resource Structure */
unsigned long remap_size;   /* Device Memory Size */

static ssize_t proc_buzz_write(struct file* file, const char __user * buf,
        size_t count, loff_t* ppos) {

    char buzz_buf[16];
    u32 buzz_value;

    if (count < 11) {
        if (copy_from_user(buzz_buf, buf, count)) {
            return -EFAULT;
        }
        buzz_buf[count] = 0;
    }
    buzz_value = simple_strtoul(buzz_buf, NULL, 0);
    wmb();
    iowrite32(buzz_value, base_addr);
    return count;
}

static int proc_buzz_show(struct seq_file* p, void* v) {
    u32 buzz_value;
    buzz_value = ioread32(base_addr);
    seq_printf(p, "0x%x", buzz_value);
    return 0;
}

static int proc_buzz_open(struct inode* inode, struct file* file) {
    unsigned int size = 16;
    char* buf;
    struct seq_file* m;
    int res;

    buf = (char*)kmalloc(size * sizeof(char), GFP_KERNEL);
    if(!buf) {
        return -ENOMEM;
    }
    res = single_open(file, proc_buzz_show, NULL);
    if(!res) {
        m = file->private_data;
        m->buf = buf;
        m->size = size;
    } else {
        kfree(buf);
    }
    return res;
}

/* File Operations for /proc/buzz */
static const struct file_operations proc_buzz_operations = {
    .open = proc_buzz_open,
    .read = seq_read,
    .write = proc_buzz_write,
    .llseek = seq_lseek,
    .release = single_release
};

static void buzz_shutdown(struct platform_device* pdev) {
    iowrite32(0, base_addr);
}

static int buzz_remove(struct platform_device *pdev) {
    buzz_shutdown(pdev);
    /* Remove /proc/buzz entry */
    remove_proc_entry(DRIVER_NAME, NULL);
    /* Release mapped virtual address */
    iounmap(base_addr);
    /* Release the region */
    release_mem_region(res->start, remap_size);
    return 0;
}

/* Device Probe function for buzz
 *------------------------------------
 * Get the resource structure from the information in device tree.
 * request the memory regioon needed for the controller, and map it into
 * kernel virtual memory space. Create an entry under /proc file system
 * and register file operations for that entry.
 */
static int buzz_probe(struct platform_device *pdev) {
    printk("[[ BUZZ ]] probe started");
    struct proc_dir_entry* buzz_proc_entry;
    int ret = 0;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        dev_err(&pdev->dev, "No memory resource\n");
        return -ENODEV;
    }

    remap_size = res->end - res->start + 1;
    if (!request_mem_region(res->start, remap_size, pdev->name)) {
        dev_err(&pdev->dev, "Cannot request IO\n");
        return -ENXIO;
    }

    base_addr = ioremap(res->start, remap_size);
    if (base_addr == NULL) {
        dev_err(&pdev->dev, "Couldn't ioremap memory at 0x%08lx\n",
                (unsigned long)res->start);
        ret = -ENOMEM;
        goto err_release_region;
    }
    buzz_proc_entry = proc_create(DRIVER_NAME, 0, NULL,
            (const struct proc_ops*)&proc_buzz_operations);
    if(buzz_proc_entry == NULL) {
        dev_err(&pdev->dev, "Couldn't create proc entry\n");
        ret = -ENOMEM;
        goto err_create_proc_entry;
    }
    printk(KERN_INFO DRIVER_NAME " probed at VA 0x%08lx\n",
            (unsigned long) base_addr);

    return 0;

err_create_proc_entry:
    iounmap(base_addr);
err_release_region:
    release_mem_region(res->start, remap_size);

    return ret;
}

/* device match table to match with device node in device tree */
static const struct of_device_id buzz_of_match[] = {
    { .compatible = "ebaz,buzz-1.00.a" },
    {}
};

MODULE_DEVICE_TABLE(of, buzz_of_match);

/* platform driver structure for buzz driver */
static struct platform_driver buzz_driver = {
    .driver = {
    .name = DRIVER_NAME,
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(buzz_of_match),
    },
    .probe = buzz_probe,
    .remove = buzz_remove,
    .shutdown = buzz_shutdown,
};

/* Register buzz platform driver */
module_platform_driver(buzz_driver);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("buzz driver");
