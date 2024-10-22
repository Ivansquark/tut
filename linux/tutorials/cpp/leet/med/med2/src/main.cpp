#include "leet2.h"
#include "print.h"

#include <stdint.h>


using namespace Print;

int main() {
    List l1;
    l1.push_back(5);
    l1.push_back(4);
    l1.push_back(9);
    l1.print();
    print();
    List l2;
    l2.push_back(5);
    l2.push_back(6);
    l2.push_back(4);
    l2.push_back(9);
    l2.print();
    print();
    Sol2 s;
    List l3 = s.addTwoNumbers(l1, l2);
    l3.print();
    //freeList(l3.first);
    return 0;
}
