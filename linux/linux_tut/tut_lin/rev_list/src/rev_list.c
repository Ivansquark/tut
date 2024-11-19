#include "rev_list.h"

#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

char buf[1024] = {0};

int main() {
    List* head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    print_list(&head);
    rev(&head);
    print_list(&head);
    return 0;
}

void print_list(List** head) {
    List* cur = *head;
    while(cur) {
        printf("int = %d\n", cur->val);
        cur = cur->next;
    }
}
