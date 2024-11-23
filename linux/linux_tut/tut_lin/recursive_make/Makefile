.PHONY: all clean

PROJ := upver

GCC_PATH = /usr/bin/
CC = $(GCC_PATH)gcc
CXX = $(GCC_PATH)g++
OBJC = $(GCC_PATH)objcopy
OBJD = $(GCC_PATH)objdump
AS = $(GCC_PATH)as
LD = $(GCC_PATH)ld
MAKE = make

INC = inc/
LIB = lib/
BLD = build/
SRC = src/
inc = -I$(INC) -Ireadver/inc/ -Itoup/inc/ -Isharedt/inc/

OPTIMIZATION := 0
CFLAGS = -O$(OPTIMIZATION) -g -Wall -Wextra -fPIE
#LFLAGS := -fPIE -lsharedt -Lsharedt/build/ -Wl,-rpath,shared/build/
LFLAGS := -fPIE -lsharedt -Lbuild/ -Wl,-rpath,build/
#___________________ OBJECTS & DEPENDENCIES ____________________________
CXXSRC = $(wildcard $(SRC)*.cpp)
CXXOBJ := $(addprefix $(BLD),$(CXXSRC:.cpp=.o))
DEPS_CXX = $(CXXOBJ:.o=.d)

CSRC = $(wildcard $(SRC)*.c)
COBJ := $(addprefix $(BLD),$(CSRC:.c=.o)) 
MAKE_OBJ := readver/build/src/readver.o toup/build/src/toup.o
DEPS_C = $(COBJ:.o=.d)
	
all:	$(BLD)${PROJ}.dis $(BLD)${PROJ}.elf

$(BLD)${PROJ}.dis: $(BLD)$(SRC)${PROJ}.o
	$(OBJD) -D $< -M intel > $(BLD)${PROJ}.dis

#------------------------------------  LINKER ---------------------------------
$(BLD)${PROJ}.elf: make-readver make-toup make-sharedt $(COBJ) $(CXXOBJ) 
	$(CC) -o $@ $(COBJ) $(MAKE_OBJ) $(LFLAGS)
#    $@ — target name
#    $< — first dependancy name
#    $? — all dependancies names, thats newer than target
#    $^ — all dependencies names of the target
#	 %	- template for all files
#-------------------------------------- SIZE ----------------------------------	
	@echo "************************************************************"
	@echo "*******************   SIZE   *******************************"
	@echo "************************************************************"
	$(GCC_PATH)size $(BLD)${PROJ}.elf
	@echo "************************************************************"

#___________________ BUILD __________________________________	
$(COBJ) : $(BLD)%.o : %.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(inc)
$(DEPS_C) : $(BLD)%.d : %.c
	mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) $(inc)  > $@
$(CXXOBJ) : $(BLD)%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(inc)
$(DEPS_CXX) : $(BLD)%.d : %.cpp
	mkdir -p $(@D)
	$(CXX) -E $(CXXFLAGS) $< -MM -MT $(@:.d=.o) $(inc) > $@

#______________ RECURSIVE MAKE ________________________________________________
make-readver:
	$(MAKE) -C readver build/src/readver.o
make-toup:
	$(MAKE) -C toup build/src/toup.o
make-sharedt:
	$(MAKE) -C sharedt build/libsharedt.so
	cp sharedt/build/libsharedt.so build/libsharedt.so

# find headers dependencies
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS_C)
include $(DEPS_CXX)
endif

clean:
	rm -rf build 
	rm -rf toup/build
	rm -rf readver/build
	rm -rf sharedt/build

