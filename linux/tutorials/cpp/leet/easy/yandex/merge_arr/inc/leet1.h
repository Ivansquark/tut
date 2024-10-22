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

using namespace std;

void swap(int* l, int* r) {
    int tmp = *r;
    *r = *l;
    *l = tmp;
}

// Даны два массива: [1, 2, 3, 2, 0] и [5, 1, 2, 7, 3, 2]
// Надо вернуть [1, 2, 2, 3] (порядок неважен)

typedef struct {
    int len;
    int* arr;
} Arr;

void merge_arr(int* arr1, int len1, int* arr2, int len2, Arr* a) {
#if 0
    if (!len1 || !len2) {
        a->len = 0;
        return;
    }
    std::unordered_map<int,int> m1;
    std::unordered_map<int,int> m2;
    for(auto i = 0; i < len1; ++i) {
        m1[i]++;
    }
    for(auto i = 0; i < len2; ++i) {
        m2[i]++;
    }
    auto size = (m1.size() > m2.size()) ? m1.size() : m2.size();
    int count = 0;
    for(int i = 0; i < size; ++i) {
        if(m1[i] && m2[i]) {
            a->arr[count] = arr1[i];
            count++;
        }
    }
    a->len = count;
#endif
    int arr_t[len1 + len2] = {0}; // VLA
    int count = 0;
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            if (arr1[i] == arr2[j]) {
                a->arr[count++] = arr1[i];
                break;
            }
        }
    }
    a->len = count;
}

#endif // LEET1_H
