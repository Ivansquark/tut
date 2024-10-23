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

int maxOnesLenIfDel1Element(int* arr, int len) {
    if (!len) return 0;
    if ((len == 1) && arr[0]) return 1;
    // find zero count left 1, right 1, max
    int max = 0;
    int l = 0;
    int r = 0;
    for (int i = 0; i < len; ++i) {
        if (!arr[i]) {
            // left
            l = 0;
            while ((i - l > 0) && arr[i - l - 1]) {
                l++;
            }
            // right
            r = 0;
            while ((i + r + 1 < len) && arr[i + r + 1]) {
                r++;
            }
            if (max < l + r) max = l + r;
        }
        i += r; //goto right
    }
    return max;

#if 0
    // find zero count left, right, max
    int max = 0;
    for (int i = 0; i < len; ++i) {
        if (!arr[i]) {
            // count left
            int j = i;
            int countL = 0;
            while (j--) {
                if (!arr[j]) break;
                countL++;
            }
            if (!j && arr[0]) countL++;
            // count right
            int countR = 0;
            if (i != len - 1) {
                for (int j = i + 1; j < len; ++j) {
                    if (!arr[j]) break;
                    countR++;
                }
            }
            if (max <= countL + countR) {
                max = countL + countR;
            }
        }
    }
    if (len > 0 && !max) {
        if (!arr[0]) return 0;
        return len - 1;
    }
    return max;

    // greedy
    // int maxCount = 0;
    // int tempCount = 0;
    // int count = 0;
    // while (count < len) {
    //    for (int i = 0; i < len; ++i) {
    //        if (i == count) continue;
    //        // count max ones
    //        if (arr[i] == 1) {
    //            tempCount++;
    //        } else {
    //            if (tempCount > maxCount) {
    //                maxCount = tempCount;
    //            }
    //            tempCount = 0;
    //        }
    //    }
    //    if (tempCount > maxCount) {
    //        maxCount = tempCount;
    //    }
    //    tempCount = 0;
    //    count++;
    //}
    // return maxCount;
#endif
}

#endif // LEET1_H
