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
    //------- O(n) ---------------
    std::unordered_map<int, int> m;
    int count = 0;
    for (int i = 0; i < len1; ++i) {
        m[arr1[i]]++;
    }
    for (int i = 0; i < len2; ++i) {
        if (m[arr2[i]]) {
            m[arr2[i]]--;
            //a->arr[count++] = arr2[i];
            arr1[count++] = arr2[i]; //return in first array
        }
    }
    a->arr = arr1;
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

}

#endif // LEET1_H
