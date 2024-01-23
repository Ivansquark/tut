#ifndef SFINAE_H
#define SFINAE_H
//--------------------- integral constant -------------------------------------
template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T, v>;
    constexpr operator T() const noexcept { return v; }
    constexpr T operator()() const noexcept { return v; }
};
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename T>
struct is_lvalue_reference : false_type {};
template <typename T>
struct is_lvalue_reference<T&> : true_type {};
template <typename T>
struct is_lvalue_reference<T&&> : false_type {};
// struct false_type {
//     static constexpr bool value = false;
//     constexpr operator bool() noexcept { return value; }
// };
// struct true_type {
//     static constexpr bool value = true;
//     constexpr operator bool() noexcept { return value; }
// };

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


//------------------------ move -----------------------------------------------
template <typename T>
remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<remove_reference_t<T>&&>(t);
}
//------------------------ forward --------------------------------------------
template <typename T>
T&& forward(remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}
template <typename T>
T&& forward(remove_reference_t<T>&& t) noexcept {
    static_assert(!is_lvalue_reference<T>::value,
                  "Can not forward an rvalue as an lvalue");
    return static_cast<T&&>(t);
}

#endif // SFINAE_H
