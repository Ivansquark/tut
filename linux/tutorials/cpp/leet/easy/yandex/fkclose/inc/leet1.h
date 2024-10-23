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

struct arrS {
    int len = 0;
    int* arr;
};

// find_k_closest(a={2,3,5,7,11}, index=3, k=2) -> {5,7}
// find_k_closest(a={4,12,15,15,24}, index=1, k=3) -> {12,15,15}
// find_k_closest(a={2,3,5,7,11}, index=2, k=2) -> {5,7} или {3,5}

void find_k_closest(int* arr, int len, int idx, int k, arrS* stru) {
    // find left diff, find right diff, check which, add to arr left or right
    if (!k) {
        stru->len = 0;
    }
    if (k == 1) {
        stru->len = 1;
        stru->arr[0] = arr[idx];
    }
    int diffLeft = 0;
    int diffRight = 0;
    int countLeft = idx;
    int countRight = idx;
    if (countLeft > 0) {
        countLeft = idx - 1;
    }
    if (countRight < len) {
        countRight = idx + 1;
    }
    k--;
    while (k > 1) {
        // find l & r
        if (countLeft > 0) {
            diffLeft = arr[idx] - arr[countLeft];
        } else {
            diffLeft = arr[idx];
        }
        if (countRight < len) {
            diffRight = arr[idx] - arr[countRight];
        } else {
            diffRight = arr[idx];
        }
        if (diffLeft < diffRight) {
            if (countLeft > 0) {
                countLeft--;
            }
        } else {
            if (countRight < len) {
                countRight++;
            }
        }
        k--;
    }
    stru->len = countRight - countLeft;
    Print::print(stru->len);
    memcpy(stru->arr, arr + countLeft, stru->len * sizeof(int));
}

#endif // LEET1_H
