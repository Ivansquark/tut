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
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    for (int i = 0; i < len1 - (len2 - 1); ++i) {
        if (arr1[i] == arr2[0]) {
            // check coincedence
            bool has = true;
            for (int j = 0; j < len2; ++j) {
                if (arr1[i + j] != arr2[j]) {
                    has = false;
                    break;
                }
            }
            if (has) {
                return ((len1 - (len2 - 1)));
            }
        }
    }
    return 0;
}

int maxArr2InArr1(int* arr1, int len1, int* arr2, int len2) {
    if (len2 > len1) return 0;
    int count = 0;
    bool has = false;
    for (int i = 0; i < len1 - (len2 - 1); ++i) {
        if (arr1[i] != arr2[0]) continue;
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

int maxArr2InArrMap(int* arr1, int len1, int* arr2, int len2) {
    struct VecHasher {
        std::size_t operator()(const std::vector<int>& a) const {
            std::size_t h = 0;
            for (int e : a) {
                //h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
                h ^= e + 0x9e3779b9 + (h << 6) + (h >> 2);
            }
            return h;
        }
    };
    if (len2 > len1) return 0;
    vector<int> v1(arr1, arr1 + len1);
    vector<int> v2(arr2, arr2 + len2);
    unordered_map<std::vector<int>, int, VecHasher> test;
    for (int i = 0; i < len1 - (len2 - 1); ++i) {
        if (arr1[i] != arr2[0]) continue;
        vector<int> v(arr1 + i, arr1 + i + len2);
        unordered_map<std::vector<int>, int, VecHasher> tmp;
        test[v]++;
    }
    return test[v2];
}

#endif // LEET1_H
