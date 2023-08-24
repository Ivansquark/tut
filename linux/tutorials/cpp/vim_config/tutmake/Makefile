.PHONY: all, clean

CC = gcc
CPP = g++
LD = g++
OBJD = objdump
OBJC = objcopy

CPPFLAGS = -Wall -Werror -Wextra -g3 -O0
LDFLAGS = -Xlinker -Map=$(BLD)main.map -pie  
BLD = build/
SRC = src/
INC = inc/

all: $(BLD)main.out

#$(BLD)main.out: $(BLD)main.o $(BLD)start.o $(BLD)sum.o
#	$(LD) -o $(BLD)main.out $(BLD)main.o $(BLD)start.o $(BLD)sum.o $(LDFLAGS)

#$(BLD)main.o: $(BLD)main.S
#	$(CPP) -c $(BLD)main.S -o $(BLD)main.o -I$(INC) $(CPPFLAGS)
#$(BLD)main.S: $(BLD)main.i
#	$(CPP) -S $(BLD)main.i -o $(BLD)main.S -I$(INC)
#$(BLD)main.i: $(SRC)main.cpp
#	$(CPP) -E $(SRC)main.cpp > $(BLD)main.i -I$(INC)

#$(BLD)start.o: $(SRC)start.cpp
#	$(CPP) -c $(SRC)start.cpp -o $(BLD)start.o -I$(INC) $(CPPFLAGS)
#	$(OBJD) -D $(BLD)start.o >> $(BLD)start.lst
#$(BLD)sum.o: $(SRC)sum.cpp
#	$(CPP) -c $(SRC)sum.cpp -o $(BLD)sum.o -I$(INC) $(CPPFLAGS)

$(BLD)main.out: $(BLD)main.o $(BLD)start.o $(BLD)sum.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(BLD)%.o: $(SRC)%.cpp 
	$(CPP) -c $< -o $@ -I$(INC) $(CPPFLAGS)


clean:
	rm -Rf build/
	mkdir build


#    $@ — target name
#    $< — first dependancy name
#    $? — all dependancies names, thats newer than target
#    $^ — all dependencies names of the target
#	 %	- template for all files		

