#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

int mySqrt(int x) {
//#if 0
    if (!x) return 0;
    int l = 0;
    int r = x;
    long long int mid = 0;
    while (l <= r) {
        //mid = (l + r) / 2;
        mid = (l + r + 1) / 2;
        //if (x / mid == mid) return mid;
        if (x / mid < mid) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mid;
//#endif

#if 0
    if(!x) return 0;
    int l = 1;
    int r = x / 2;
    int mid = 0;

    while (l <= r) {
        mid = (r + l) / 2;
        //if (x % mid == 0 && x / mid == mid) {
        if (x / mid == mid) {
            return mid;
        }
        if (mid > x / mid) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mid;
#endif
}

#endif // LEET1_H
