#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define GPIO_IOC_MAGIC     'G'
#define GPIO_IOC_SET_DIR   _IOW(GPIO_IOC_MAGIC, 0, int)
#define GPIO_IOC_WRITE     _IOW(GPIO_IOC_MAGIC, 1, int)
#define GPIO_IOC_READ      _IOR(GPIO_IOC_MAGIC, 2, int)

int main() {
    int fd = open("/dev/gpio_dev", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int dir = 1;
    ioctl(fd, GPIO_IOC_SET_DIR, &dir); // set output

    int val = 1;
    ioctl(fd, GPIO_IOC_WRITE, &val);   // set high

    sleep(1);

    val = 0;
    ioctl(fd, GPIO_IOC_WRITE, &val);   // set low

    dir = 0;
    ioctl(fd, GPIO_IOC_SET_DIR, &dir); // set input

    ioctl(fd, GPIO_IOC_READ, &val);
    printf("Input value: %d\n", val);

    close(fd);
    return 0;
}
