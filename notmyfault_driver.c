#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CosmosTux");
MODULE_DESCRIPTION("Advanced Linux NotMyFault Kernel Driver v3.0");

#define PROC_NAME "notmyfault"

static ssize_t proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *data) {
    char cmd[32];
    unsigned long leak_size = 256; // Standardmäßig 256MB
    void *ptr;

    if (count > 31) return -EINVAL;
    if (copy_from_user(cmd, buffer, count)) return -EFAULT;
    cmd[count] = '\0';

    // 1. DYNAMISCHES SPEICHERLECK (Z.B. "leak:512")
    if (strncmp(cmd, "leak:", 5) == 0) {
        if (kstrtoul(cmd + 5, 10, &leak_size) == 0) {
            pr_info("NotMyFault: Versuche %lu MB im Kernel zu lecken...\n", leak_size);
            ptr = kmalloc(leak_size * 1024 * 1024, GFP_KERNEL);
            if (!ptr) pr_err("NotMyFault: Out of Memory bei %lu MB!\n", leak_size);
        }
    }
    // 2. HARD KERNEL PANIC
    else if (strncmp(cmd, "panic", 5) == 0) {
        panic("NotMyFault: Manually triggered Hard Kernel Panic (BSOD Equivalent)!");
    }
    // 3. PAGE FAULT (BAD POINTER READ)
    else if (strncmp(cmd, "pagefault", 9) == 0) {
        int *invalid_ptr = (int *)0x00001000;
        int val = *invalid_ptr;
        pr_info("NotMyFault: Read value %d\n", val);
    }
    // 4. NULL POINTER WRITE CRASH
    else if (strncmp(cmd, "nullwrite", 9) == 0) {
        int *ptr = NULL;
        *ptr = 0xDEADBEEF;
    }
    // 5. HARD CPU HANG (DEADLOCK)
    else if (strncmp(cmd, "hang", 4) == 0) {
        while(1) { mdelay(1000); }
    }

    return count;
}

static const struct proc_ops proc_fops = { .proc_write = proc_write };

static int __init nmf_init(void) {
    proc_create(PROC_NAME, 0222, NULL, &proc_fops);
    return 0;
}

static void __exit nmf_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
}

module_init(nmf_init);
module_exit(nmf_exit);
