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

int substrMax(const char* arr, int len, int k) {
    // intuitive
    // count k if not reapeted chars
    char countChar[255] = {0};
    int max = 0;
    int temp = 0;  // count real elems
    int count = 0; // check counter

    for (int i = 0; i < len; ++i) {
        temp = 0;
        count = 0;
        // check every symbol  //eceeeaaab (2)
        for (int j = i; j < len; ++j) {
            if (countChar[arr[j]]) {
                // not count
                temp++;
            } else {
                if (count >= k) {
                    // new search
                    // clear hash
                    memset(countChar, 0, 255);
                    break;
                }
                temp++;
                count++;
                countChar[arr[j]]++;
            }
        }
        // check max
        if (max < temp) max = temp;
    }
    return max;
}

#endif // LEET1_H
