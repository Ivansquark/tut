.PHONY: all, clean

#CC = /bin/arm-linux-gnueabihf-gcc-11
#CPP = /bin/arm-linux-gnueabihf-g++-11
CC = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CPP = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
LD = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ld
AS = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-as
OBJ =  ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-objdump


CPPFLAGS = -Wall -Werror -g3 -O0
LFLAGS = -static -Xlinker -Map=$(BLD)/main.map #-L~/raspberrypi/i686_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/lib/ \
		 -L/home/debian/raspberrypi/sysroot/

SRC = src/
INC = -Iinc/
BLD = build/

all: $(BLD)main.elf

$(BLD)main.elf: $(BLD)main.o
	$(CC) -o $@ $^ $(LFLAGS)
	#$(OBJ) -D $(BLD)main.elf > $(BLD)main.list
	
$(BLD)%.o: $(SRC)%.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS) $(INC)

clean:
	rm -Rf build/
	mkdir build



