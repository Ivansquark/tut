#ifndef FORWARD
#define FORWARD

#include "sfinae.h"
#include "print.h"

class MyF {
  public:
    MyF() { print("default ctor"); }
    explicit MyF(int i) : num(new int(i)) {
        print("default numeric ctor", *num);
    };
    ~MyF() {
        delete num;
        print("destructor");
    }
    MyF(const MyF& my) { print("copy ctor"); }
    MyF(MyF&& my) { print("move ctor"); }
    MyF(const MyF&& my) { print("const move ctor"); }
    MyF& operator=(const MyF&) {
        print("operator = &");
        return *this;
    }
    MyF& operator=(MyF&&) {
        print("operator = &&");
        return *this;
    }
    int getI() { return *num; }

  private:
    int* num = nullptr;
};

TEST(TestGroupName, test_move) {
    // Arrange
    int x = 0;
    MyF my(1);
    MyF my_lvalue_but_type_deduction_is_rvalue = forward<MyF>(my);
    MyF my_lvalue_ref = forward<MyF&>(my);
    MyF my_rvaalue_ref = forward<MyF&&>(my);
    //MyF my2 = MyF(forward<int&&>(x+1));
    my = forward<MyF>(my);
    my = forward<MyF&>(my);
    my = forward<MyF&&>(my);
    // Act
    // Assert
    EXPECT_EQ(my.getI(), 1);
}

#endif //FORWARD
