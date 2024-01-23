#ifndef PRINT_H
#define PRINT_H

#include <iostream>

template <typename... Args>
void print(Args&&... args) {
    ((std::cout << std::forward<Args>(args) << " "), ...,
     (std::cout << std::endl));
}

#endif // PRINT_H
