#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    
    int arr[] = {1, 2, 3, 1, 1, 5, 7};
    //int arr[] = {1, 2, 3};
    //const int LEN = sizeof(arr)/sizeof(int);
    vector<int64_t> v;
    for (auto&& i : arr) {
        v.push_back(i);
        print(i);
    }

    size_t ret = longestGoodSubarray(v, 5);

    print("\n");
    print(ret);
    return 0;
}
