#ifndef RVALUE_H
#define RVALUE_H

#include <meta.h>

#include <iostream>

/*
 *--------------------------+-------------------------------
 *  lvalue                  |   rvalue
 *--------------------------+-------------------------------
 * 1.   identifier (int A)  | 1.    literal (5)
 * ---------------------------------------------------------
 * 2.   =   op=             | 2.    binary + - * / % & | ...
 * 3.   prefix ++ --        | 3.    postfix ++ --
 * 4.   unary *             | 4.    unary & + -
 * 5.   ?: (if both lvalue) | 5.    ?: (if one rvalue)
 * 6.   , (if right lvalue) | 6.    , (if right rvalue)
 * ---------------------------------------------------------
 * 7.   func if ret lvalue  | 7.    func if ret rvalue
 *      reference           |       reference
 * 8.   cast if lval ref    | 8.    cast if rval ref
 */

int a = 1;
int& b = a;
// int& c = 2; // CE Compilation Error
//////////////////////////////////////////////////////////
///
const int& c = 2; // lifetime prolongation
///
//////////////////////////////////////////////////////////
// int&& b_rval = a; // CE
int&& c_rval = 2; // good
int& g_rval = c_rval;
int* g_ptr = &c_rval;
// int&& h = c_rval; //CE
const int const_a = 1;
const int& const_b = const_a;
// const int&& const_c_rval = const_b; // CE
const int&& const_c_rval = (const int&&)const_b; // good
// int&& const_c_rval = (const int&&)const_b; // CE const qualifier
const int&& const_c_rval2 = 2; // good
const int& const_g = c_rval;
const int* const_g_ptr = &c_rval;

///////////////////////////////////////////////////////////////////////////////
///     UNIVERSAL REFERENCES
///////////////////////////////////////////////////////////////////////////////
void f(int& x);
void f(int&& x);
// one function gets &lval and &&rval :
template <typename T>
void foo(T&& uval);
// void foo(const T&& uval); // not universal only rval

// reference collapsing:
// & + &    = &
// & + &&   = &
// && + &   = &
// && + &&  = &&
// rvalue:
// val == int&& rref    => T = int&&;   => foo(int&& &&rref)   == foo(int&& val)
// lvalue:
// val == int& lref   => T = int&;    => foo(int& && val) == foo(int& val)
// val == int lval    => T = int;    => foo(int& & val) == foo(int& val)
//
//////////////////////////////////////////
///     TEMPLATE TYPE DEDUCTION
//////////////////////////////////////////
//  template <typename T>
//  void foo(paramType param); //paramType = (const?)T(&?)(&?)

// case 1
template <typename T>
void foo_lref(T& t) {
    std::cout << "T&: " << t << std::endl;
}
template <typename T>
void foo_clref(const T& t) {
    std::cout << "const T&: " << t << std::endl;
}
template <typename T>
void foo_uref(T&& t) {
    std::cout << "T&&: " << t << std::endl;
}
// get only rvalue ref (if not implemented non const foo_uref)
template <typename T>
void foo_curef(const T&& t) {
    std::cout << "const T&&: " << t << std::endl;
}
template <typename T>
void foo_val(T t) {
    std::cout << "T: " << t << std::endl;
}

// foo_ref
int val = 1;           // paramType==int&,         T==int
const int cval = 1;    // paramType==const int&,   T==const int
int& lref = val;       // paramType==int&,         T==int
const int& clref = 2;  // paramType==const int&,   T==const int
int&& rref = 3;        // paramType==int&,         T==int
const int&& crref = 3; // paramType==const int&,   T==const int

// foo_clref
// int val = 1;            // paramType==const int&, T==int
// const int cval = 1;     // paramType==const int&, T==int
// int& lref = val;        // paramType==const int&, T==int
// const int& clref = 1;   // paramType==const int&, T==int
// int&& rref = 1;         // paramType==const int&, T==int
// const int&& crref = 1;  // paramType==const int&, T==int

// foo_uref
// int val = 1;            // paramType==int&, T==int&
// const int cval = 1;     // paramType==const int&, T==const int&
// int& lref = val;        // paramType==int&, T==&int
// const int& clref = 1;   // paramType==const int&, T==const int&
// int&& rref = 1;         // paramType==int&&, T==int
// const int&& crref = 1;  // paramType==const int&&, T==const int
// 1;                      // paramType==int&&, T==int

///////////////////////////////////////////////////////////////////////////////
///
///                 MOVE
///
///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct remove_reference {
    using type = T;
};
template <typename T>
struct remove_reference<T&> {
    using type = T;
};
template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;
// through typedef
// template <typename T>
// struct remove_reference_t {
//    typedef typename remove_reference<T>::type type;
//};
// template <typename T>
// constexpr typename remove_reference_t<T>::type&& move(T&& t) {
//    return static_cast<typename remove_reference_t<T>::type&&>(t);
//}

// template <typename T>
// constexpr typename remove_reference<T>::type&& move(T&& t) {
//    return static_cast<typename remove_reference<T>::type&&>(t);
//}
// C++14
template <typename T>
decltype(auto) move(T&& param) {
    return static_cast<remove_reference_t<T>&&>(param);
}

///////////////////////////////////////////////////////////////////////////////
///
///                 FORWARD
///
///////////////////////////////////////////////////////////////////////////////
void bar(const int& val) {
    std::cout << "bar const T& val: " << val << std::endl;
}
void bar(int&& val) {
    //(*((long long*)&val)) = 0;
    std::cout << "bar T&& val: " << val << std::endl;
}

template <typename T>
void showBar(T&& val) {
    if(is_lvalue(std::forward<decltype(val)>(val))) {
        std::cout << "lvalue ";
    } else {
        std::cout << "not lvalue ";
    }
    print("showBar val type: ",
          type_of<decltype(val)>());
    print("showBar T type: ",
          type_of<decltype(std::forward<decltype(val)>(val))>());
    bar(val);
    // bar(std::move(std::remove_const_t<T>(val)));
    // bar(std::forward<T&&>(const_cast<std::remove_const_t<T>&>(val)));
    // bar(std::forward<decltype(val)>(val));
    bar(std::forward<T&&>(val));
}

// forward must return universal (forward) reference
// forward an lvalue as either an lvalue or an rvalue
template <typename T>
constexpr T&& forward(typename remove_reference<T>::type& val) noexcept {
    return static_cast<T&&>(val);
}

// forward an rvalue as an rvalue
template <typename T>
constexpr T&& forward(typename remove_reference<T>::type&& val) noexcept {
    // to unable next example:  "func(std::forward<int&>(7));"
    static_assert(
        !std::is_lvalue_reference<T>::value,
        "std::forward must not be used to convert an rvalue to an lvalue");
    return static_cast<T&&>(val);
}

#endif // RVALUE_H
