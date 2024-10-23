#include "leet1.h"
#include "math.h"
#include "print.h"

using namespace Print;

#include <stdio.h>
#include <time.h>

void gsetkv(int kv) {
    int kv_s = ceil(kv * 4095 / 50.f);
    char eset[16] = {0};
    snprintf(eset, 16, "%02d,%d,", 0, kv_s);
    // send_string(eset);
    printf("%s\r\n", eset);
    printf("set kV = %d\r\n", kv_s);
}

void printd(int n) {
    long int i = n;
    if (i < 0) {
        putchar('-');
        i = -i;
    }
    if (i / 10) printd(i / 10);
    putchar(i % 10 + '0');
}

int main() {
    printd(0x80000000);
    print("\n");
    gsetkv(25);
    print("\n");
    std::string a = "1010";
    std::string b = "1011";
    std::string res = Sol67::addBinary(a, b);
    print(res);

    time_t biggest = 0x7FFFFFFF;
    printf("biggest = %s \n", ctime(&biggest));
    return 0;
}
