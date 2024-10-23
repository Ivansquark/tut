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

int maxZeroesToOne(int* arr, int len) {
    // find max zeroes sequence, return middle
    int l = 0;
    int l_temp = 0;
    int count = 0;
    int max = 0;
    for(int i = 0; i < len - max + 1; ++i) {
        if(!arr[i]) {
            // find straight zeroes
            count = 0;
            l_temp = i;
            while(!arr[i]) {
                count++;
                i++;
                if(i == len) break;
            }
            if(max <= count) {
                max = count;
                l = l_temp;
            }
            //Print::print("max = ", max);
        }
    }
    return (l + max /2);

}

#endif // LEET1_H
