#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // Needed for KERN_INFO

int init_module(void)
{
    printk(KERN_INFO "Hello world 1.\n");
    // 0 を返すと、モジュールのロードに成功したことを意味します
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye world 1.\n");
}

MODULE_LICENSE("GPL");
