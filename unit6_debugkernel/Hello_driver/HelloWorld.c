#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LiemVT");
MODULE_DESCRIPTION("A simple Hello World kernel module");
MODULE_VERSION("0.1");

static int __init helloworld_init(void) {
    printk(KERN_INFO "Hello, Kernel!\n");
    return 0;
}

static void __exit helloworld_exit(void) {
    printk(KERN_INFO "Goodbye, Kernel!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
