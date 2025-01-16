#include <stdio.h>

int main(int argc, char** argv) {
    printf("Hello patch\n");
    for(int i = 1; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
