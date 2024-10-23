#ifndef CONC_H
#define CONC_H

#include "print.h"

#include <algorithm>
#include <iterator>
#include <vector>

enum Port {
    PA,
    PB
};

enum Func {
    PUSH_PULL,
    PULL_UP,
    ALTERNATE,
};

enum Baud {
    B9600 = 9600,
    B115200 = 115200
};

template <Port port, int num, Func func>
class Gpios {
  public:
    //using _Func = Func;
    Gpios() {
        if constexpr (func == ALTERNATE) {
            Print::print("ALTERNATE");
        }
    }
};

// template <class Gpios<Port port, Func func>>
// concept IsAlt = func == ALTERNATE;
//  concept IsAlt = requires() { func == ALTERNATE; };
//  concept IsAlt = requires() { func == PUSH_PULL; };
//  concept IsAlt = requires(Gpios::_Func func) { Gpios::func == PUSH_PULL; };

template <Func func>
concept IsAlt = func == ALTERNATE;
template <Baud baud>
concept IsBaud = (baud == Baud::B9600 || baud == Baud::B115200);

// template <Port port, Func func>
template <Port port_tx, int port_tx_num, Port port_rx, int port_rx_num,
          Baud baud>
    requires IsBaud<baud>
class Uart {
  public:
    Uart() { Print::print("Uart"); }
    Gpios<port_tx, port_tx_num, Func::ALTERNATE> tx;
    Gpios<port_rx, port_rx_num, Func::PULL_UP> rx;
};

template <typename T>
constexpr bool Shiftable = requires(T i) { i >> 1; };

#endif // CONC_H
