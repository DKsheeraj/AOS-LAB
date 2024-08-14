#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

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
	{ 0x93fe36e, "module_layout" },
	{ 0xb67fda8a, "remove_proc_entry" },
	{ 0x45238fe8, "proc_create" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x5c1c3eb4, "cpu_hwcaps" },
	{ 0xb788fb30, "gic_pmr_sync" },
	{ 0x5e2d7875, "cpu_hwcap_keys" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x37a0cba, "kfree" },
	{ 0xbdab899, "kmem_cache_alloc_trace" },
	{ 0xe67bbcbf, "kmalloc_caches" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0xc5850110, "printk" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0x4b0a3f52, "gic_nonsecure_priorities" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "FD1BC9F603A08B89CA150B0");
