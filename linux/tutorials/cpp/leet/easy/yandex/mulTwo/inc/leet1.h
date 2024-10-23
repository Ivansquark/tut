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

int minMulTwo(int* arr, int len) {
    if (!len) return 0;
    if (len == 1) return arr[0];
    int min1 = 0x7fffffff, min2 = 0x7fffffff, max1 = 0x80000000,
        max2 = 0x80000000;
    for (int i = 0; i < len; ++i) {
        if (min1 > arr[i]) {
            min2 = min1;
            min1 = arr[i];
        } else {
            if (min2 >= arr[i]) {
                min2 = arr[i];
            }
        }
        if (max1 < arr[i]) {
            max2 = max1;
            max1 = arr[i];
        } else {
            if (max2 <= arr[i]) {
                max2 = arr[i];
            }
        }
    }
    //Print::print("min1", min1, "min2", min2);
    //Print::print("max1", max1, "max2", max2);
    if ((min1 < 0 && min2 < 0) && (max2 < 0) && (max1 < 0)) {
        return max1 * max2;
    }
    if ((min1 < 0 && min2 < 0) && (max2 < 0) && (max1 >= 0)) {
        return min1 * max1;
    }
    if ((min1 < 0 && min2 < 0) && (max2 >= 0) && (max1 >= 0)) {
        return min1 * max1;
    }
    if ((min1 < 0 && min2 >= 0) && (max2 >= 0) && (max1 >= 0)) {
        return min1 * max1;
    }
    if ((min1 >= 0 && min2 >= 0) && (max2 >= 0) && (max1 >= 0)) {
        return min1 * min2;
    }
    return 0;
}

#endif // LEET1_H
