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
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;
        ListNode* slow = head->next;
        ListNode* fast = head;
        if (fast->next->next) {
            fast = fast->next->next;
        } else {
            return false;
        }
        while (fast->next) {
            if (fast == slow) return true;
            slow = slow->next;
            if (fast->next->next) {
                fast = fast->next->next;
            } else {
                return false;
            }
        }
        return false;
    }
};
#endif // LEET1_H
