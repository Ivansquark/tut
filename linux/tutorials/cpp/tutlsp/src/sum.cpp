#include "sum.h"

template <typename T>
Sum<T>::Sum(T a, T b) {
    this->a = a; this->b = b; sum = a+b;
}

template <typename T>
void Sum<T>::print() {
    std::cout << "Sum = " << sum <<std::endl;
}

template class Sum<int>;
