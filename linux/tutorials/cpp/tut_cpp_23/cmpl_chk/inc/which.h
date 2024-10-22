#ifndef WHICH_H
#define WHICH_H

#include "print.h"

namespace Which {

enum Dmas {
    NO,
    USE
};

struct No {};
struct Use {};


template <int i, typename T>
class Uart {
  public:
    using Type = T;
    Uart() {}
};

constexpr bool get() { return (Uart::Type) ? true : false; }

template <typename T>
void send() {
    Print::print("T");
}
template <>
void send<No>() {
    Print::print("NO");
}
template <>
void send<Use>() {
    Print::print("USE");
}
// template <>
// void send<Which::Uart::Type>() {
//     Print::print("Type");
// }

void s() {
    Print::print("s");
    send<Uart<1, Use>::Type>();
}

} // namespace Which

#endif // WHICH_H
