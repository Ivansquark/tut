#ifndef LEET1_H
#define LEET1_H

#include "print.h"
#include <algorithm>
#include <list>
#include <stdint.h>
#include <string>
#include <string_view>

using namespace std;

struct stack {
    char arr[10000] = {0};
    int count = 0;
};
void push(struct stack* s, char a) { s->arr[s->count++] = a; }
char pop(struct stack* s) {
    if (!s->count) return -1;
    char tmp = s->arr[s->count - 1];
    s->count--;
    return tmp;
}

bool isValid(char* s) {
    stack st;
    if (!*s) return false;
    while (*s) {
        char c = *s;
        if (c == '(' || c == '{' || c == '[') {
            push(&st, c);
            if (!(*(s + 1))) return false;
        } else {
            char get = pop(&st);
            if (get == -1) return false;
            if (get == '(' && c == ')') {
            } else if (get == '{' && c == '}') {
            } else if (get == '[' && c == ']') {
            } else {
                return false;
            }
        }
        s++;
    }
    if (st.count) return false;
    return true;
}

#endif // LEET1_H
