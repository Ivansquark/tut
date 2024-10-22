#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode Node;

void init_top(Node** top, int val) {
    if (*top) return;
    // top = (Node*)calloc(1, sizeof(Node));
    *top = (Node*)malloc(sizeof(Node));
    (*top)->next = NULL;
    (*top)->val = val;
}

void push(Node* top, int val) {
    if (!top) return;
    Node* tmp = top;
    while (tmp->next) {
        tmp = tmp->next;
    }
    // tmp->next = (Node*)calloc(1, sizeof(Node));
    tmp->next = (Node*)malloc(sizeof(Node));
    tmp->next->next = NULL;
    tmp->next->val = val;
}

int pop(Node* top) {
    if (!top) return -1;
    Node* tmp = top;
    Node* prev = top;
    while (tmp->next) {
        prev = tmp;
        tmp = tmp->next;
    }
    int ret = tmp->val;
    free(prev->next);
    prev->next = NULL;
    // free(tmp);
    // tmp = NULL;
    return ret;
}

void freeList(Node* top) {
    if (!top) return;
    Node* tmp = top;
    Node* prev = top;
    while (tmp->next) {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
}

void printList(const Node* top) {
    if (!top) return;
    const Node* tmp = top;
    while (tmp->next) {
        Print::print(tmp->val);
        tmp = tmp->next;
    }
    Print::print(tmp->val);
}

Node* reverse_list(Node** top) {
    if (!*top || !(*top)->next) return *top;
    Node* next = NULL;
    Node* prev = NULL;
    Node* curr = *top;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *top = prev;
    return prev;
}

Node* reverse_list_recursive(Node** top) {
    if (!*top ) return NULL;
    if(!(*top)->next) return *top;
    Node* tmp = reverse_list_recursive(&(*top)->next);
    //(*top)->next->next = *top;
    //(*top)->next = NULL;
    return tmp;
}

#endif // LEET1_H
