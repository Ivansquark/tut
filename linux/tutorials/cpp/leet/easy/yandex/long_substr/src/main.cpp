#include "leet1.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    // find max substr with non repeated symbols < k (repeated not count)
    //const char* arr = "eceeeaaab";
    const char* arr = "eceeeb";
    //const char* arr = "";
    //const char* arr = "eceeeaaabbbbbbb";
    print(arr);
    print("\n");
    print(substrMax(arr, strlen(arr), 4));
    return 0;
}
