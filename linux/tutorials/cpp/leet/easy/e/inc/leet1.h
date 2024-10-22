#ifndef LEET1_H
#define LEET1_H

#include <string>

// 58. Length of Last Word
class Sol58 {
  public:
    static int lengthOfLastWord(const std::string& s) {
        int count = 0;
        bool start = false;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (!start && s.data()[i] != ' ') {
                start = true;
            }
            if (start) {
                if (s.data()[i] == ' ') {
                    break;
                }
                count++;
            }
        }
        return count;
    }
};

// 67. Add bynary
// Given two binary strings a and b, return their sum as a binary string.
class Sol67 {
  public:
    static std::string addBinary(std::string& a, std::string& b) {
        std::string result = "";
        bool IsAdd = false;
        bool IsAbiggerB = false;
        if (a.size() > b.size()) {
            IsAbiggerB = true;
        }
        int size_min = (a.size() <= b.size()) ? a.size() : b.size();
        int size_max = (a.size() >= b.size()) ? a.size() : b.size();
        reverse(a);
        reverse(b);
        for (int i = 0; i < size_min; ++i) {
            char c = 0;
            if (!IsAdd) {
                if (a.data()[i] == '0' && b.data()[i] == '0') {
                    c = '0';
                    IsAdd = false;
                } else if (a.data()[i] == '0' && b.data()[i] == '1') {
                    c = '1';
                    IsAdd = false;
                } else if (a.data()[i] == '1' && b.data()[i] == '0') {
                    c = '1';
                    IsAdd = false;
                } else {
                    c = '0';
                    IsAdd = true;
                }
            } else {
                if (a.data()[i] == '0' && b.data()[i] == '0') {
                    c = '1';
                    IsAdd = false;
                } else if (a.data()[i] == '0' && b.data()[i] == '1') {
                    c = '0';
                    IsAdd = true;
                } else if (a.data()[i] == '1' && b.data()[i] == '0') {
                    c = '0';
                    IsAdd = true;
                } else {
                    c = '1';
                    IsAdd = true;
                }
            }
            result.push_back(c);
        }
        for (int i = size_min; i < size_max; ++i) {
            if (!IsAdd) {
                if (IsAbiggerB) {
                    result.push_back(a.data()[i]);
                } else {
                    result.push_back(b.data()[i]);
                }
            } else {
                if (IsAbiggerB) {
                    char c = a.data()[i];
                    if(c == '0') {
                        IsAdd = false;
                        c = '1';
                    } else {
                        c = '0';
                    }
                    result.push_back(c);
                } else {
                    char c = b.data()[i];
                    if(c == '0') {
                        IsAdd = false;
                        c = '1';
                    } else {
                        c = '0';
                    }
                    result.push_back(c);
                }
            }
        }
        if(size_min = size_max) {
            if (IsAdd) {
                result.push_back('1');
            }
        }
        reverse(result);
        return result;
    }
    static void reverse(std::string& str) {
        int end = (str.size()) / 2;
        for (int i = 0; i < end; ++i) {
            std::swap(str.data()[i], str.data()[str.size() - 1 - i]);
        }
    }
};

#endif // LEET1_H
