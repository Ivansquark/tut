#ifndef SFINAE_H
#define SFINAE_H
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
template <typename T>
T&& forward(remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}

#endif // SFINAE_H
