.PHONY: ALL, clean

AS = as
CC = gcc
CPP = g++
LD = ld
OBJD = objdump
OBJC = objcopy
CPPFLAGS = -Wall -Werror -Wpedantic -g -O0
LFLAGS = -lstdc++ -Xlinker -Map=$(BLD)prog.map

SRC = src/
INC = inc/
BLD = build/

ALL: $(BLD)prog.out
$(BLD)prog.out: $(BLD)prog.o $(BLD)start.o $(BLD)sum.o
	$(CC) -o $(BLD)prog.out $^ $(LFLAGS)

#$(BLD)prog.o: $(SRC)prog.cpp
#	$(CC) -c $(SRC)prog.cpp -o $(BLD)prog.o $(CPPFLAGS)
#	$(OBJD) $(BLD)prog.o -D > $(BLD)prog.lst

$(BLD)prog.o: $(BLD)prog.S
	$(CC) -c $(BLD)prog.S -o $(BLD)prog.o -I$(INC) $(CPPFLAGS)
$(BLD)prog.S: $(BLD)prog.i
	$(CPP) -S $(BLD)prog.i -o $(BLD)prog.S -I$(INC) -g
$(BLD)prog.i: $(SRC)prog.cpp
	$(CPP) -E $(SRC)prog.cpp >> $(BLD)prog.i	-I$(INC)	

$(BLD)start.o: $(SRC)start.cpp
	$(CPP) -c $(SRC)start.cpp -o $(BLD)start.o -I$(INC) $(CPPFLAGS)

$(BLD)sum.o: $(SRC)sum.cpp
	$(CPP) -c $< -o $@ -I$(INC) $(CPPFLAGS)

clean:
	rm -Rf build
	mkdir build
