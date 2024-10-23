#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr1[] = {1, 1, 3, 2, 1, 4, 1, 3, 2, 1};
    //int arr2[] = {1, 1, 3, 2, 1, 4, 1, 3, 2};
    //int arr2[] = {3,2,1};
    int arr2[] = {3, 2, 1};
    // int arr[] = {1, 1, 1};
    for (auto&& i : arr1) {
        print(i);
    }
    print("");
    for (auto&& i : arr2) {
        print(i);
    }
    print("");
    print(maxArr2InArr1(arr1, sizeof(arr1) / sizeof(int), arr2,
                        sizeof(arr2) / sizeof(int)));
    print("");
    print(maxArr2InArrMap(arr1, sizeof(arr1) / sizeof(int), arr2,
                        sizeof(arr2) / sizeof(int)));
    //print("\n");
    print(maxRanges(arr1, sizeof(arr1) / sizeof(int), arr2,
                        sizeof(arr2) / sizeof(int)));
    return 0;
}
