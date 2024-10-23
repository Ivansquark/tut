#include <gtest/gtest.h>

#include <cstdio>
#include <limits>
#include <list>
#include <memory>
#include <vector>

#include "shortalloc.h"

constexpr int VSZ = 10;
constexpr int BUFSZ = 200;

template <class T, size_t BufSize = BUFSZ>
using SmallVector = std::vector<T, short_alloc<T, BufSize, alignof(T)>>;
using SmallString = std::basic_string<char, std::char_traits<char>,
                                      short_alloc<char, BUFSZ, alignof(int)>>;

TEST(allocs, shortalloc) {
    // we want to check we are allocating everything from arena,
    // not from new. So storing initial to current memory usage.
    SmallVector<int>::allocator_type::arena_type a;
    //SmallVector<int> v{a};

    //for (int i = 0; i < VSZ; ++i) {
    //    v.push_back(i);
    //    // EXPECT_EQ(memuse(), initial);
    //}
    SmallString str("opa",a);
    SmallString sm(std::move(str),a);
    SmallString str1("askoaoskdpasdokaposdkpkaosdkaposdkpadsodapdkspoask"
            "la;sdalsdkasdklads;k;alsdkl;l;adskapdkoadksppokasoapsdkpad",a);
    std::cout << &str << std::endl;
    std::cout << &str1 << std::endl;

    // really we expect much more, since we are not freeing.
    // like for VSZ = 10 we expect: 1 + 2 + 4 + 8 + 16 ints
    // i.e. 31 * 4 = 124 out of 200
    //EXPECT_EQ(a.used() >= VSZ * sizeof(int), true);

    // Yes, the correct values are actually in the vector
    //for (int i = 0; i < VSZ; ++i) EXPECT_EQ(v[i], i);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
