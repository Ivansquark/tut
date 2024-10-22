#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    vector<int> arr{2, 3, 7, 8, 9, 17, 19};
    //vector<int> arr{4};
    // int arr[] = {1, 1, 1};
    for (auto&& i : arr) {
        print(i);
    }
    print("\n");
    vector<string> sumRange = summaryRanges(arr);
    for (auto&& i : sumRange) {
        print(i);
    }
    return 0;
}
