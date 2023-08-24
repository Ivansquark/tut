#include "start.h"
#include "sum.h"

int main(int argc, char** argv) {
    Start start;
    start.print();
    start.~Start();
    Sum<int> sum(10,15);
    sum.printSum();
    //argc=0;
    argv++;
    return argc;
}
