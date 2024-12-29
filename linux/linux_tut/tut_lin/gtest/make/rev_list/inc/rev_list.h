#ifndef REV_LIST_H
#define REV_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct list {
    int val;
    struct list* next;
} List;

void print_list(List** head);
int push(List** head, int v) {
    if (!*head) {
        List* p = (List*)calloc(1, sizeof(List));
        if (!p) return -1;
        p->val = v;
        *head = p;
        (*head)->next = NULL;
        return 0;
    }
    if (!(*head)->next) {
        List* p = (List*)calloc(1, sizeof(List));
        if (!p) return -1;
        p->val = v;
        (*head)->next = p;
        return 0;
    }
    List* curr = *head;
    List* prev = NULL;
    while (curr) {
        prev = curr;
        curr = curr->next;
    }
    List* p = (List*)calloc(1, sizeof(struct list*));
    if (!p) return -1;
    curr = p;
    prev->next = curr;
    curr->val = v;
    //curr->next = NULL;
    return 0;
}

List* rev(List** head) {
    List* prev = NULL;
    List* curr = *head;
    List* next = NULL;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
    return prev;
}

#endif
