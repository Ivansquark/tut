#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    // int arr[] = {1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1};
    //int arr[] = {1, 1, 14, 15, 16};
    int arr[] = {0};
    const int LEN = sizeof(arr) / sizeof(int);
    for (auto&& i : arr) {
        print(i);
    }

    print("\n");
    Range r = find_range(arr, LEN, 15);
    print(r.begin, r.end);
    return 0;
}
