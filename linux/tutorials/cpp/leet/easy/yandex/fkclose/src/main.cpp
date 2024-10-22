#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {1, 1, 14, 15, 16};
    const int LEN = sizeof(arr)/sizeof(int);
    int arrRet[LEN] = {0};
    for (auto&& i : arr) {
        print(i);
    }
    arrS stru = {0, arrRet};

    find_k_closest(arr, LEN, 4, 4, &stru);

    print("\n");
    for (auto i = 0; i < stru.len; ++i) {
        print(stru.arr[i]);
    }
    return 0;
}
