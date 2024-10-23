#ifndef META_H
#define META_H

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeinfo>

// compile time check tipe by compile error
template <typename T>
class CheckType;
// CheckType<decltype(T)> whatType;

template <typename T>
struct is_pointer {
    static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

template <typename T>
const bool is_pointer_v = is_pointer<T>::value;

template <typename T>
void f() {
    if constexpr (is_pointer_v<T>) { T x = nullptr; }
}

template <typename T, typename U>
struct is_same {
    static const bool value = false;
};
template <typename T>
struct is_same<T, T> {
    static const bool value = true;
};
template <typename T, typename U>
const bool is_same_v = is_same<T, U>::value;

template <typename Head, typename... Tail>
struct common_type {
    using type =
        typename common_type<Head, typename common_type<Tail...>::type>::type;
};

// decltype :::: val    -> type                    metafunction
// declval  :::: type   -> expression of type      function

template <typename T>
std::add_rvalue_reference_t<T> declval() noexcept; // unevaluated dummy

template <typename U, typename T>
struct common_type<T, U> {
    using type =
        std::remove_reference_t<decltype(true ? declval<T>() : declval<U>())>;
};
template <typename... Types>
using common_type_t = typename common_type<Types...>::type;

template <typename T, typename U>
struct is_base_of {

};

// template <typename T>
// struct remove_reference {
//    using type = T;
//};
// template <typename T>
// struct remove_reference<T&> {
//    using type = T;
//};
// template <typename T>
// using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
T g() {
    // typename remove_reference<T>::type x;
    // return x;
}

template <typename T>
struct remove_const {
    using type = T;
};
template <typename T>
struct remove_const<const T> {
    using type = T;
};
template <typename T>
using remove_const_t = typename remove_const<T>::type;

///////////////////////////////////////////////////////////////////////////////
///
///     FOLDING EXPRESSIONS
///
///////////////////////////////////////////////////////////////////////////////

// void print(){}

// template <typename Head, typename ...Tail>
// void print(const Head& head, const Tail&... tail) {
//    std::cout << head << " ";
//    print(tail...);
//}

template <typename... Types>
void print(Types&&... obj) {
    // static_assert(is_same_v<Types, const std::String&>);
    //(std::cout << ... << types);
    ((std::cout << std::forward<Types&&>(obj) << " "), ...);
    std::cout << std::endl;
}

template <typename type, typename... args>
void getFuncInfo(type (*func)(args...)) {
    // some code here...
    // here my example:
    ((std::cout << typeid(args).name() << "\n"), ...);
}

template <class T>
std::string type_name1() {
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void (*)(void*)> own(nullptr, std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value) r += " const";
    if (std::is_volatile<TR>::value) r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

template <typename T>
constexpr bool is_lvalue(T&&) {
    return std::is_lvalue_reference<T>{};
}

template <class T>
constexpr std::string_view type_of() {
    // string_view p = __PRETTY_FUNCTION__;
    // return string_view(p.data() + 47, p.find(';', 47) - 47);
    std::string_view name, prefix, suffix;
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr std::string_view type_of() [with ";
    suffix = "; std::string_view = std::basic_string_view<char>";
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}
#endif // META_H
