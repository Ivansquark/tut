#include "o.h"

static void (*events[10])() = {0};
void (*functions[2])() = {nullptr};
void addHandler(int i, void (*f)()) { events[i] = f; }
void call(int i) { events[i](); }
void addFunctions(void (*f)()) {
    for(int i = 0; i < 2; ++i) {
        if(!functions[i]) {
            functions[i] = f;
            return;
        }
    }
}
void callFunctions() {
    for(int i = 0; i < 2; ++i) {
        if(functions[i]) {
            functions[i]();
        }
    }
}

void (*ObsMan::events[10])() = {nullptr};
void (*ObsManDyn::events[10])() = {nullptr};
ObsInterface* ObsDyn::objs[2] = {nullptr};
