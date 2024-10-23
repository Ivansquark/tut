#ifndef COCHECK_H
#define COCHECK_H

#include "print.h"
// #include <mutex>

enum Port {
    PA,
    PB
};

extern bool arr_rcc[2];

template <Port port>
class Gpios {
  public:
    Gpios() {
        // if not setted set Rcc
        setRcc();
    }
    static void setRcc() {
        Print::print("setRcc common");
        [[maybe_unused]] static bool once = [] [[nodiscard]] {
            if constexpr (port == PA) {
                arr_rcc[PA] = true;
                Print::print("setRcc PA");
            } else if constexpr (port == PB) {
                arr_rcc[PB] = true;
                Print::print("setRcc PB");
            }

            return true;
        }();

        //-------- call_once -use mutex - large overhead ----------------------
        // std::call_once(flag, []() {
        //     if constexpr (port == PA) {
        //         arr_rcc[PA] = true;
        //         Print::print("setRcc PA");
        //     } else if constexpr (port == PB) {
        //         arr_rcc[PB] = true;
        //         Print::print("setRcc PB");
        //     }
        // });
    }

    // static std::once_flag flag;
};

#endif // COCHECK_H
