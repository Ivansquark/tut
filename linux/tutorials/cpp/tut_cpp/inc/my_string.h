#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <string.h>

class String {
  public:
    String() = default;
    String(int n, char a) : arr(new char[n]), size(n) { memset(arr, a, size); }
    String(const char* a) : String(sizeof(a), '\0') { memcpy(arr, a, size); }
    String(const String& s) : String(s.size, '\0') { memcpy(arr, s.arr, size); }
    String& operator=(String s) {
        swap(s);
        return *this;
    }
    String(String&& s) : arr(std::move(s.arr)), size(std::move(s.size)) {
        arr = nullptr;
        size = 0;
    }
    String& operator=(String&& s) {
        //String ss = std::move(s);
        swap(s);
        //size = std::move(s.size);
        //s.size = 0;
        //arr = std::move(s.arr);
        //s.arr = nullptr;
        return *this;
    }

    ~String() { delete[] arr; }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        for (int i = 0; i < s.size; i++) { os << s.arr[i]; }
        return os;
    }

  private:
    char* arr;
    int size;
    void swap(String& s) {
        size = s.size;
        s.size = 0;
        arr = s.arr;
        s.arr = nullptr;
    }
};

#endif // MY_STRING_H
