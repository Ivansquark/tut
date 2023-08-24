#include "start.h"
#include "sum.h"
#include <iostream>	

int main(int argc, char** argv) {
    Start start;
    start.print();
    double dub=0;
	std::cout<< "hello" << std::endl;
    	printf("hello world!!!");
	printf("OPA");
	Sum<int> sum(5,6);
	sum.print();    
    uint8_t data = 0x56;
    bool and2 = data & 2;
    bool and4 = data & 4;
    std::cout << "and2 = "<< and2 << "\t" << "and4 = " << and4 << std::endl;
	return 0;
}
