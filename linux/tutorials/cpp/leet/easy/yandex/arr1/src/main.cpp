#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    // int arr[] = {0, 0, 3, 4, 0, 8, 0};
    int arr[] = {1, 0, 0, 0, 1};
    for (auto&& i : arr) {
        print(i);
    }
    print("\n");
    // moveZero(arr, sizeof(arr) / sizeof(int));
    for (auto&& i : arr) {
        print(i);
    }
    print("\n");

    int arr1[] = {1, 0, 0, 0, 2};
    int* pa = (int*)&arr1[0];
    print("prev pa = ", pa);
    int** pa1 = &pa;
    int LEN = sizeof(arr) / sizeof(int);
    moveZeroStatic(pa1, &LEN);
    print("cur pa = ", pa);
    for (int i = 0; i < LEN; ++i) {
        //print(*(*pa1 + i));
        print(*(pa + i));
    }

    return 0;
}
