.PHONY: all, clean

CC = g++

INC = inc/
SRC = src/
BLD = build/

CPPFLAGS = -Wall -Wextra -g -O0
LFLAGS = -lpthread

all: $(BLD)main.elf

$(BLD)main.elf: $(BLD)main.o
	$(CC)   -o $(BLD)main.elf $^ $(LFLAGS)

$(BLD)%.o: $(SRC)%.cpp
	$(CC) -c $< -o $@ -I$(INC) $(CPPFLAGS)

clean:
	rm -rf build
	mkdir build

