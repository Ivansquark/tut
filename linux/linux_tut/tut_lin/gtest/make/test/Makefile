.PHONY: all clean rebuild

PROJ = gtest

CC = $(GCC_PATH)gcc
CXX = $(GCC_PATH)g++
AR = $(GCC_PATH)ar

BLD = build/
SRC = src/
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
inc = -Iinc/ -I/usr/include -I/usr/src/gtest -I{GTEST_HEADERS}
GTEST_SRC = /usr/src/gtest/src
GTEST_DIR = /usr/src/gtest

OPTIMIZATION := 0
CFLAGS = -O$(OPTIMIZATION) -g -Wall -Wextra -fpic -pthread
LFLAGS := -fpie -lpthread

#    $@ — target name
#    $< — first dependancy name
#    $? — all dependancies names, thats newer than target
#    $^ — all dependencies names of the target
#	 %	- template for all files

#___________________ OBJECTS & DEPENDENCIES ____________________________
CXXSRC = $(wildcard ${SRC}*.cpp)
CXXOBJ := $(addprefix $(BLD),$(CXXSRC:.cpp=.o))
DEPS_CXX = $(CXXOBJ:.o=.d)

CSRC = $(wildcard $(SRC)*.c)
COBJ := $(addprefix $(BLD),$(CSRC:.c=.o))
DEPS_C = $(COBJ:.o=.d)

all: ${BLD}${PROJ}.elf

${BLD}${PROJ}.elf: ${COBJ} $(CXXOBJ) $(BLD)gtest_main.a $(BLD)gtest.a
	$(CXX) $^ -o $@ ${LFLAGS}

#___________________ BUILD __________________________________	
$(COBJ) : $(BLD)%.o : %.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(inc)
$(DEPS_C) : $(BLD)%.d : %.c
	mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) $(inc)  > $@
$(CXXOBJ) : $(BLD)%.o : %.cpp
	mkdir -p $(@D)
	echo 'make main.cpp'
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(inc)
$(DEPS_CXX) : $(BLD)%.d : %.cpp
	mkdir -p $(@D)
	$(CXX) -E $(CXXFLAGS) $< -MM -MT $(@:.d=.o) $(inc) > $@
#--------------------  Gtests ------------------------------------------
$(BLD)gtest-all.o : $(GTEST_SRCS_)
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            -o $@ $(GTEST_DIR)/src/gtest-all.cc

$(BLD)gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            -o $@ $(GTEST_DIR)/src/gtest_main.cc

$(BLD)gtest.a : $(BLD)gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(BLD)gtest_main.a : $(BLD)gtest-all.o $(BLD)gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


# find headers dependencies
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS_C)
include $(DEPS_CXX)
endif

clean:
	rm -R build/src
	rm ${PROJECT}.elf

rebuild:
	rm -R build
