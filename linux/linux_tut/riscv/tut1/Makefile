#    $@ — target name
#    $< — first dependancy name
#    $? — all dependancies names, thats newer than target
#    $^ — all dependencies names of the target
#	 %	- template for all files

.PHONY: all, clean

CPP = /home/debian/embedded/linux/buildroot/output/host/bin/riscv64-linux-g++
CPPFLAGS = -Wall -c -g3 -O0

INC = inc/
SRC = src/
BLD = build/

SRCFILES = $(wildcard $(SRC)*.cpp)
OBJFILES = $(patsubst $(SRC)%.cpp, $(BLD)%.o, $(SRCFILES))

all: $(BLD)main

$(BLD)main: $(OBJFILES)
	$(CPP) $^ -o $@

$(BLD)%.o: $(SRC)%.cpp
	@ # **** mutex for parallel execution (mkdir must be locked) ****
	@if mkdir /var/lock/.myscript.exclusivelock; \
	then if [ ! -d "$(BLD)" ]; then mkdir $(BLD); fi; \
	rmdir /var/lock/.myscript.exclusivelock; \
	fi
	$(CPP) $< -o $@ -I$(INC) $(CPPFLAGS)

clean:
	rm -rf $(BLD)
