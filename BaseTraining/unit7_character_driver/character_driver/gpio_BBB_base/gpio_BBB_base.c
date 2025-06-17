#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>        // Thêm để dùng readl/writel
#include <linux/slab.h>

#define GPIO1_BASE             0x4804C000
#define GPIO_OE_OFFSET         0x134
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190

#define GPIO_PIN               28
#define GPIO_PIN_MASK          (1 << GPIO_PIN)

#define DEVICE_NAME            "gpio_dev"
#define CLASS_NAME             "gpio_class"

static void __iomem *gpio_base;
static dev_t dev_num;
static struct class *gpio_class;
static struct device *gpio_device;
static struct cdev gpio_cdev;
static uint32_t original_oe;

// ===== File operations =====
static int gpio_open(struct inode *inode, struct file *file) {
    pr_info("%s: device opened\n", DEVICE_NAME);
    original_oe = readl(gpio_base + GPIO_OE_OFFSET);
    writel(original_oe & ~GPIO_PIN_MASK, gpio_base + GPIO_OE_OFFSET);
    return 0;
}

static int gpio_release(struct inode *inode, struct file *file) {
    pr_info("%s: device closed\n", DEVICE_NAME);
    writel(original_oe, gpio_base + GPIO_OE_OFFSET);
    return 0;
}

static ssize_t gpio_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    char cmd;
    if (copy_from_user(&cmd, buf, 1))
        return -EFAULT;

    switch (cmd) {
        case '1':
            writel(GPIO_PIN_MASK, gpio_base + GPIO_SETDATAOUT_OFFSET);
            pr_info("printf 1 > /dev/gpio_dev\n");
            break;
        case '0':
            writel(GPIO_PIN_MASK, gpio_base + GPIO_CLEARDATAOUT_OFFSET);
            pr_info("printf 0 > /dev/gpio_dev");
            break;
        default:
            pr_info("%s: invalid write command\n", DEVICE_NAME);
            return -EINVAL;
    }
    return 1;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = gpio_open,
    .release = gpio_release,
    .write = gpio_write,
};

// ===== Module init/exit =====
static int __init gpio_driver_init(void) {
    int ret;

    if ((ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME)) < 0)
        return ret;

    cdev_init(&gpio_cdev, &fops);
    if ((ret = cdev_add(&gpio_cdev, dev_num, 1)) < 0)
        goto unregister;

    gpio_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(gpio_class)) {
        ret = PTR_ERR(gpio_class);
        goto del_cdev;
    }

    gpio_device = device_create(gpio_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(gpio_device)) {
        ret = PTR_ERR(gpio_device);
        goto destroy_class;
    }

    gpio_base = ioremap(GPIO1_BASE, 0x1000);
    if (!gpio_base) {
        ret = -ENOMEM;
        goto destroy_device;
    }

    pr_info("%s: driver initialized\n", DEVICE_NAME);
    return 0;

destroy_device:
    device_destroy(gpio_class, dev_num);
destroy_class:
    class_destroy(gpio_class);
del_cdev:
    cdev_del(&gpio_cdev);
unregister:
    unregister_chrdev_region(dev_num, 1);
    return ret;
}

static void __exit gpio_driver_exit(void) {
    iounmap(gpio_base);
    device_destroy(gpio_class, dev_num);
    class_destroy(gpio_class);
    cdev_del(&gpio_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("%s: driver unloaded\n", DEVICE_NAME);
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LiemVT");
MODULE_DESCRIPTION("Simple GPIO driver ON/OFF Led.");
