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
#include <vector>

using namespace std;

vector<string> summaryRanges(vector<int>& nums) {
    vector<string> ret;
    size_t count = 0;
    if(!nums.size()) return ret;

    for (size_t i = 1; i < nums.size(); ++i) {
        if ((nums[i]) != (nums[i - 1] + 1)) {
            // print left
            if (i - 1 == count) {
                string tmp = to_string(nums[count]);
                ret.push_back(tmp);
                count++;
            } else {
                string tmp = to_string(nums[count]);
                string tmp1 = to_string(nums[i - 1]);
                ret.push_back(tmp + "->" + tmp1);
                // set count on new pos
                count = i;
            }
        }
    }
    if (!count) {
        if (nums.size() == 1) {
            string tmp = to_string(nums[count]);
            ret.push_back(tmp);
        } else {
            string tmp = to_string(nums[count]);
            string tmp1 = to_string(nums[nums.size() - 1]);
            ret.push_back(tmp + "->" + tmp1);
        }
    } else if (count < nums.size() - 1) {
        string tmp = to_string(nums[count]);
        string tmp1 = to_string(nums[nums.size() - 1]);
        ret.push_back(tmp + "->" + tmp1);
    } else if (count == nums.size() - 1) {
        string tmp = to_string(nums[count]);
        ret.push_back(tmp);
    }

    return ret;
}

#endif // LEET1_H
