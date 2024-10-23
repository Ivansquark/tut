.PHONY = ALL, clean

CC = gcc
CPP = g++

CPPFLAGS = -Wall -g -O0 -Wpedantic
LFLAGS = -fPIC -Xlinker -Map=$(BLD)main.map

SRC = src/
INC = -Iinc/
BLD = build/

ALL: $(BLD)main.elf

$(BLD)main.elf: $(BLD)main.o
	$(CPP) -o $@ $^ $(LFLAGS)

$(BLD)%.o: $(SRC)%.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS) $(INC)


clean:
	rm -rf build
	cd build
