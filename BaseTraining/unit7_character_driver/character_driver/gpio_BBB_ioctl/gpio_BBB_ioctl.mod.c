#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
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
__used __section(__versions) = {
	{ 0x441199c1, "module_layout" },
	{ 0xedc03953, "iounmap" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x71eadc8, "cdev_del" },
	{ 0xebc96d1c, "class_destroy" },
	{ 0xa1c0b261, "device_destroy" },
	{ 0xe97c4103, "ioremap" },
	{ 0x3d3e385, "device_create" },
	{ 0xdcfb973, "__class_create" },
	{ 0xc663131e, "cdev_add" },
	{ 0x5f53d92f, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x822137e2, "arm_heavy_mb" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C376C1574222C683019252D");
