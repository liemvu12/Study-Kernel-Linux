obj-m += gpio_BBB_ioctl.o

KDIR := /home/liemvt/work/unit6/linux
PWD  := $(shell pwd)

ARCH := arm
CROSS_COMPILE := /home/liemvt/work/unit6/gcc-arm-linux/bin/arm-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc

all:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	$(CC) user_space.c -o user_space

clean:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
	$(RM) user_space
