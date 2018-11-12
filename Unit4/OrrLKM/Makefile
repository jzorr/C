obj-m += OrrLKM.o
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod OrrLKM.ko
	sudo rmmod OrrLKM.ko
	dmesg

