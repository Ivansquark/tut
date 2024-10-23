#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>
#include <limits.h>

using namespace std;

int findMin(int* nums, int numsSize) {
    // get nums[mid] get nums[low] if low < mid => left sorted => min go r
    // else => right sorted set min => go left
    int l = 0;
    int r = numsSize - 1;
    int min = INT_MIN;
    //int min = 0x7FFFFFFF;
    int mid = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (nums[l] <= nums[mid]) {
            // left is sorted, go right
            min = (min < nums[l]) ? min : nums[l];
            l = mid + 1;
        } else {
            // right is sorted, go left
            min = (min < nums[r]) ? min : nums[r];
            r = mid - 1;
        }
    }
    return min;
}

#endif // LEET1_H
