#ifndef CPP17_H
#define CPP17_H

#include <array>
#include <charconv>
#include <iostream>
#include <iterator>
#include <ostream>

// new features:
//
// fold expressions
// template<auto n> for non type (constexpr objects)
// if constexpr
// constexpr lambda
// structured binding: int arr[2] = {1,2}; auto[a,b] = arr;
// std::array<int,6> arr; auto& [a, b, c, d, e, f] = *(int(*)[6])arr.data();
// [[maybe_unused]]
// alignas(4) for dinamyc allocation too
// std::filesystem
// std::optiional, std::any, std::variant
// std::string_view
// namespace ns1::ns2
// std::invoke, std::size, std::data и std::empty
// std::to_chars, std::from_chars

using std::cout;
using std::endl;
class Check {
  public:
    Check() { cout << "Check()" << endl; }
    Check(int i) : i(i) { cout << "Check(int)" << endl; }
    Check(const Check&) { cout << "Check(const Check&)" << endl; }
    Check& operator=(const Check&) {
        cout << "operator=(const&)" << endl;
        return *this;
    }
    Check(Check&&) { cout << "Check(Check&&)" << endl; }
    Check& operator=(Check&&) {
        cout << "operator=(&&)" << endl;
        return *this;
    }
    int i = 0;

  private:
    friend std::ostream& operator<<(std::ostream& strm, const Check& other) {
        strm << other.i << endl;
        return strm;
    }
};

template <typename... Args>
constexpr auto sum(Args&&... args) {
    return (args + ... + 1);
}

template <typename... Args>
void print1(Args&&... args) {
    using std::cout;
    using std::endl;
    ((cout << std::forward<Args>(args) << " "), ...);
    cout << endl;
    //(... ,(cout << (args)));
}
void cpp17_test() {
    Check check(1);
    print1(Check((check)), "opa", "jopa");
    print1(sum(1, 2, 3, 4), sum(3, 7));

    // to_char
    // char arr[10];
    std::array<int, 6> arr;
    std::fill(std::begin(arr), std::end(arr), 'A');
    for (auto&& i : arr) { i = 'B'; }
    arr[5] = '\0';
    auto& [a, b, c, d, e, f] = *(int(*)[6])arr.data();
    print1("binding: ", a='O', b, c, d, e, f);
    print1("binding: ", a, b, c, d, e, f);
    a = 'O'; f = '\0';
    print1((char*)(arr.data()));
    for(auto&& i : arr) {
        print1(i);
    }
    // cout << arr << endl;
    //[[maybe_unused]] auto res =
    //    std::to_chars(std::begin(arr), std::end(arr), 3.14F);
    [[maybe_unused]] auto res =
        std::to_chars((char*)std::begin(arr), (char*)std::end(arr), 3.14F);
    // print1(arr.data()[0], 3.14);
    // from char
    float val;
    std::from_chars((char*)arr.data(), (char*)(arr.data() + 3), val);
    print1(val + 5, std::size(arr));
}

#endif // CPP17_H
