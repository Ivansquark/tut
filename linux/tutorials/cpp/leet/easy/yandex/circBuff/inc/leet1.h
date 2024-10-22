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

using namespace std;

template <int N = 10>
struct CircBuff {
    int writeIndex = 0;
    int readIndex = 0;
    int arr[N] = {0};
    int push(int x){
        if((writeIndex + 1)%N == readIndex) {
            return 0;
        }
        arr[writeIndex] = x;
        writeIndex = (writeIndex + 1) % N;
        return 1;
    }
    int pop(int* ret) {
        if(readIndex == writeIndex) {
            return 0;
        }
        *ret = arr[readIndex];
        readIndex = (readIndex + 1) % N;
        return 1;
    }
    void print() {
        Print::print("read =", readIndex, "write =", writeIndex);
        for(int i = 0; i < N; ++i) {
            Print::print(arr[i]);
        }
    }
};

#endif // LEET1_H
