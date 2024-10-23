#ifndef PRINT_H
#define PRINT_H

#include <iostream>

#if 1
template <typename... Args>
void print(Args&&... args) {
    ((std::cout << std::forward<Args>(args) << " "), ...,
     (std::cout << std::endl));
    std::cout << std::endl;
}
#else
template <typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ..., (std::cout << std::endl));
}
#endif

#endif // PRINT_H
