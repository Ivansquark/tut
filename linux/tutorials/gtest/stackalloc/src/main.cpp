#include <gtest/gtest.h>

#include <cstdio>
#include <limits>
#include <list>
#include <memory>
#include <vector>

#include "stackalloc.h"

constexpr int VSZ = 10;
constexpr int BUFSZ = 24;

using sString = std::basic_string<char, std::char_traits<char>,
                                  stack_alloc<char, BUFSZ, alignof(long int)>>;
TEST(allocs, stackalloc) {
    // sString str1("012345678901234");
    // std::string str("0123456789012345678901234opaa");
    // sString str("0123456789012345678901234opaa");
    sString str("0123456789012345");
    // sString str2("0123456789012345");
    // print(str, std::addressof(str));
    // std::cout << "Pointer str = " << (int*)&str[0] << std::endl;
    // print(str2, std::addressof(str2));
    // std::cout << "Pointer str2 = " << (int*)&str2[0] << std::endl;
    // str2 = str;
    // sString sss{std::forward<sString>(str)};
    {
        sString sss{std::forward<sString>(str)};
        // sString sss{(str)};
        // sString sss;
        // sss = {std::move(str)};
        std::cout << "Pointer sss = " << (int*)&sss.data()[0] << std::endl;
    }
    std::cout << "Pointer str = " << (int*)&str.data()[0] << std::endl;
    // str = std::forward<sString>(str2);

    // reverse(str.begin(), str.end());
    // sString sum = str + str2;
    // std::cout << "Pointer sum = " << (int*)&sum.data()[0] << std::endl;
    // std::for_each(sum.begin(), sum.end(), [](char& i){i--;});
    //  str = std::move(str2);
    // print(str, std::addressof(str));
    // print(str2, std::addressof(str2));
    // std::cout << "Pointer str = " << (int*)&str.data()[0] << std::endl;
    // std::cout << "Pointer str2 = " << (int*)&str2.data()[0] << std::endl;

    // std::string sa = "Was the stringaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    // sString sb(std::move(str2));
    // sString sd ("ooo");
    // sd = std::move(str);
    // str2 = sd;
    // str2 = (std::move(sd));
    // std::string sb;
    // sb = (std::move(str2));
    // std::cout << "Size str2 = " << str2.size() << std::endl;
    // std::cout << "Size sb = " << sb.size() << std::endl;
    // std::cout << "Pointer str2 = " << (int*)&str2.data()[0] << std::endl;
    // std::cout << "Pointer sb = " << (int*)&str2.data()[0] << std::endl;
    // std::cout << "Old [" << sb << "] new [" << str2 << "]" << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
