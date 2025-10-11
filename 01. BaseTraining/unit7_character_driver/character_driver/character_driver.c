// generic_char_driver.c - Reusable character driver skeleton

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "generic_dev"
#define CLASS_NAME  "generic_class"
#define IOCTL_MAX_LEN 256

static dev_t dev_num;
static struct class *drv_class;
static struct device *drv_device;
static struct cdev drv_cdev;

static char ioctl_buf[IOCTL_MAX_LEN] = {0};

// ========= Interface để tái sử dụng =========
struct generic_dev_ops {
    int  (*open)(void);
    int  (*release)(void);
    ssize_t (*read)(char __user *buf, size_t len);
    ssize_t (*write)(const char __user *buf, size_t len);
    long (*ioctl)(unsigned int cmd, unsigned long arg);
};

// Đối tượng giữ các hàm xử lý riêng của ngoại vi
static struct generic_dev_ops *dev_ops = NULL;

// ========= Wrapper để khớp với file_operations =========
static int drv_open(struct inode *inode, struct file *file) {
    return dev_ops && dev_ops->open ? dev_ops->open() : 0;
}

static int drv_release(struct inode *inode, struct file *file) {
    return dev_ops && dev_ops->release ? dev_ops->release() : 0;
}

static ssize_t drv_read(struct file *file, char __user *buf, size_t len, loff_t *off) {
    return dev_ops && dev_ops->read ? dev_ops->read(buf, len) : -ENOSYS;
}

static ssize_t drv_write(struct file *file, const char __user *buf, size_t len, loff_t *off) {
    return dev_ops && dev_ops->write ? dev_ops->write(buf, len) : -ENOSYS;
}

static long drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    return dev_ops && dev_ops->ioctl ? dev_ops->ioctl(cmd, arg) : -ENOTTY;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = drv_open,
    .release = drv_release,
    .read = drv_read,
    .write = drv_write,
    .unlocked_ioctl = drv_ioctl,
};

// ========= API public để device khác đăng ký handler =========
int register_device_ops(struct generic_dev_ops *ops) {
    dev_ops = ops;
    return 0;
}
EXPORT_SYMBOL(register_device_ops);

int unregister_device_ops(void) {
    dev_ops = NULL;
    return 0;
}
EXPORT_SYMBOL(unregister_device_ops);

// ========= Module Init/Exit =========
static int __init generic_driver_init(void) {
    int ret;

    if ((ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME)) < 0)
        return ret;

    cdev_init(&drv_cdev, &fops);
    if ((ret = cdev_add(&drv_cdev, dev_num, 1)) < 0)
        goto unregister;

    drv_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(drv_class)) {
        ret = PTR_ERR(drv_class);
        goto del_cdev;
    }

    drv_device = device_create(drv_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(drv_device)) {
        ret = PTR_ERR(drv_device);
        goto destroy_class;
    }

    pr_info("Generic char driver loaded\n");
    return 0;

destroy_class:
    class_destroy(drv_class);
del_cdev:
    cdev_del(&drv_cdev);
unregister:
    unregister_chrdev_region(dev_num, 1);
    return ret;
}

static void __exit generic_driver_exit(void) {
    device_destroy(drv_class, dev_num);
    class_destroy(drv_class);
    cdev_del(&drv_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("Generic char driver unloaded\n");
}

module_init(generic_driver_init);
module_exit(generic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Reusable character driver skeleton");
MODULE_VERSION("1.0");
