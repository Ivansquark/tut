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

vector<int> sortedSquares(vector<int>& nums) {
    int len = nums.size();
    if (!len) return nums;
    if (len == 1) {
        nums[0] *= nums[0];
        return nums;
    }
    int l = 0;
    int r = len - 1;
    vector<int> ret(len, 0);
    int count = len - 1;
    while (l <= r) {
        long int r1 = nums[r] * nums[r];
        long int l1 = nums[l] * nums[l];
        if (l1 < r1) {
            ret[count] = r1;
            r--;
        } else {
            ret[count] = l1;
            l++;
        }
        count--;
    }
    return ret;
}

#endif // LEET1_H
