#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template <int N = 10>
struct Queue {
    int writeIndex = 0;
    int readIndex = 0;
    Queue() {v.reserve(N);}
    ~Queue() {v.clear();}
    vector<int> v;
    int push(int x){
        if(v.size() >= N) {
            return 0;
        }
        v.push_back(x);
        return 1;
    }
    int pop(int* ret) {
        if(!v.size()) {
            return 0;
        }
        *ret = v[0];
        vector<int> tmp(v.begin() + 1, v.end());
        v = std::move(tmp);
        return 1;
    }
    void print() {
        for(size_t i = 0; i < v.size(); ++i) {
            Print::print(v[i]);
        }
    }
};

#endif // LEET1_H
