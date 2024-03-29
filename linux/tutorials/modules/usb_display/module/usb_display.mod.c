#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x7f05569b, "usb_find_interface" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x92997ed8, "_printk" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x2eaaa67a, "usb_bulk_msg" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xe8aada02, "usb_register_driver" },
	{ 0x128d92d7, "usb_deregister" },
	{ 0xe9e3ebca, "usb_deregister_dev" },
	{ 0x37a0cba, "kfree" },
	{ 0x26c930d9, "_dev_info" },
	{ 0x8abb0c2b, "kmalloc_caches" },
	{ 0x7b339a74, "kmalloc_trace" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0x9ed12e20, "kmalloc_large" },
	{ 0x9f2015b4, "usb_register_dev" },
	{ 0xa85023f1, "_dev_err" },
	{ 0x94a9c4ab, "module_layout" },
};

MODULE_INFO(depends, "usbcore");

MODULE_ALIAS("usb:v1A86pDEADd*dc*dsc*dp*ic*isc*ip*in*");
