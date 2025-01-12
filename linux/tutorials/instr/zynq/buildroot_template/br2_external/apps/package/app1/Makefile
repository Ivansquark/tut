.PHONY: all, clean

SRC = src/
INC = inc/
BLD = build/

inc := -I$(INC)

OPTIMIZATION = 0
#OPTIMIZATION = s

CXXFLAGS += -g -O$(OPTIMIZATION)

all: $(BLD)app1.elf

$(BLD)app1.elf: $(BLD)main.o
	$(CXX) -o $(BLD)app1.elf $(BLD)main.o $(LFLAGS)

$(BLD)main.o: $(SRC)main.cpp
	mkdir -p build
	#$(CXX) $(CXXFLAGS) -c $< -o $@ $(inc)
	$(CXX) -c $(SRC)main.cpp -o $(BLD)main.o $(CXXFLAGS) $(inc)

clean:
	rm -r build


