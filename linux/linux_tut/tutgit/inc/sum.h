#ifndef SUM_H
#define SUM_H

template <typename... Args>
constexpr auto sum(Args&&... args) {
    return (args + ...);
}

#endif //SUM_H
