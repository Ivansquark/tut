#ifndef TEST1
#define TEST1

template <typename T>
class TwoNum {
    T val1;
    T val2;

  public:
    TwoNum(T v1, T v2) : val1(v1), val2(v2) {}
    T getVal1() { return val1; }
    T getVal2() { return val2; }
    T getSum() { return val1 + val2; }
};

#endif // TEST1
