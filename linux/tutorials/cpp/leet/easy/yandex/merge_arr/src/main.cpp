#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    // int arr[] = {1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1};
    // int arr[] = {1, 1, 14, 15, 16};
    int arr1[] = {1, 7, 2, 3, 5, 0, 1, 2};
    int arr2[] = {3, 2, 1, 2};
    int arrT[100] = {0};
    const int LEN1 = sizeof(arr1) / sizeof(int);
    const int LEN2 = sizeof(arr2) / sizeof(int);
    for (auto&& i : arr1) {
        print(i);
    }
    Arr a{LEN1, arrT};
    print("\n");
    merge_arr(arr1, LEN1, arr2, LEN2, &a);
    print(a.len, a.arr);
    for (auto i = 0; i < a.len; ++i) {
        print(a.arr[i]);
    }
    print("");
    //for (auto&& i : arr2) {
    //    print(i);
    //}
    return 0;
}
