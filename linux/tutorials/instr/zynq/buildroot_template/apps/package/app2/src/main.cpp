#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Test Cmake!!!" << std::endl;
    if(argc > 1) {
        for(int i = 0; i < argc; ++i) {
            std::cout << argv[i + 1] << std::endl;
        }
    }
    return 0;
}
