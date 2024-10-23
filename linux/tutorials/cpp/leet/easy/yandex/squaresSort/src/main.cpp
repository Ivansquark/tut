#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    int arr[] = {-116, -11, -2, -1, 0, 1};
    // int arr[] = {0};
    const int LEN = sizeof(arr) / sizeof(int);
    for (auto&& i : arr) {
        print(i);
    }

    print("\n");
    std::vector<int> v = sortedSquares(std::vector<int>(arr, arr + LEN));
    for (auto i : v) {
        print(i);
    }
    return 0;
}
