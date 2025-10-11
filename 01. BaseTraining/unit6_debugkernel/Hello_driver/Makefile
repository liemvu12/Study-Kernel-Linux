obj-m += HelloWorld.o

KDIR := /home/liemvt/work/unit6/linux
PWD  := $(shell pwd)

ARCH := arm     
CROSS_COMPILE := /home/liemvt/work/unit6/gcc-arm-linux/bin/arm-linux-gnueabihf-  

all:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	make -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
