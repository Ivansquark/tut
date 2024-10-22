#include "allocate.h"
#include "concepts.h"
#include "constexpr.h"
#include "init_list.h"
#include "leetcode.h"
#include "meta.h"
#include "my_string.h"
#include "rvalue.h"
#include "sfinae.h"
#include "vect.h"

#include <iostream>
#include <list>
#include <string.h>
#include <vector>

const int& g(const int& a) {
    int* z = remove_const_t<int*>(&a);
    // int* z = &a; //ce
    (*z)++;
    return a;
}

void checkSfinae() noexcept;
void forward_check();
int main() {
    InitList l1{};
    InitList l21{0};
    InitList l2{{}};
    InitList l12({});
    InitList l3{{{}}};
    // InitList l4{{{{}}}};

    std::vector<int> vvv{24, 3};
    Solution sol;
    std::cout << sol.largestNumber(vvv) << std::endl;
    std::clog << sol.largestNumber(vvv) << std::endl;
    checkSfinae();
    // constexpr_test();
    //
    std::cout << "sizeof(int) = " << sizeof(int) << std::endl;

    forward_check();
    return 0;
}

void vector_check() {
    Vector<int> v;
    v.reserve(10);
    v.push_back(5);
    v.push_back(6);
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it;
    }
    // void (Vector<int>::*ptr)(const int&) = &Vector<int>::push_back;
    // std::cout << "ptr to method: " << (void*&)ptr << std::endl;
    // printf("%p\n", ptr);
    // const int& (*p)(const int&) = &g;
    // std::cout << "ptr to function: " << &*(size_t*)(void*&)p << std::endl;
    // printf("%p\n", p);

    Vector<bool> vbool(false);
    for (int i = 0; i < 10; i++) {
        vbool.push_back(true);
        std::cout << vbool[i];
    }
    vbool.push_back(false);
    std::cout << std::endl;
    std::cout << vbool[10] << vbool[11] << " size: " << vbool.size()
              << std::endl;
    for (Vector<bool>::iterator it = vbool.begin(); it != vbool.end(); ++it) {
        const bool& b = *(it);
        std::cout << b;
    }
}

void rvalue_check() {
    // CheckType<common_type_t<char, int, long long> > whatType;
    String s;
    String ss("opa");
    s = ss;
    std::cout
        << is_same_v<String, std::remove_reference<String&>::type> << std::endl;
    std::cout << "eto pisdets" << std::endl;
    int z = 5;
    print('a', "opa", 'o', z);
    const int a = 5;
    std::cout << g(a) << std::endl;
    if constexpr (1) {
        std::cout << "const" << std::endl;
    }
    std::cout << "\nrval:\n";
    foo_uref(1);
    static_assert(is_same_v<decltype(rref), int&&>);
    foo_curef((static_cast<decltype(move(crref))>(crref)));
    foo_curef(move(crref));
    foo_uref(crref);
}

void forward_check() {
    showBar(10);
    showBar(val);
    showBar(move(val));
    showBar(move(cval));
    std::string&& str = std::forward<std::string>(std::string{'4'});
    print(std::move(&str));
    uint64_t ci = 0;
    print("lref type: ", type_of<decltype(ci)>());

    print(sizeof(ci));
}

template <typename T, typename = enable_if_t<std::is_same_v<std::list<int>, T>>>
void opa(const T& t) {
    print("opa sz = ", t.size());
}
void opa(...) { print("opa()...", "opa"); }

void checkSfinae() noexcept {
    Vector<int> v(1, 1);
    sfoo(std::move(v));
    sfoo(1);
    print(has_method_construct_v<Test, int>);
    std::list<int> l{1, 1};
    std::list<char> lc;
    std::cout << has_method_size_v<std::list<int>> << std::endl;
    opa(v);
    opa(l);
    //throw("opa");
}
