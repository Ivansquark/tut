CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/misc
TARGET = opa_printk

obj-m := $(TARGET).o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean: 
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *.symvers *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions
#.PHONY = all, clean
#SRC = src/
#INC = inc/
#BLD = build/
#CPP = g++
#CFLAGS = -Wall -g3 -O0 -ffunction-sections -fdata-sections -std=c++17
#LFLAGS = -Xlinker -Map=$(BLD)main.map -Xlinker --gc-sections
#all: $(BLD)main.elf
#$(BLD)main.elf: $(BLD)main.o
#	$(CPP) -o $@ $^ $(LFLAGS)
#$(BLD)%.o: $(SRC)%.cpp
#	$(CPP) -c $< -o $@ -I$(INC) $(CFLAGS)
#clean:
#	rm -rf build
#	mkdir build

# @ - target name
# ^ - all dependancies names
# < - first dependancy name
# $? — all dependancies names, thats newer than target
# %	- template for all files
	
