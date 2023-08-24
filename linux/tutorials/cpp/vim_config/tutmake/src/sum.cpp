#include "sum.h"

template <typename T>
Sum<T>::Sum(T x, T y) {
    first = x;
    second = y;
    result = x+y;
}

template <typename T>
Sum<T>::~Sum<T>(){}

template <typename T>
void Sum<T>::printSum() {
    int temp = static_cast<int>(result);
    printf("%d\n", temp);
}
template <typename T>
void Sum<T>::sum(){
    result = first + second;
}

template class Sum<int>;
