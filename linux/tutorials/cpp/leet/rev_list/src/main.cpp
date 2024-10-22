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
    reverse_list(&top);
    //reverse_list_recursive(&top);
    printList(top);
    freeList(top);
    return 0;
}
