#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

class Solution {
  public:
    static int lengthOfLongestSubstring(string s) {
        std::string_view sw = s;
        std::string_view sv = s;
        int max = 0;
        int max_cur = 0;
        int count = 0;
        for ([[maybe_unused]] auto&& i : sw) {
            count++;
            for (size_t j = 0; j < sv.size(); j++) {
                max_cur++;
                std::string_view sw1 = sv.substr(0, j + 1);
                if (j == sv.size()) {
                    break;
                }
                auto x = sw1.find(sw1[j + 1], 0);
                if (x != std::string_view::npos) {
                    break;
                }
            }
            if (max_cur > max) {
                max = max_cur;
            }
            max_cur = 0;
            sv = sw.substr(count, sw.size());
        }
        return max;
    }
};

#endif // LEET1_H
