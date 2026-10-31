#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CosmosTux");
MODULE_DESCRIPTION("Advanced Linux NotMyFault Kernel Driver");
#define PROC_NAME "notmyfault"
static ssize_t proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *data) {
    char cmd[16]; if (count > 15) return -EINVAL;
    if (copy_from_user(cmd, buffer, count)) return -EFAULT;
    cmd[count] = '\0';
    if (strncmp(cmd, "panic", 5) == 0) { panic("NotMyFault: Manually triggered Kernel Panic!"); }
    else if (strncmp(cmd, "pagefault", 9) == 0) { int *invalid_ptr = (int *)0x00001000; pr_alert("NotMyFault: Simulating Page Fault...\n"); *invalid_ptr = 42; }
    else if (strncmp(cmd, "hang", 4) == 0) { pr_alert("NotMyFault: Simulating System Hang...\n"); while(1) { mdelay(1000); } }
    else if (strncmp(cmd, "leak", 4) == 0) { void *ptr = kmalloc(256 * 1024 * 1024, GFP_KERNEL); if (!ptr) pr_err("NotMyFault: Out of Memory!\n"); }
    return count;
}
static const struct proc_ops proc_fops = { .proc_write = proc_write };
static int __init nmf_init(void) { proc_create(PROC_NAME, 0222, NULL, &proc_fops); return 0; }
static void __exit nmf_exit(void) { remove_proc_entry(PROC_NAME, NULL); }
module_init(nmf_init); module_exit(nmf_exit);
