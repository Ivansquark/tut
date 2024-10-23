#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>

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
        } else {
            ListNode* l = first;
            while (l->next) {
                ListNode* prev = l;
                l = l->next;
                delete (prev);
            }
            delete (l);
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
        // std::list<int> v1 = get_vec(l1);
        // std::list<int> v2 = get_vec(l2);
        // int sum = getNum(v1) + getNum(v2);

        bool carry = false;
        int temp = l1->val + l2->val;
        ListNode* l = nullptr;
        ListNode* lp = nullptr;
        ListNode* l1p = l1;
        ListNode* l2p = l2;
        if (temp > 9) {
            carry = true;
            l = new ListNode(temp % 10);
            lp = l;
        } else {
            l = new ListNode(temp);
            lp = l;
        }
        while (l1p->next && l2p->next) {
            l1p = l1p->next;
            l2p = l2p->next;
            if (carry) {
                int temp = l1p->val + l2p->val + 1;
                if (temp > 9) {
                    carry = true;
                    lp->next = new ListNode(temp % 10);
                    lp = lp->next;
                } else {
                    carry = false;
                    lp->next = new ListNode(temp);
                    lp = lp->next;
                }
            } else {
                int temp = l1p->val + l2p->val;
                if (temp > 9) {
                    carry = true;
                    lp->next = new ListNode(temp % 10);
                    lp = lp->next;
                } else {
                    carry = false;
                    lp->next = new ListNode(temp);
                    lp = lp->next;
                }
            }
        }
        while (l1p->next) {
            l1p = l1p->next;
            if (carry) {
                int temp = l1p->val + 1;
                if (temp > 9) {
                    carry = true;
                    lp->next = new ListNode(temp % 10);
                    lp = lp->next;
                } else {
                    carry = false;
                    lp->next = new ListNode(temp);
                    lp = lp->next;
                }
            } else {
                int temp = l1p->val;
                lp->next = new ListNode(temp);
                lp = lp->next;
            }
        }
        while (l2p->next) {
            l2p = l2p->next;
            if (carry) {
                int temp = l2p->val + 1;
                if (temp > 9) {
                    carry = true;
                    lp->next = new ListNode(temp % 10);
                    lp = lp->next;
                } else {
                    carry = false;
                    lp->next = new ListNode(temp);
                    lp = lp->next;
                }
            } else {
                int temp = l2p->val;
                lp->next = new ListNode(temp);
                lp = lp->next;
            }
        }
        if (carry) {
            lp->next = new ListNode(1);
        }
        return l;
    }
    ListNode* retList(int n) {
        ListNode* list = nullptr;
        ListNode* listRet = nullptr;
        bool o = false;
        if (!n) {
            listRet = new ListNode(0);
        }
        while (n) {
            int once = n % 10;
            if (!list) {
                list = new ListNode(once);
            } else {
                list->next = new ListNode(once);
                list = list->next;
            }
            if (!o) {
                o = true;
                listRet = list;
            }
            n /= 10;
        }
        return listRet;
    }
    std::list<int> get_vec(ListNode* l) {
        std::list<int> v;
        while (l->next != nullptr) {
            v.emplace_back(l->val);
            l = l->next;
        }
        v.emplace_back(l->val);
        return v;
    }
    int getNum(std::list<int>& v) {
        int num = 0;
        int dec = 1;
        for (auto&& i : v) {
            num += dec * i;
            dec *= 10;
        }
        return num;
    }
};

#endif // LEET1_H
