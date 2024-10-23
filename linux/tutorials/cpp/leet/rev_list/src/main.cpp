#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    Node* top = NULL;

    init_top(&top, 1);
    push(top, 2);
    push(top, 3);
    push(top, 4);
    push(top, 5);
    // reverse_list(&top);
    reverse(&top);
    // reverse_list_recursive(&top);
    printList(top);
    freeList(top);

    int x[] = {1, 2};
    //auto ret = [](int* x) { return x[0]; };
    //ret(x);
    //print("ret", ret);
    return 0;
}
