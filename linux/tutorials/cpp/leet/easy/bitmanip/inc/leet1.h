#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

// Given an integer n, return an array ans of length n + 1 such that for each i
// (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

// Input: n = 2
// Output: [0,1,1]
// Explanation:
// 0 --> 0
// 1 --> 1
// 2 --> 10

vector<int> countBits(int n) {
    vector<int> ret(n + 1, 0);
    for (int i = 1; i < n; ++i) {
        // push back bits
        ret[i] = ret[i >> 1] + i & 1;
    }
    return ret;
}

bool isPowerOfFour(int n) {
    // bit through 1
    bool Is = false;
    if (n == 1) return true;
    int tmp = 0;
    bool IsOne = false;
    for (int i = 0; i < 32; i += 2) {
        // check if only one bit setted
        tmp = n & 3;
        if (tmp) {
            return false;
        }
        n = n >> 2;
        if (n & 1) {
            if (!IsOne) {
                IsOne = true;
            } else {
                return false;
            }
        }
        n &= ~1;
    }
    return true;
}

void reverse(string& str) {
    size_t len = str.size();
    for (size_t i = 0; i < len / 2; ++i) {
        std::swap(str[i], str[len - 1 - i]);
        // char tmp = str[len - 1 - i];
        // str[len - 1 - i] = str[i];
        // str[i] = tmp;
    }
}

char retHex(int n) {
    int t = n % 16;
    if (t == 15) return 'f';
    if (t == 14) return 'e';
    if (t == 13) return 'd';
    if (t == 12) return 'c';
    if (t == 11) return 'b';
    if (t == 10) return 'a';
    return (t + '0');
}

string toHex(int n) {
    string ret;
    int sign = n >> 31;
    if (!sign) {
        do {
            ret.push_back(retHex(n % 16));
        } while (n /= 16);
        reverse(ret);
    } else {
        // two compliment ~x + 1
        for (int i = 0; i < 8; ++i) {
            ret.push_back(retHex((n >> 4 * i) & 0xf));
        }
        reverse(ret);
    }
    return ret;
}

#endif // LEET1_H
