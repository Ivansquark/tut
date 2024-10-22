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
#include <vector>

using namespace std;

size_t longestGoodSubarray(const vector<int64_t> v, uint32_t k) {
    // two pointers right finds no repeats left;
    size_t len = v.size();
    if (!len) return 0;
    if (len == 1) return 1;
    size_t l = 0;
    size_t r = 0;
    size_t max = 0;
    unordered_map<int, int> m;
    for (size_t i = 0; i < len; ++i) {
        if (!m[v[i]]) {
            // go next
            r++;
            // check k 
            if ((r - l - 1) >= k) return k;
        } else {
            if (max < r - l) max = r - l;
            l = r;
            //new check
            m.clear();
            i = r;
            // go next
            r++;
        }
        m[v[i]]++;
    }
    if (max < r - l) max = r - l;
    return max;
#if 0

    //uint64_t arr[10000] = {0};
    //for (size_t i = 0; i < v.size(); ++i) {
    //    memset(arr, 0, sizeof(arr));
    //    size_t tmp = 0;
    //    for (size_t j = i; j < v.size(); ++j) {
    //        if (arr[v[j]]) {
    //            break;
    //        } else {
    //            arr[v[j]]++;
    //            tmp++;
    //        }
    //        max = (max < tmp) ? tmp : max;
    //    }
    //}
    return max;
#endif
}

#endif // LEET1_H
