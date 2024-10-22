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

int maxRanges(int* arr1, int len1, int* arr2, int len2) {
    if (len2 > len1) return 0;
    if (!len2) return 0;
    // find arr, ranges = l + size-1 - right
    for (int i = 0; i < len1; ++i) {
        if (arr1[i] == arr2[0]) {
            // check coincedence
            bool has = true;
            for (int j = 0; j < len2; ++j) {
                if (arr1[i + j] != arr2[j]) {
                    has = false;
                }
            }
            if (has) {
                return (i + (len1 - (len2)));
            }
        }
    }
}

int maxArr2InArr1(int* arr1, int len1, int* arr2, int len2) {
    if (len2 > len1) return 0;
    int count = 0;
    bool has = false;
    for (int i = 0; i < len1 - (len2 - 1); ++i) {
        has = false;
        for (int j = 0; j < len2; ++j) {
            if (arr1[j + i] != arr2[j]) {
                break;
            }
            if (j == len2 - 1) has = true;
        }
        if (!has)
            continue;
        else {
            i += len2 - 1;
            count++;
        }
    }
    return count;
}

#endif // LEET1_H
