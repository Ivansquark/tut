#ifndef MOVE_H
#define MOVE_H

#include "print.h"
#include "sfinae.h"
#include <gtest/gtest.h>
#include <iostream>

class MyM {
  public:
    MyM() { print("default ctor"); }
    explicit MyM(int i) : num(new int(i)) {
        print("default numeric ctor", *num);
    };
    ~MyM() {
        delete num;
        print("destructor");
    }
    MyM(const MyM& my) { print("copy ctor"); }
    MyM(MyM&& my) { print("move ctor"); }
    MyM(const MyM&& my) { print("const move ctor"); }
    MyM& operator=(const MyM&) {
        print("operator = &");
        return *this;
    }
    MyM& operator=(MyM&&) {
        print("operator = &&");
        return *this;
    }
    int getI() { return *num; }

  private:
    int* num = nullptr;
};

TEST(TestGroupName, test_move) {
    // Arrange
    MyM my(1);
    const MyM my0 = MyM((MyM(my))); // no optimization in this case
    // const MyM my0 = MyM(move(MyM(my))); // no optimization in this case
    MyM my1 = move(my);
    MyM my2 = move(my0);
    my1 = move(my2);
    // Act
    // Assert
    // EXPECT_EQ(my.getI(), 1);
}

#endif // MOVE_H
