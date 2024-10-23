#ifndef SFINAE_H
#define SFINAE_H

#include <iostream>

template <typename T, T value_>
struct integral_constant {
    static const T value = value_;
};

struct true_type : public integral_constant<bool, true> {};
struct false_type : public integral_constant<bool, false> {};

// check method size
template <typename T>
auto sfoo(const T& t) -> decltype(T().size()) {
    size_t sz = t.size();
    std::cout << "void foo(const T&), sz = " << sz << std::endl;
    return 0;
}

int sfoo(...) {
    std::cout << "int foo(...)" << std::endl;
    return 0;
}
// check method presence in class
template <typename T, typename... Args>
struct has_method_size {
  private:
    // comma trick (return type int)
    template <
        typename TT, typename... AArgs,
        typename = decltype(std::declval<TT>().size(std::declval<AArgs>()...))>
    static true_type test(int);
    template <typename>
    static false_type test(...);

  public:
    using type = decltype(test<T, Args...>(0));
};

template <typename T, typename... Args>
bool has_method_size_v =
    std::is_same_v<typename has_method_size<T, Args...>::type, true_type>;

// check method presence in class
template <typename T, typename... Args>
struct has_method_construct {
  private:
    // comma trick (return type int)
    template <typename TT, typename... AArgs>
    static auto f(int)
        -> decltype(std::declval<TT>().construct(std::declval<AArgs>()...),
                    int()) {
        return 1;
    }
    template <typename...>
    static char f(...) {
        return 0;
    }

  public:
    // static const bool value = sizeof(f<T, Args...>(0)) == sizeof(int);
    static const bool value = std::is_same<decltype(f<T, Args...>(0)), int>();
};

template <typename T, typename... Args>
bool has_method_construct_v = has_method_construct<T, Args...>::value;

struct Test {
    void construct(int);
};

//------------------- std::enable_if ------------------------------------------

template <typename T, typename = std::enable_if_t<std::is_class_v<T>>>
void ifenable(const T&) {
    std::cout << "class" << std::endl;
}
void ifenable(...) { std::cout << "no_class" << std::endl; }

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

template <bool B = true, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;


#endif // SFINAE_H
