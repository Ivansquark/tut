#ifndef ITER_H
#define ITER_H

#include "arr.h"
#include "moveval.h"
#include "print.h"
#include "sfinae.h"
#include <cassert>
#include <gtest/gtest.h>
#include <memory>

TEST(TestGroupName, test_iterator) {
    const int x = 1;
    // static_assert(x != 0, "Failed");
    assert(x == 0);
    //Arr<std::string, 5> b{"a", "b"};
    Arr<std::string, 5> b{{'a', 'b'}};
    //Arr<std::string, 4> b{"opa"};
    //Arr<int, 4> b{1,2,3};
    //Arr<std::string, 4> b("opa");
    // std::array<std::string, 1> b{"a"};
    // auto tmp = std::make_unique<Arr<std::string, 5>>{"opa", "j", "u"};
    // auto a = *tmp.get();
    auto a = b;
    // auto tmp = new Arr<int, 5>();
    // auto a = *tmp;
    auto beg = a.begin();
    auto end = a.end();
    print(b[0]);
    //std::cout << a[0] << std::endl;
    // int counter = 0;
    // for (auto& i : a) {
    //     i = counter++;
    // }
    std::cout << *(beg) << std::endl;
    // print(*end);
    std::advance(beg, 1);
    // print(std::distance(beg, --end));
    print(*beg);
    // EXPECT_EQ(x,2);
}

#endif // ITER_H
