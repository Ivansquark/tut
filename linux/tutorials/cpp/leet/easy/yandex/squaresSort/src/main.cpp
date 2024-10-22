#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {-1, -116, -2, -1, -99, 0};
    //int arr[] = {0};
    const int LEN = sizeof(arr) / sizeof(int);
    for (auto&& i : arr) {
        print(i);
    }

    print("\n");
    print(minMulTwo(arr, LEN));
    return 0;
}
