#include "print.h"

using namespace Print;

int main() {
    std::string s = "Hello world!!!";
    std::string s1 = "Hello world1!!!";
    print(std::move(s), s1, "opa", 1, 2, 3);
    //s1 = std::move(s);
    print(s);
    return 0;
}
