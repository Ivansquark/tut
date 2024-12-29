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
    List head;
    head.val = 0;
    head.next = NULL;
    List head1;
    head1.val = 2;
    head1.next = NULL;
    push(&head, 1);
    push(&head, 5);
    push(&head, 10);
    push(&head, 24);
    push(&head1, 3);
    push(&head1, 7);
    push(&head1, 14);
    print_list(&head);
    print_list(&head1);
    //List new_head = *rev(&head);
    printf("____ reverse ____\n");
    List merge = *merge_l(&head, &head1);
    printf("____ merge ____\n");
    print_list(&merge);
    printf("____ merge1 ____\n");
    print_list(&head);
    printf("____ merge2 ____\n");
    print_list(&head1);
    return 0;
}
