#pragma once
#include <cstdio>

template <typename T>
class Sum {
public:
    Sum(T x=0, T y=0);
    ~Sum();
    void printSum();
    void sum();
private:
    T first = 0;
    T second = 0;
    T result = 0;    
};
