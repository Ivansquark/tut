#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {0, 0, 3, 4, 0, 8, 0};
    for (auto&& i : arr) {
        print(i);
    }
    print("\n");
    moveZero(arr, sizeof(arr) / sizeof(int));
    for (auto&& i : arr) {
        print(i);
    }
    return 0;
}
