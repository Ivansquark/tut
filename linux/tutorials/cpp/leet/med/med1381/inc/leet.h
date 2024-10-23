#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class CustomStack {
  public:
    CustomStack(int maxSize) {
        size = maxSize;
        stack.reserve(size);
    }

    void push(int x) {
        if (stack.size() < size) {
            stack.emplace_back(x);
        }
    }

    int pop() {
        if (stack.size()) {
            int i = stack[stack.size() - 1];
            stack.pop_back();
            return i;
        } else {
            return -1;
        }
    }

    void increment(int k, int val) {
        int sz = (k < stack.size()) ? k : stack.size();
        for (int i = 0; i < sz; i++) {
            stack[i] += val;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const CustomStack& st);

  private:
    int size;
    std::vector<int> stack;
};

std::ostream& operator<<(std::ostream& os, const CustomStack& st) {
    for (int i = 0; i < st.stack.size(); ++i) {
        os << st.stack[i] << " ";
    }
    return os;
}

// 1381
// Input
//["CustomStack","push","push","pop","push","push","push","increment",
//       "increment","pop","pop","pop","pop"]
//[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
// Output
//[null,null,null,2,null,null,null,null,null,103,202,201,-1]
// Explanation
// CustomStack stk = new CustomStack(3); // Stack is Empty []
// stk.push(1);                          // stack becomes [1]
// stk.push(2);                          // stack becomes [1, 2]
// stk.pop();             // return 2 --> Return top of the stack 2, stack [1]
// stk.push(2);                          // stack becomes [1, 2]
// stk.push(3);                          // stack becomes [1, 2, 3]
// stk.push(4); // stack still [1, 2, 3], Do not add elements as size is 4
// stk.increment(5, 100);                // stack becomes [101, 102, 103]
// stk.increment(2, 100);                // stack becomes [201, 202, 103]
// stk.pop(); // return 103 --> Return top 103, stack becomes [201, 202]
// stk.pop(); // return 202 --> Return top of the stack 202, stack becomes [201]
// stk.pop(); // return 201 --> Return top of the stack 201, stack becomes []
// stk.pop(); // return -1 --> Stack is empty return -1.
#endif // LEET1_H
