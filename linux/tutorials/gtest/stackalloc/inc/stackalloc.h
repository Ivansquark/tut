#ifndef STACK_ALLOC
#define STACK_ALLOC

#include "print.h"
#include <iostream>
// arena class to allocate memory
template <size_t N, size_t alignment = alignof(long int)>
class arena {
    alignas(alignment) char buf_[N];
    //alignas(alignment) char* buf_;
    char* ptr_;

  private:
    static size_t align_up(size_t n) noexcept {
        return (n + (alignment - 1)) & ~(alignment - 1);
    }

    bool pointer_in_buffer(char* p) noexcept {
        return ((buf_ <= p) && (p <= buf_ + N));
    }

  public:
    ~arena() {
        ptr_ = nullptr;
        print("~arena()");
    }
    arena() noexcept : ptr_(buf_) { print("arena()"); }
    arena(const arena&) = delete;
    arena& operator=(const arena&) = delete;
    // arena(arena&&) = delete;
    arena(arena&&) { print("arena&&"); };
    arena& operator=(arena&& other) {        
        
        //print("other.ptr_ = ", (int*)other.ptr_, "other.buf_",
        //      (int*)other.buf_);
        //print("this.ptr_ = ", (int*)ptr_, "this.buf_", (int*)buf_);
        //size_t size = other.ptr_ - other.buf_;
        buf_ = other.buf_;
        ptr_ = other.ptr_;
        //print("size = ", size);
        //other.deallocate(other.ptr_, other.ptr_ - other.buf_);
        //other.ptr_ = nullptr;
        //allocate(size);

        print("arena&&");
        return *this;
    };
    // arena& operator=(arena&&) = delete;

    char* allocate(size_t n) noexcept {
        auto const aligned_n = align_up(n); // size of current allocation
        if (static_cast<decltype(aligned_n)>(buf_ - ptr_ + N) >= aligned_n) {
            // if fit in buf_  place in buf_
            char* r = ptr_;
            ptr_ += aligned_n;
            std::cout << "allocate on stack" << std::endl;
            print("allocated = ", aligned_n, "bytes");
            return r;
        } else {
            // TODO: set here check about heap
            std::cout << "allocate on heap" << std::endl;
            print("allocated = ", aligned_n, "bytes");
            return static_cast<char*>(::operator new(n));
        }
    }
    void deallocate(char* p, size_t n) noexcept {
        if (!pointer_in_buffer(p)) {
            std::cout << "deallocate from heap" << std::endl;
            print("deallocated = ", n, "bytes");
            ::operator delete(p);
        }
        n = align_up(n);
        if (p + n == ptr_) {
            p = ptr_;
            std::cout << "deallocate from stack" << std::endl;
            print("deallocated = ", n, "bytes");
        }
    }
};

template <typename T, size_t N, size_t Align = alignof(long int)>
class stack_alloc {
  public:
    using value_type = T;
    static auto constexpr alignment = Align;
    static auto constexpr size = N;
    using arena_type = arena<size, alignment>;

  private:
    arena<N, Align> a_;

  public:
    stack_alloc() = default;
    // stack_alloc() { print("stack_alloc()"); }
    //  stack_alloc(const stack_alloc&) = default;
    stack_alloc(const stack_alloc&) {
        // not do here anything
        print("stack_alloc(const stack_alloc&)");
    }
    // stack_alloc(const stack_alloc&) = delete;
    // stack_alloc& operator=(const stack_alloc&) {
    //    print("op= (stack_alloc&)");
    //}
    stack_alloc& operator=(const stack_alloc&) = delete;
    // stack_alloc(stack_alloc&&) = delete;
    // stack_alloc& operator=(stack_alloc&&) = delete;
    stack_alloc(stack_alloc&& other) {
        print("stack_alloc(stack_alloc&&)");
        // std::swap(a_, other.a_);
        //  memcpy(&a_, &other.a_, sizeof(a_));
        //  other.a_.deallocate();
        //  other.a_.deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
        a_ = std::move(other.a_);
    }
    // stack_alloc& operator=(stack_alloc&&) {
    //     print("op= (stack_alloc&&)");
    // }

    // const arena_type& get_arena() const { return &a_; }
    // arena_type& get_arena() { return &a_; }

    // template <class U>
    // stack_alloc(stack_alloc<U, N> a) noexcept {}
    const arena_type& get_arena() const { return a_; }
    arena_type& get_arena() { return a_; }

    template <class Up>
    struct rebind {
        using other = stack_alloc<Up, N, alignment>;
    };

    T* allocate(size_t n) {
        // char* res = a_.template allocate<alignof(T)>(n * sizeof(T));
        char* res = a_.allocate(n * sizeof(T));
        return reinterpret_cast<T*>(res);
    }

    void deallocate(T* p, size_t n) noexcept {
        a_.deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
    }

    template <class U, size_t M, size_t A2>
    bool equals(const stack_alloc<U, M, A2>& rhs) const noexcept {
        return N == M && Align == A2 && &a_ == &rhs.get_arena();
    }
};
template <class T, size_t N, size_t A1, class U, size_t M, size_t A2>
bool operator==(const stack_alloc<T, N, A1>& x,
                const stack_alloc<U, M, A2>& y) noexcept {
    return x.equals(y);
}

template <class T, size_t N, size_t A1, class U, size_t M, size_t A2>
bool operator!=(const stack_alloc<T, N, A1>& x,
                const stack_alloc<U, M, A2>& y) noexcept {
    return !(x == y);
}

#endif // STACK_ALLOC
