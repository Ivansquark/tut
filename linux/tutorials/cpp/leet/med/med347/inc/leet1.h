#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* ret = (int*)calloc(k, sizeof(int));

    int arrNeg[10001] = {0};
    int arrPos[10001] = {0};

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] < 0) {
            arrNeg[-nums[i]]++;
        } else {
            arrPos[nums[i]]++;
        }
    }
    int max = 0;
    // TODO: find k max elements
    int* arr = (int*)calloc(k, sizeof(int));
    for (int i = 0; i < k; ++i) {
        // set max = 0
        int max_i_neg = 0;
        int max_i_pos = 0;
        for (int i = 1; i < 10001; ++i) {
            if (max < arrNeg[i]) {
                max = arrNeg[i];
                max_i_neg = i;
            }
        }
        max = 0;
        for (int i = 0; i < 10001; ++i) {
            if (max < arrPos[i]) {
                max = arrPos[i];
                max_i_pos = i;
            }
        }
        max = (max_i_neg < max_i_pos) ? -1*(max_i_neg) : max_i_pos;
        arr[i] = max;
    }
    //reverse arr
    for(int i = 0; i < k; ++i) {
        ret[i] = arr[k-1-i];
    }
    *returnSize = k;
    return ret;
}

#if 0 
class Solution {
  public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;

        // Count the frequency of each element
        for (auto it : nums) {
            m[it]++;
        }

        priority_queue<pair<int, int>> q;

        // Push each element and its frequency as a pair into the priority queue
        for (auto it : m) {
            q.push({it.second, it.first});
        }

        vector<int> ans;

        // Pop the top k elements from the priority queue and add them to the
        // result array
        while (k--) {
            ans.push_back(q.top().second);
            q.pop();
        }

        return ans;
    }
};
# endif
#endif // LEET1_H
