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

using namespace std;
// find max substr with non repeated symbols < k (repeated not count)
// const char* arr = "eceeeaaab";
// "ecceeeb"; check all symbols
//  ++++++-
//   +++++-

int substrMax(const char* arr, int len, int k) {
    // intuitive
    // count k if not reapeted chars
    int countChar[256] = {0};
    int max = 0;
    int temp = 0;  // count real elems
    int count = 0; // check counter

    for (int i = 0; i < len; ++i) {
        temp = 0;
        count = 0;
        // check every symbol  //eceeeaaab (2)
        for (int j = i; j < len; ++j) {
            if (!countChar[arr[j]]) {
                if (count >= k) {
                    // new search
                    // clear hash
                    memset(countChar + 'A' - 1, 0, 255 - 'A');
                    if (max < temp) max = temp;
                    break;
                }
                count++;
                countChar[arr[j]]++;
            }
            temp++;
        }
        // check max
        if (max < temp) max = temp;
    }
    return max;
}

#endif // LEET1_H
