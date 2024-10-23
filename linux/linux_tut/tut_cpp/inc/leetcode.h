#ifndef LEETCODE_H
#define LEETCODE_H

#include <algorithm>
#include <string.h>
#include <string>
#include <vector>

class Solution {
    int arrX[10] = {0};
    int arrY[10] = {0};

  public:
    std::string largestNumber(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end(), [this, &nums](int y, int x) {
            fillArr(arrX, x);
            fillArr(arrY, y);
            bool isXbiggerY = !IsXbiggerY();
            memset(arrX, 0, 10);
            memset(arrY, 0, 10);
            return isXbiggerY;
        });
        std::string s;
        for (auto i : nums) { s += (std::to_string(i)); }
        return s;
    }

  private:
    void fillArr(int* arr, int val) {
        int count = 0;
        int tempVal = val;
        while (tempVal) {
            arr[count] = tempVal % 10;
            tempVal /= 10;
            count++;
        }
    }
    bool IsXbiggerY() {
        int tempBigXi = 0;
        int tempBigYi = 0;
        for (int i = 9; i >= 0; --i) {
            if (arrX[i] > arrY[i]) {
                if (!arrY[i]) {
                    tempBigXi = i;
                    break;
                }
                return true;
            } else if (arrX[i] < arrY[i]) {
                if (!arrX[i]) {
                    tempBigYi = i;
                    break;
                }
                return false;
            }
        }
        if (tempBigXi) {
            for (int i = tempBigXi; i >= 0; --i) {
                if (arrY[i]) {
                    for (int j = tempBigXi; j >= 0; --j, --i) {
                        if (i < 0) {
                            if (!arrX[j])
                                return false;
                            else
                                return false;
                        }
                        if (arrX[j] > arrY[i]) {
                            return true;
                        } else if (arrX[j] < arrY[i]) {
                            return false;
                        }
                    }
                    return false;
                }
            }
        } else if (tempBigYi) {
            for (int i = tempBigYi; i >= 0; --i) {
                if (arrX[i]) {
                    for (int j = tempBigYi; j >= 0; --j, --i) {
                        if (i < 0) {
                            if (!arrY[j])
                                return true;
                            else
                                return true;
                        }
                        if (arrX[i] > arrY[j]) {
                            return true;
                        } else if (arrX[i] < arrY[j]) {
                            return false;
                        }
                    }
                    return false;
                }
            }
        }
        return false;
    }
};

#endif // LEETCODE_H
