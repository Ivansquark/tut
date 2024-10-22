#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {1, 2, 3};
    int arr1[] = {0, 1, 3};
    int arr2[] = {1, 2, 3};
    int len = sizeof(arr) / sizeof(int);

    print(searchInsert(arr, len, 4));
    print(searchInsert(arr1, len, 2));
    print(searchInsert(arr2, len, 0));
    return 0;
}
