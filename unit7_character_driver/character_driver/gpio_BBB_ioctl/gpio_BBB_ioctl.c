#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>        // Thêm để dùng readl/writel
#include <linux/slab.h>

#define GPIO1_BASE             0x4804C000
#define GPIO_DATAIN_OFFSET      0x138
#define GPIO_OE_OFFSET         0x134
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190

#define GPIO_PIN               28
#define GPIO_PIN_MASK          (1 << GPIO_PIN)

#define DEVICE_NAME            "gpio_dev"
#define CLASS_NAME             "gpio_class"
#define GPIO_IOC_MAGIC     'G'
#define GPIO_IOC_SET_DIR   _IOW(GPIO_IOC_MAGIC, 0, int)  // 0=input, 1=output
#define GPIO_IOC_WRITE     _IOW(GPIO_IOC_MAGIC, 1, int)  // 0=low, 1=high
#define GPIO_IOC_READ      _IOR(GPIO_IOC_MAGIC, 2, int)

static void __iomem *gpio_base;
static dev_t dev_num;
static struct class *gpio_class;
static struct device *gpio_device;
static struct cdev gpio_cdev;

// ===== File operations =====
static int gpio_open(struct inode *inode, struct file *file) {
    pr_info("GPIO device opened\n");
    return 0;
}

static int gpio_release(struct inode *inode, struct file *file) {
    pr_info("GPIO device closed\n");
    return 0;
}

static ssize_t gpio_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    pr_info("GPIO device closed\n");
    return 0;
}

static long gpio_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int value;
    uint32_t reg;

    switch (cmd) {
        case GPIO_IOC_SET_DIR:
            if (copy_from_user(&value, (int __user *)arg, sizeof(int)))
                return -EFAULT;
            reg = readl(gpio_base + GPIO_OE_OFFSET);
            if (value == 1)
                reg &= ~GPIO_PIN_MASK;  // output.
            else
                reg |= GPIO_PIN_MASK;   // input.
            writel(reg, gpio_base + GPIO_OE_OFFSET);
            pr_info("GPIO_IOC_SET_DIR loaded %d\n", value);
            break;

        case GPIO_IOC_WRITE:
            if (copy_from_user(&value, (int __user *)arg, sizeof(int)))
                return -EFAULT;
            if (value == 1)
                {
                    writel(GPIO_PIN_MASK, gpio_base + GPIO_SETDATAOUT_OFFSET);
                    pr_info("GPIO_IOC_WRITE %d\n", value); 
                }
            else
                {
                    writel(GPIO_PIN_MASK, gpio_base + GPIO_CLEARDATAOUT_OFFSET);
                    pr_info("GPIO_IOC_WRITE %d\n", value);
                }
            break;

        case GPIO_IOC_READ:
            reg = readl(gpio_base + GPIO_DATAIN_OFFSET);
            value = (reg & GPIO_PIN_MASK) ? 1 : 0;
            pr_info("GPIO_IOC_READ %d\n", value);
            if (copy_to_user((int __user *)arg, &value, sizeof(int)))
                return -EFAULT;
            break;

        default:
            return -ENOTTY;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = gpio_open,
    .release = gpio_release,
    .write = gpio_write,
    .unlocked_ioctl = gpio_ioctl,
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
MODULE_DESCRIPTION("character driver GPIO using ioctl to control in/out .");
MODULE_VERSION("1.0");
