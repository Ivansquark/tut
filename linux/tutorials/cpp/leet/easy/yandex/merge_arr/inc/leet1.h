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
// [1,2,3,4,5] [2,3,4]

typedef struct {
    int len;
    int* arr;
} Arr;

void merge_arr(int* arr1, int len1, int* arr2, int len2, Arr* a) {
#if 0
    // ----- Sort 1 2 two pointers O(nlog(n)) ---------------
    sort(arr1, arr1 + len1, [](int x, int y) { return x < y; });
    sort(arr2, arr2 + len2, [](int x, int y) { return x < y; });
    int l1 = 0;
    int l2 = 0;
    int r1 = 0; // i
    int r2 = 0; // i
    while (l1 < len1 && l2 < len2) {
        if (arr1[l1] < arr2[l2]) {
            l1++;
        } else if (arr1[l1] > arr2[l2]) {
            l2++;
        } else {
            // find right
            r1 = l1;
            r2 = l2;
            while (arr1[r1] == arr2[r2]) {
                r1++;
                r2++;
                if ((r1 >= len1) || (r2 >= len2)) {
                    break;
                }
            }
            break;
        }
    }
    a->len = r1 - l1;
    memcpy(a->arr, arr1 + l1, a->len*sizeof(int));
#endif

    //------- O(n) ---------------
    std::unordered_map<int, int> m;
    int count = 0;
    for (int i = 0; i < len1; ++i) {
        m[arr1[i]]++;
    }
    for (int i = 0; i < len2; ++i) {
        if (m[arr2[i]]) {
            m[arr2[i]]--;
            a->arr[count++] = arr2[i];
        }
    }
    a->len = count;
#if 0

    //------- O(n) ---------------
    if (!len1 || !len2) {
        a->len = 0;
        return;
    }
    std::unordered_map<int, int> m1;
    std::unordered_map<int, int> m2;
    for (auto i = 0; i < len1; ++i) {
        m1[arr1[i]]++;
    }
    for (auto i = 0; i < len2; ++i) {
        m2[arr2[i]]++;
    }
    int count = 0;
    // check less array
    if (len1 < len2) {
        // arr1
        for (int i = 0; i < len1; ++i) {
            if (m1[arr1[i]] && m2[arr1[i]]) {
                m1[arr1[i]]--;
                m2[arr1[i]]--;
                a->arr[count] = arr1[i];
                count++;
            }
        }
    } else {
        // arr2
        for (int i = 0; i < len2; ++i) {
            if (m1[arr2[i]] && m2[arr2[i]]) {
                m1[arr2[i]]--;
                m2[arr2[i]]--;
                a->arr[count] = arr2[i];
                count++;
            }
        }
    }

    a->len = count;
#endif

#if 0
    // ------ O(n^2) --------------
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
#endif
}

#endif // LEET1_H
