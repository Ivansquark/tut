#ifndef TEST_OBSERVER
#define TEST_OBSERVER

#include "o.h"
#include "obs.h"
#include "static_observer.h"
#include <bitset>

template <unsigned long N>
void printBitset(std::bitset<N> const& bs) {
    std::cout << bs.template to_string<char, std::char_traits<char>,
                                       std::allocator<char>>()
              << std::endl;
}

void foo() { ObserverManager::call(1); }

void bar1() { SubManager::call(0); }
class ObjTest1 {
  public:
    static void run() { std::cout << "objTest1" << std::endl; }
};
class ObjTest2 {
  public:
    static void run() { std::cout << "objTest2" << std::endl; }
};
class Obj1 : public ObjVirt {
  public:
    void run() override { std::cout << "Obj1.run" << std::endl; }
};
class Obj2 : public ObjVirt {
  public:
    void run() override { std::cout << "Obj2.run" << std::endl; }
};
void bar2() { SubManVirt::call(1); }

void callAll(int i) {call(i);}
void cfunc1() {std::cout << "cfunc1" << std::endl;}
void cfunc2() {std::cout << "cfunc2" << std::endl;}

TEST(TestGroupName, test_iterator) {
    std::bitset<1> bs;
    printBitset<1>(bs);

    Observer<1, Test1, Test2> obs1;
    foo();

    Obs<0, ObjTest1, ObjTest2> o;
    bar1();
    // EXPECT_EQ(x,2);
    ObsVirt obs(1);
    Obj1 obj1;
    Obj2 obj2;
    obs.addObj(&obj1);
    obs.addObj(&obj2);
    bar2();
    addFunctions(cfunc1);
    addFunctions(cfunc2);
    addHandler(1, callFunctions);
    callAll(1);
}

#endif // TEST_OBSERVER
