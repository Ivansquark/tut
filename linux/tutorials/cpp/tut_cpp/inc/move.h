#ifndef MOVE_H
#define MOVE_H

#include <iostream>

template <typename T>
void swap(T& a, T&b) {
    T t = std::move(a);
    a = std::move(b);
    b = std::move(t);
}

template <typename T>
std::remove_reference<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference<T>&&>(t);
}


#endif //MOVE_H
