#include <unistd.h>
#include "stdio.h"

#include "main.h"


int main(int argc, char** argv) {
    write(1, "opa\n",4);
    write(2, "error\n", 6);
    write(1, "dev1\n", 4);
    char* str = "\x31 \x32";
    printf("\n%s\n", str);
    printf("\nsum=%d",sum(5,6));
    return 0;
}

int sum(int x, int y) {
    return x + y;
}
