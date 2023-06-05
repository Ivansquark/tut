#include <iostream>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Opa");

static int __init opa_init(void) {
    printk("Opa");
    return 0;
}

static void __exit opa_exit(void) {
    printk("Bye");
}

module_init(opa_init);
module_exit(opa_exit);

//int main(int argc, char* argv[]) {
//    std::cout << "Module" << std::endl;
//    return 0;
//}
