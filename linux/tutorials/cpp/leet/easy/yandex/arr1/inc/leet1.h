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

void moveZeroStatic(int** arr, int* len) {
    // static replace arr pointers
    Print::print("arr = ", arr);
    if (!len) return;
    static int a[10000] = {0};
    int count = 0;
    for (int i = 0; i < *len; i++) {
        if (*(*arr + i) != 0) {
            a[count++] = *(*arr + i);
        }
    }
    int* pa = (int*)a;
    *arr = pa;

    for (int i = 0; i < *len; ++i) {
        Print::print(*(*arr + i));
    }
    // Print::print(*arr);
    Print::print("a = ", a);
}
void moveZero(int* arr, int len) {
    /* 2 ptr p0 - find 0, p1-find1 swap
     * [1,0,0,3,0]
     *  1 | | | |
     *  0 | | | |
     *
     *  1 | | | |
     *  | 0 | | |
     *
     *  | | | 1 |
     *  | 0 | | |
     *
     * [0,0,0,0,0]
     * [1,1,1,1,1]
     */
    if (!len || len == 1) return;
    int p0 = 0;
    for (int p1 = 0; p1 < len; p1++) {
        if (arr[p1]) {
            if (!arr[p0]) {
                std::swap(arr[p0], arr[p1]);
            }
            p0++;
        }
    }

#if 0
    int j = 0;
    for (int i = 0; i < len; ++i) {
        // find first not_zero
        if (arr[i]) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j++;
        }
    }

#endif

#if 0
    if (!len) return;
    assert(len < 1000);
    // memset(a, 0, sizeof(a));
    int* a = (int*)calloc(len, sizeof(int));
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] != 0) {
            a[count++] = arr[i];
        }
    }
    memcpy(arr, a, sizeof(int) * len);
    // for(unsigned long long i = 0; i < 1000000000*3*5; ++i) {
    //     __asm("nop");
    // }
    //  free(a);
#endif
    //   for (int i = 0; i < len; ++i) {
    //       if (!arr[i]) {
    //           int* tArr = (int*)malloc(len * sizeof(int));
    //           // copy first elements
    //           memcpy(tArr, arr, i * sizeof(int));
    //           // copy last elements
    //           memcpy(tArr + i, arr + i + 1, (len - 1 - i)*sizeof(int));
    //           //copy zero
    //           tArr[len - 1] = 0;
    //           // reverse copy
    //           memcpy(arr, tArr, len*sizeof(int));
    //           free(tArr);
    //       }
    //   }
}

#endif // LEET1_H
