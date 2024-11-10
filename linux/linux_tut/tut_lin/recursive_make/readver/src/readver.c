#include "readver.h"

#include <stdio.h>
#include <string.h>

int readver(char* str) {
    int i;
    FILE* fp = fopen("/proc/version", "r");
    if (!fp) {
        fprintf(stderr, "Cannot open /proc/ver\n");
        return 1;
    }
    for (i = 0; (i < STR_SIZE) && ((str[i] = fgetc(fp)) != EOF); ++i) {}
    str[i] = 0;
    fclose(fp);
    return 0;
}
