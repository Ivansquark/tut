#ifndef REV_LIST_H
#define REV_LIST_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct list {
    int val;
    struct list* next;
} List;

void push(List* head, int val) {
    if (!head) {
        List* p = malloc(sizeof(*p));
        p->val = val;
        head = p;
        return;
    }
    List* curr = head;
    List* prev = head;
    while (curr) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = malloc(sizeof(List));
    prev->next->val = val;
}

List* rev(List* head) {
    List* prev = NULL;
    List* curr = head;
    List* next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    // head->val = prev->val;
    // head->next = prev->next;
    return prev;
}

void print_list(List* head) {
    if (!head) return;
    List* curr = head;
    while (curr) {
        char buf[20] = {0};
        sprintf(buf, "val = %d\n", curr->val);
        write(2, buf, strlen(buf));
        curr = curr->next;
    }
}

List* merge_l(List* head1, List* head2) {
    List* curr1 = head1;
    List* curr2 = head2;
    List* ret = NULL;
    List* prev = NULL;
    if (curr1->val < curr2->val) {
        ret = curr1;
        curr1 = curr1->next;
    } else{
        ret = curr2;
        curr2 = curr2->next;
    }
    prev = ret;
    while (curr1 && curr2) {
        if (curr1->val < curr2->val) {
            ret->next = curr1;
            curr1 = curr1->next;
        } else {
            ret->next = curr2;
            curr2 = curr2->next;
        }
        ret = ret->next;
    }
    if (curr1) {
        ret->next = curr1;
    } else if (curr2) {
        ret->next = curr2;
    }
    return prev;
}

#endif
