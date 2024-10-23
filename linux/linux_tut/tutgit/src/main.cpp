#include "stdio.h"
#include <iostream>
#include <unistd.h>

#include "sum.h"
#include "print.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    write(1, "opa\n", 4);
    print(1, 2, "opa");
    print(sum(1, 2, 3));
    return 0;
}

int sum(int x, int y) { return x + y; }
