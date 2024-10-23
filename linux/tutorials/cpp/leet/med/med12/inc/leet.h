#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

// I	1
// V	5
// X	10
// L	50
// C	100
// D	500
// M	1000

using namespace std;
class Solution {
  public:
    static std::string intToRoman(int num) {
        std::string str;
        int thousands = num / 1000;
        for (int i = 0; i < thousands; i++) {
            str.push_back('M');
        }
        num -= thousands * 1000;

        int check = num / 100;

        if (check == 9) {
            str.push_back('C');
            str.push_back('M');
            num -= 900;
        } else if (check == 4) {
            str.push_back('C');
            str.push_back('D');
            num -= 400;
        } else {
            int fiveHundr = num / 500;
            for (int i = 0; i < fiveHundr; i++) {
                str.push_back('D');
            }
            num -= fiveHundr * 500;
            int hundr = num / 100;
            for (int i = 0; i < hundr; i++) {
                str.push_back('C');
            }
            num -= hundr * 100;
        }

        check = num / 10;
        if (check == 9) {
            str.push_back('X');
            str.push_back('C');
            num -= 90;
        } else if (check == 4) {
            str.push_back('X');
            str.push_back('L');
            num -= 40;
        } else {
            int fiveTens = num / 50;
            for (int i = 0; i < fiveTens; i++) {
                str.push_back('L');
            }
            num -= fiveTens * 50;
            if (num >= 10) {
                int tens = num / 10;
                for (int i = 0; i < tens; i++) {
                    str.push_back('X');
                }
                num -= tens * 10;
            }
        }

        check = num % 10;
        if (check == 9) {
            str.push_back('I');
            str.push_back('X');
        } else if (check == 4) {
            str.push_back('I');
            str.push_back('V');
        } else {
            int five = num / 5;
            for (int i = 0; i < five; i++) {
                str.push_back('V');
            }
            num -= five * 5;

            int last = num % 10;
            for (int i = 0; i < last; i++) {
                str.push_back('I');
            }
        }
        return str;
    }
};

#endif // LEET1_H
