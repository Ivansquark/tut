#pragma once

#include <iostream>

template <typename T>
class Sum {
public:
    Sum(T a = 0, T b =0);
    void print();
private:
    T a;
    T b;
    T sum;
};
