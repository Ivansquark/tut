.PHONY: all, clean

#CC = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CC = /bin/arm-linux-gnueabihf-gcc-11
CPP = g++
#CPP = arm-linux-gnueabihf-g++
#CPP = aarch64-linux-gnu-g++-11
#CPP = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++

LD = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ld
AS = ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-as
OBJ =  ~/raspberrypi/i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-objdump


CPPFLAGS = -std=c++17 -Wall -Wpedantic -g3 -O0
LFLAGS = -lpthread -lssl -lcrypto -L/home/opa/pi/sysroot/lib -fPIC -Xlinker -Map=$(BLD)main.map  \
		  #-static

SRC = src/
INC = -Iinc/
BLD = build/

all: $(BLD)main.elf
	

$(BLD)main.elf: $(BLD)main.o $(BLD)tcp.o $(BLD)http_parser.o $(BLD)https.o
	$(CPP) -o $@ $^ $(LFLAGS)
#	$(OBJ) -D $(BLD)main.elf > $(BLD)main.list
	
$(BLD)%.o: $(SRC)%.cpp
	if [ ! -d "build/" ]; then mkdir build;	fi
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(INC)
	
clean:
	rm -Rf build/
