#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xcbae5412, "__const_udelay" },
	{ 0xbd069841, "kstrtoull" },
	{ 0xe8213e80, "_printk" },
	{ 0xd710adbf, "__kmalloc_noprof" },
	{ 0x75738bed, "panic" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x2b3afeb6, "remove_proc_entry" },
	{ 0xd272d446, "__fentry__" },
	{ 0xbf2b4c01, "proc_create" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x35a0db66, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xbd03ed67,
	0x5cb46e6d,
	0xa61fd7aa,
	0x092a35a2,
	0xcbae5412,
	0xbd069841,
	0xe8213e80,
	0xd710adbf,
	0x75738bed,
	0x90a48d82,
	0xd272d446,
	0x2b3afeb6,
	0xd272d446,
	0xbf2b4c01,
	0xd272d446,
	0x35a0db66,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__ref_stack_chk_guard\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"__const_udelay\0"
	"kstrtoull\0"
	"_printk\0"
	"__kmalloc_noprof\0"
	"panic\0"
	"__ubsan_handle_out_of_bounds\0"
	"__stack_chk_fail\0"
	"remove_proc_entry\0"
	"__fentry__\0"
	"proc_create\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "B8BA3068BA4941DA9B1D3B3");
