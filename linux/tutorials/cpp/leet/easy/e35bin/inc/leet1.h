#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

int searchInsert(int* nums, int numsSize, int target) {
    int l = 0;
    int r = numsSize - 1;
    //int min = 0;
    int med = 0;
    while (l <= r) {
        med = (r + l) / 2;
        //min = med;
        if(target < nums[med]) {
            r = med - 1;
        } else if (target > nums[med]) {
            l = med + 1;
        } else {
            return med;
        }
    }
    if(target > nums[med]) {
        return med + 1;
    } else {
        return med;
    }
}

#endif // LEET1_H
