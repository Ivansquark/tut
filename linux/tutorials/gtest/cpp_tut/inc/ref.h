#ifndef REF_H
#define REF_H

#include "moveval.h"
#include "print.h"
#include "sfinae.h"
#include <gtest/gtest.h>

MoveVal<int> x = 31;
MoveVal<int>* ptrX = &x;
MoveVal<int>& lrefX = x;
const MoveVal<int>& clrefX = std::move(x);
MoveVal<int>&& rrefX = std::move(x);
const MoveVal<int>&& crrefX = std::move(x);

TEST(TestGroupName, test_decay) {
    // Arrange
    print("&x=", &x, " &ptrX=", &ptrX, " &lrefX=", &lrefX,
          " &clrefX=", &clrefX);
    print("&rrefX=", &rrefX, " &crrefX=", &crrefX);
    // rrefX += "o";
    MoveVal<int> intMove = std::move(x);
    print(std::move(intMove));
    MoveVal<std::string> str = std::string("opa");
    MoveVal<std::string> str1 = std::string("---");
    str1 = std::move(str);
    print(std::move(str1));
    print(std::ref(str));
    // print(str1);
}

#endif // REF_H
