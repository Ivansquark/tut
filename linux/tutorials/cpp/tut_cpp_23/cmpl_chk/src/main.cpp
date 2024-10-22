//#include "cocheck.h"
#include "conc.h"
#include "which.h"

using namespace Print;

int main() {

    //----- requires ----------------------------------------------------------
    //print(Shiftable<char>);

    //Gpios<PA, ALTERNATE> pa0;
    Uart<Port::PB, 1, Port::PB, 2, Baud::B9600> u0;
    
    Which::Uart<1, Which::No> w;
    Which::s();

    return 0;
}
