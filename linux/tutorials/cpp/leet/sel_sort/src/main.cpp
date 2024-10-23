#include "print.h"

#include <stdint.h>

using namespace Print;

void selSort(int* arr, int len);
void bubbleSort(int* arr, int len);
int binSearch(int* arr, int size, int val);

int main() {
    int arr[] = {3, 5, 1, 7, 2};
    selSort(arr, sizeof(arr) / sizeof(int));
    //bubbleSort(arr, sizeof(arr) / sizeof(int));
    for (auto&& i : arr) {
        print(i);
    }
    //print(binSearch(arr, sizeof(arr) / sizeof(int), 1));
    // for(int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
    //     print(arr[i]);
    // }
    return 0;
}

void swap(int* l, int* r) {
    int tmp = *r;
    *r = *l;
    *l = tmp;
}

void selSort(int* arr, int len) {
    // find min => swap with first
    for(int  i = 0; i < len; ++i) {
        int min = 0x7fffffff;
        int idx = 0;
        for(int j = i; j < len; ++j) {
            if(arr[j] < min) {
                min = arr[j];
                idx = j;
            }
            swap(&arr[i], &arr[idx]);
        }
    }
    //
    //
    //int first = 0;
    //while (first < len) {
    //    int max = arr[first];
    //    int idx = first;
    //    for (int i = first; i < len; ++i) {
    //        if (arr[i] > max) {
    //            max = arr[i];
    //            idx = i;
    //        }
    //    }
    //    if (idx > first) {
    //        swap(&arr[first], &arr[idx]);
    //    }
    //    first++;
    //}
}

void bubbleSort(int* arr, int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int binSearch(int* arr, int size, int val) {
    // find mid
    int mid = size;
    int first = 0;
    int last = size - 1;
    while (first <= last) {
        mid = (last + first) / 2;
        if (val < arr[mid]) {
            last = mid - 1;
        } else if (val > arr[mid]) {
            first = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
