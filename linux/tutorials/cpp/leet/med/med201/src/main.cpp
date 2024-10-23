#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;
int bitRange(int left, int right) {
    long long int ret = left;
    if (left != 2147483647) {
        for (int i = left + 1; i < right; ++i) {
            ret &= i;
        }
    } else {
        ret = left & right;
    }

    return ret;
}

int main() {
    print(bitRange(1, 2));
    return 0;
}
