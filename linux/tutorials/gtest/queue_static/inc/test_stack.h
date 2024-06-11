#ifndef TEST_STACK_H
#define TEST_STACK_H

#include "print.h"
#include "stack.h"
#include <cassert>
#include <gtest/gtest.h>

template <typename... Args>
void pr(Args&&... args) {
    ((std::cout << "pr: " << std::forward<Args>(args) << " "), ...,
     (std::cout << std::endl));
}

TEST(TestGroupName, test_stack) {
    pr("Test", "stack");
    // Arrange
    // std::static_assert((2 + 2 == 5), ("opa"));
    // const int i = 0;
    // assert(i == 1.5);
    Heavy<double> h(1.5);
    Heavy<double> d(1.6);
    Stack<Heavy<double>> stack;
    //stack.push(h);
    stack.push(12);

    //stack.push(std::move(h));
    //stack.emplace(d);
    // stack.emplace(std::move(h)); //runtime error
    stack.emplace(1.7); // no additional copy
    //stack.emplace(7.5);
    print(stack.size());
    print(*stack.pop());
    print(*stack.pop());
    print(stack.size());
    double res = *stack.pop();
    print(res);
    EXPECT_EQ(res, 1.5);
}

#endif // TEST_STACK_H
