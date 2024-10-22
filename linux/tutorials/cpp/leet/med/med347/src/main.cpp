#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {3, 4, 5, 5, 2, 2, 3};
    //int arr1[] = {5, 5, 0, 2, 3, 3, 4};
    //int arr2[] = {1, 2, 3, 3, 4, 5, -1};
    int len = sizeof(arr) / sizeof(int);

    print();
    int a;
    int* arrr = topKFrequent(arr, len, 2, &a);
    for(int i = 0; i < a; ++i) {
        print(arrr[i]);
    }
    return 0;
}
