#ifndef CONCEPTS_H
#define CONCEPTS_H

template <typename T>
bool conc() {
    bool b = requires(T x) {++x;};
    return b;

}

#endif //CONCEPTS_H
