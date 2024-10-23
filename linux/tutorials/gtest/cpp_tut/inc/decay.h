#pragma once

#include "print.h"
#include "sfinae.h"
#include <gtest/gtest.h>
#include <typeinfo>

// std::decay =:> from int&& to int, int& to int (like simple auto)

template <typename T>
void param(T&& t) {
    // print(type_name<decltype(t)()>); //compile type
    t++;
    if (is_same<typename std::decay<decltype(t)>::type, int&&>::value) {
        print("int&&");
    }  else if (is_same<typename std::decay<decltype(t)>::type, int&>::value) {
        print("int&");
    } else if (is_same<typename std::decay<decltype(t)>::type, int>::value) {
        print("int");
    } else if (is_same<T, const int>::value) {
        print("const int");
    } else {
        print("not int");
    }
}

template <typename T>
std::string type_name();

template <typename T>
void universal_param(T&& t) {
    typename std::decay<decltype(t)>::type temp = t;
    //auto temp = t;
    //decltype(t) temp = std::forward<T>(t);
    // print(type_name<decltype(t)()>); //compile type
    if (std::is_lvalue_reference<decltype(temp)>::value) {
        print("is lvalue reference");
    } else if (std::is_rvalue_reference<decltype(temp)>::value) {
        print("is rvalue reference");
    } else {
        print("is rvalue");
    }
    if (std::is_same<decltype(temp), int&&>::value) {
        print("int&&");
    } else if (std::is_same<decltype(temp), int&>::value) {
        print("int&");
    } else if (std::is_same<decltype(temp), int>::value) {
        print("int");
    } else if (is_same<decltype(temp), const int>::value) {
        print("const int");
    } else if (is_same<decltype(temp), const int&>::value) {
        print("const int&");
    } else if (is_same<decltype(temp), const int&&>::value) {
        print("const int&&");
    }
}

TEST(TestGroupName, test_decay) {
    // Arrange
    int z = 3;
    int& x = z;
    const int&& y = 2;
    //param(std::forward<int>(z));
    //param(z);
    //print(z);
    // universal_param(std::move(y));
    // universal_param(forward<int>(x));
    universal_param(x);
    // universal_param(std::forward<int>(y));
    // universal_param(std::forward<int&>(y));
    // universal_param(std::forward<int&&>(y));
    //  Act
    //  Assert
    //  EXPECT_EQ(my.getI(), 1);
}
