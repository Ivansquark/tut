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

void moveZero(int* arr, int len) {
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

#if 0
    // two pointers first find 0 second find !0 swap
    int zeroIdx = 0;
    int non_zeroIdx = 0;
    while (zeroIdx < len) {
        if (!arr[zeroIdx]) {
            // find non_zero
            non_zeroIdx = zeroIdx;
            while (non_zeroIdx < len - 1 && !arr[non_zeroIdx]) {
                non_zeroIdx++;
            }
            std::swap(arr[non_zeroIdx], arr[zeroIdx]);
        }
        zeroIdx++;
    }
#endif

#if 0
    if (!len) return;
    assert(len < 1000);
    int a[1000] = {0};
    //int* a = (int*)calloc(len, sizeof(int));
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] != 0) {
            a[count++] = arr[i];
        }
    }
    memcpy(arr, a, sizeof(int) * len);
#endif
    // free(a);
    //  for (int i = 0; i < len; ++i) {
    //      if (!arr[i]) {
    //          int* tArr = (int*)malloc(len * sizeof(int));
    //          // copy first elements
    //          memcpy(tArr, arr, i * sizeof(int));
    //          // copy last elements
    //          memcpy(tArr + i, arr + i + 1, (len - 1 - i)*sizeof(int));
    //          //copy zero
    //          tArr[len - 1] = 0;
    //          // reverse copy
    //          memcpy(arr, tArr, len*sizeof(int));
    //          free(tArr);
    //      }
    //  }
}

#endif // LEET1_H
