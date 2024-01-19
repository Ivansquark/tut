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
    MyF my(1);
    const MyF my0 = MyF((MyF(my))); // no optimization in this case
    // const MyF my0 = MyF(move(MyF(my))); // no optimization in this case
    MyF my1 = move(my);
    MyF my2 = move(my0);
    my1 = move(my2);
    // Act
    // Assert
    // EXPECT_EQ(my.getI(), 1);
}

#endif //FORWARD
