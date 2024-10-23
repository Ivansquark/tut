#ifndef CONSTEXPR_H
#define CONSTEXPR_H

#include <array>
#include <iostream>
#include <string.h>

constexpr int sqr(int x) { return x * x; }

constexpr bool isPrime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return n != 1;
}

constexpr size_t countPrimes () {
    //size_t a[5] = {1,2,3,4,5};
    //size_t res = 0;
    //size_t* ptr = &res;
    //for(size_t* p = a; p < a + 5; ++p) *ptr += isPrime(*p);
    size_t* x = new size_t[100];
    for(int i = 0; i < 100;  ++i) x[i] = i*i*i;
    int xx = x[99];//x[99];
    delete [] x;
    return xx;
}

int constexpr_test() {
    //std::array<int, sqr(5)> a = {1, 2, 3, 4, 5};
    constexpr bool is5prime = isPrime(sqr(5));
    std::cout << "is5prime = " << is5prime << std::endl;
    std::cout << "countPrimes() "<< countPrimes() << std::endl;
    constexpr size_t CountPrimes = countPrimes();
    std::cout << "CountPrimes = " << CountPrimes << std::endl;
    return 0;
}

#endif // CONSTEXPR_H
