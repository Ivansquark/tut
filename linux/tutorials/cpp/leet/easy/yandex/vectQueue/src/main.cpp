#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    Queue circ;

    circ.push(1);
    circ.push(2);
    circ.push(3);
    circ.push(4);
    circ.push(5);
    circ.push(6);
    circ.push(7);
    circ.push(8);
    circ.push(9);
    circ.push(10);
    circ.push(11);

    circ.print();
    print("\r");
    int ret = 0;
    print(circ.pop(&ret));
    print(ret);
    print(circ.pop(&ret));
    print(ret);
    print(circ.pop(&ret));
    print(ret);
    circ.push(13);
    circ.push(14);
    print("\r");
    circ.print();

    return 0;
}
