ifneq ($(KERNELRELEASE),)
obj-m := buzz.o
else
KDIR := /home/opa/embedded/fpga/xilinx/zynq/proj/template/kernel
all:
	$(MAKE) -C $(KDIR) \
	M=$$PWD \
    LOCALVERSION= \
	ARCH=arm \
    CROSS_COMPILE=arm-linux-gnueabihf- \
	modules

install:
	$(MAKE) -C $(KDIR) \
	M=$$PWD \
    LOCALVERSION= \
	ARCH=arm \
    CROSS_COMPILE=arm-linux-gnueabihf- \
	INSTALL_MOD_PATH=\
	/home/opa/embedded/fpga/xilinx/zynq/proj/template/rootfs_overlay \
	modules_install

clean:
	rm *.ko *.o *.mod.c .*.cmd *.mod *.order *.symvers

endif
