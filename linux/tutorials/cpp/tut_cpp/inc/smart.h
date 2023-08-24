#ifndef SMART_H
#define SMART_H

#include "rvalue.h"

template <typename T>
class unique_ptr {
  private:
    T* ptr = nullptr;

  public:
    unique_ptr(const T* p) : ptr(p) {}
    unique_ptr(const T& unique) = delete;
    unique_ptr& operator=(const unique_ptr& p) = delete;
    unique_ptr(unique_ptr&& other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    unique_ptr&& operator=(unique_ptr&& other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    ~unique_ptr() { delete ptr; }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    T* get() { return ptr; }
};

template <typename T>
class shared_ptr {
  private:
    size_t* counter = nullptr;
    T* ptr = nullptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

  public:
    shared_ptr(T* p) : ptr(p), counter(new size_t(1)) { ++(*counter); }
    shared_ptr(const shared_ptr& other) : counter(other.counter) {
        delete ptr;
        ptr = other.ptr;
        ++(*counter);
    }
    shared_ptr(shared_ptr&& other) : counter(other.counter) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        other.counter = nullptr;
    }

    ~shared_ptr() {
        if (--(*counter) > 1) { return; }
        delete ptr;
        *(counter) = 0;
    }
    T* operator->() { return ptr; }
    T& operator*() { return *ptr; }
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) noexcept {
    return unique_ptr<T>(new T(std::forward<Args...>(args)...));
}
// universal ref
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto ptr = new T(std::forward<Args>(args)...);
    return shared_ptr<T>(ptr);
}

#endif // SMART_H
