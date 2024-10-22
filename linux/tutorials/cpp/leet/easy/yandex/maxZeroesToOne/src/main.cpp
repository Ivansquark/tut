#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};
    //int arr[] = {1, 1, 1};
    for (auto&& i : arr) {
        print(i);
    }
    print("\n");
    print(maxZeroesToOne(arr, sizeof(arr) / sizeof(int)));
    return 0;
}
