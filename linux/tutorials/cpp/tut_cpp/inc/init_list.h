#ifndef INIT_LIST
#define INIT_LIST

#include <iostream>

struct InitList {
    InitList() { std::cout << "Default ctor" << std::endl; }
    InitList(std::initializer_list<int> l) {
        std::cout << "Initializer list ctor" << l.size() << std::endl;
    }
};

#endif //INIT_LIST
