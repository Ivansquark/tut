#ifndef TEST_STACK_H
#define TEST_STACK_H

#include "print.h"
#include "stack.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(TestGroupName, test_stack) {
    // Arrange
    // std::static_assert((2 + 2 == 5), ("opa"));
    // const int i = 0;
    // assert(i == 1.5);
    Heavy<double> h(1.5);
    Heavy<double> d(1.6);
    Stack<Heavy<double>> stack;
    stack.push(h);
    stack.push(std::move(h));
    stack.emplace(d);
    //stack.emplace(std::move(h)); //runtime error
    //stack.emplace(1.7); // no additional copy
    //stack.emplace(7.5);
    print(stack.size());
    print(*stack.pop());
    print(*stack.pop());
    print(stack.size());
    EXPECT_EQ(*stack.pop(), 1.5);
}

#endif // TEST_STACK_H
