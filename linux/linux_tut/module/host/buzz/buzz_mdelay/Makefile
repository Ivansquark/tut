.PHONY = all, clean
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/misc
TARGET = buzz

obj-m := $(TARGET).o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean: 
	@rm -f *.o *.ko *.mod .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *.symvers *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions


# @ - target name
# ^ - all dependancies names
# < - first dependancy name
# $? — all dependancies names, thats newer than target
# %	- template for all files
	
