#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_INFO(intree, "Y");

static int __init hi_init(void) {
    printk("Hi init");
    return 0;
}

static void __exit hi_exit(void) {
    printk("Hi exit");
}

module_init(hi_init);
module_exit(hi_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Greeting module");
MODULE_AUTHOR("Me");

