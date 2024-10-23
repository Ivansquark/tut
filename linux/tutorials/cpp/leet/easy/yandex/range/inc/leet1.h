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

void swap(int* l, int* r) {
    int tmp = *r;
    *r = *l;
    *l = tmp;
}
// elements = [1, -3, 4, 5]
// target = 9 ---- begin+...+end = 9    return begin,end
// result = range(2, 4) # because elements[2] + elements[3] == target
typedef struct {
    int begin;
    int end;
} Range;

Range find_range(int* arr, int len, int target) {
    Range range{-1, -1};
    if (!len) {
        return range;
    }
    int begin = 0;
    int sum = 0;
    while (begin < len) {
        for (int i = begin; i < len; ++i) {
            sum += arr[i];
            if (sum == target) {
                range.begin = begin;
                range.end = i + 1;
                return range;
            }
        }
        sum = 0;
        begin++;
    }
    return range;
}

#endif // LEET1_H
