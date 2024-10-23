#ifndef PRINT_H
#define PRINT_H

#include <iostream>
// #include <string_view>

namespace Print {

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

template <typename... Args>
void print(Args&&... args) {
    int i = 0;
    (
        [&] {
            if constexpr (std::is_same_v<decltype(args), std::string>) {
                std::cout << "string on position = " << i << std::endl;
            } else if constexpr (std::is_same_v<decltype(args), std::string&>) {
                std::cout << "string& on position = " << i << std::endl;
            } else if constexpr (std::is_same_v<decltype(args),
                                                std::string&&>) {
                std::cout << "string&& on position = " << i << std::endl;
                // std::string s(std::move(args)); // for test
            }
            i++;
        }(),
        ...);
    // if constexpr ((std::is_same_v<Args, std::string&> || ...)) {
    //     (std::cout << "string" << std::endl);
    // };

    ((std::cout << std::forward<Args>(args) << " "), ...);
    std::cout << std::endl;
}

} // namespace Print

#endif // PRINT_H
