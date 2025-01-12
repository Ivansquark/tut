#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

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
	{ 0x509c9a84, "__platform_driver_register" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x822137e2, "arm_heavy_mb" },
	{ 0x9b76d8a6, "remove_proc_entry" },
	{ 0xedc03953, "iounmap" },
	{ 0x4384eb42, "__release_region" },
	{ 0xc94d8e3b, "iomem_resource" },
	{ 0xfc161b60, "platform_get_resource" },
	{ 0xf685e643, "_dev_err" },
	{ 0xae9849dd, "__request_region" },
	{ 0xe97c4103, "ioremap" },
	{ 0x5056add8, "proc_create" },
	{ 0x92997ed8, "_printk" },
	{ 0x36acf1b3, "seq_printf" },
	{ 0x9589e427, "kmalloc_trace" },
	{ 0x2cc08cc0, "single_open" },
	{ 0x37a0cba, "kfree" },
	{ 0x33710893, "kmalloc_caches" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x20000329, "simple_strtoul" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x255461e6, "platform_driver_unregister" },
	{ 0x7a5ca705, "seq_lseek" },
	{ 0x8069fb57, "seq_read" },
	{ 0x8a867055, "single_release" },
	{ 0xad1db79e, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cebaz,buzz-1.00.a");
MODULE_ALIAS("of:N*T*Cebaz,buzz-1.00.aC*");
