#ifndef LEET2_H
#define LEET2_H

#include "print.h"

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct List {
  public:
    List() : first(nullptr) {}
    List(ListNode* node) : first(node) {}
    ListNode* first = nullptr;
    virtual ~List() {
        if (!first) {
            return;
        }
        ListNode* l = first;
        while (l) {
            ListNode* prev = l;
            l = l->next;
            delete (prev);
        }
    }
    operator ListNode*() const { return first; }
    void push_back(int x) {
        if (!first) {
            first = new ListNode(x);
        } else {
            ListNode* l = first;
            while (l->next) {
                l = l->next;
            }
            l->next = new ListNode(x);
        }
    }
    void print() {
        if (!first) return;
        ListNode* l = first;
        Print::print(l->val);
        while (l->next) {
            l = l->next;
            Print::print(l->val);
        }
    }
};

class Sol2 {
  public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* listCurr = nullptr;
        ListNode* listPrev = nullptr;
        ListNode* top = nullptr;
        int carry = 0;
        while (1) {
            int val1 = (l1) ? (l1->val) : 0;
            int val2 = (l2) ? (l2->val) : 0;

            int sum = val1 + val2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            if (!top) {
                top = new ListNode(digit);
            } else if(!listPrev) {
                listPrev = new ListNode(digit);
                top->next = listPrev;
                listCurr = listPrev;
            } else {
                listCurr->next = new ListNode(digit);
                listCurr = listCurr->next;
            }

            if (l1) {
                l1 = (l1->next) ? l1->next : nullptr;
            }
            if (l2) {
                l2 = (l2->next) ? l2->next : nullptr;
            }
            if (!l1 && !l2) break;
        }
        if (carry) {
            listCurr->next = new ListNode(carry);
        }
        return top;
    }
};

void freeList(ListNode* top) {
    ListNode* tmp = top;
    if (!top) return;
    if (!top->next) {
        delete top;
        return;
    }
    while (top) {
        tmp = top;
        top = top->next;
        // if(top)
        delete tmp;
    }
}

#endif // LEET2_H
