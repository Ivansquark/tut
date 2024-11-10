#include "toup.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void toup(char* str) {
    size_t i;
    for (i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}
