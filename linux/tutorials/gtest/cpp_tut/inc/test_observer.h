#ifndef TEST_OBSERVER
#define TEST_OBSERVER

#include "static_observer.h"
#include <bitset>

void foo() { ObserverManager::call(1); }
template <unsigned long N>
void printBitset(std::bitset<N> const& bs) {
    std::cout << bs.template to_string<char, std::char_traits<char>,
                                       std::allocator<char>>();
}
TEST(TestGroupName, test_iterator) {

    Observer<1, Test1, Test2> obs1;
    foo();
    std::bitset<1> bs;
    printBitset<1>(bs);
    // EXPECT_EQ(x,2);
}

#endif // TEST_OBSERVER
