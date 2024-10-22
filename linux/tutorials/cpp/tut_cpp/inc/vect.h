#ifndef VECT_H
#define VECT_H

//#include <allocator>
#include <iostream>
#include <memory>
#include <stddef.h>
#include <string.h>

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
  public:
    using AllocTraits = std::allocator_traits<Alloc>;
    Alloc alloc = Alloc();
    Vector(const Alloc& alloc = Alloc())
        //: begin_(reinterpret_cast<T*>(new char[CAP + sizeof(T)])),
        // end_(begin_),
        : alloc(alloc), begin_(AllocTraits::allocate(this->alloc, CAP)),
          end_(begin_), cap(CAP) {
        // default constructor
        T* it = begin_;
        for (; it != end_; it++) {
            // it = new (it) T;
            AllocTraits::construct(this->alloc, it, 0);
        }
    }
    Vector(size_t count, T value, const Alloc& alloc = Alloc())
        : alloc(alloc), begin_(AllocTraits::allocate(this->alloc, count)),
          end_(begin_ + count),
          buf_end((count > cap) ? (begin_ + count) : (begin_ + CAP)),
          // buf_end((count > CAP) ? (begin_ + count) : (begin_ + CAP)),
          cap((count > CAP) ? count : CAP) {
        // simple constructor
        T* it = begin_;
        for (; it != end_; it++) {
            AllocTraits::construct(this->alloc, it, value);
        }
    }
    Vector(const Vector& other)
        : alloc(other.alloc),
          begin_(AllocTraits::allocate(this->alloc, other.size())),
          end_(begin_ + other.size()), buf_end(begin_ + other.CAP),
          cap(other.cap) {}
    ~Vector() {
        T* it = begin_;
        for (; it != end_; it++) {
            // it->~T();
            AllocTraits::destroy(alloc, it);
        }
        // delete[] reinterpret_cast<char*>(begin_);
        AllocTraits::deallocate(alloc, begin_, size());
    }
    void push_back(const T&& t) noexcept {
        emplace_back(std::move(t));
    }
    void push_back(const T& t) noexcept {
        emplace_back(t);
    }
    template <typename&&... Args>
    void emplace_back(const Args&... args) noexcept {
        if (size() < full_size() - 1) {
            // end_ = new (end_) T(args...);
            AllocTraits::construct(alloc, end_, std::forward<Args>(args)...);
            ++end_;
        } else {
            // expand cap => resize
            resize(full_size() + 2 * CAP);
            // end_ = new (end_) T(args...);
            AllocTraits::construct(alloc, end_, std::forward<Args>(args)...);
            ++end_;
        }
    }

    void reserve(size_t s) noexcept {
        if (s > full_size()) {
            // copy values to new dinamyc mem
            // T* new_begin = reinterpret_cast<T*>(new char[s * sizeof(T)]);
            T* new_begin = AllocTraits::allocate(alloc, s);
            T* it = begin_;
            T* jt = new_begin;
            for (; it != end_; it++) {
                *jt = *it;
                jt++;
                // it->~T();
                AllocTraits::destroy(alloc, it);
            }
            buf_end = new_begin + s;
            end_ = new_begin + size();
            // delete[] reinterpret_cast<char*>(begin_);
            AllocTraits::deallocate(alloc, begin_, s);
            begin_ = new_begin;
        }
    }

    size_t size() const { return end_ - begin_; }

  private:
    T* begin_ = nullptr;
    T* end_ = nullptr;
    T* buf_end = nullptr;
    size_t cap = CAP;
    size_t full_size() const { return buf_end - begin_; }
    void resize(size_t s) {
        if (s > full_size()) {
            // copy values to new dinamyc mem
            // T* new_begin = reinterpret_cast<T*>(new char[s * sizeof(T)]);
            T* new_begin = AllocTraits::allocate(alloc, s);
            T* it = begin_;
            T* jt = new_begin;
            for (; it != end_; it++) {
                *jt = *it;
                jt++;
                // it->~T();
                AllocTraits::destroy(alloc, it);
            }
            buf_end = new_begin + s;
            end_ = new_begin + size();
            // delete[] reinterpret_cast<char*>(begin_);
            AllocTraits::deallocate(alloc, begin_, s);
            begin_ = new_begin;
            cap = full_size();
        }
    }
    // constants:
  private:
    static constexpr size_t CAP = 5;

  public:
    // friend class iterator;
    class iterator {
      public:
        Vector& vect;
        iterator(Vector& is) : vect(is), index(0) {}
        iterator(Vector& is, bool) : vect(is), index(is.size()) {}
        iterator(const iterator& other) { this = other; }
        const iterator& operator=(const iterator& other) { this = other; }
        T& operator++() { return vect[++index]; }
        T operator++(int) {
            auto tmp = vect[index];
            ++index;
            return tmp;

        }
        T& operator--() { return vect[--index]; }
        T operator--(int) {
            auto tmp = vect[index];
            --index;
            return tmp;
        }
        T& operator*() { return vect[index]; }
        bool operator==(const iterator& it) { return index == it.index; }
        bool operator!=(const iterator& it) { return index != it.index; }

      private:
        size_t index;
    };
    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(*this, true); }
    T& operator[](size_t index) { return *(begin_ + index); }
};

// --------------  Vector bool ------------------------------------------------

template <>
class Vector<bool> {
  public:
    Vector() : arr(new char[CAP]), sz(CAP), cap(CAP) {}
    Vector(bool val) : arr(new char[CAP]()), sz(CAP), cap(CAP) {
        BitReference(arr, 0) = val;
    }
    Vector(const Vector<bool>& other) {
        delete[] arr;
        this->arr = other.arr;
        this->sz = other.sz;
        this->cap = other.cap;
    }
    ~Vector() { delete[] arr; }
    struct BitReference {
        BitReference(char* arr, size_t index = 0)
            : chunk(arr + (index >> 3)), bit(index & 0b111) {
            //*(arr + (index >> 3)) = index & 0b111;
        }
        char* chunk;
        char bit;
        BitReference operator=(bool b) {
            if (b) {
                *chunk |= 1 << bit;
            } else {
                *chunk &= ~(1 << bit);
            }
            return *this;
        }
        operator bool() const { return *chunk & (1 << bit); }
    };
    BitReference operator[](size_t index) {
        // index/7 and last thre bits in index
        return BitReference(arr + (index >> 3), index & 0b111);
    }
    void push_back(bool value) {
        if (!(sz % 8)) {
            // expand
            char* newArr = new char[2 * sz]();
            // std::uninitialized_copy(arr, arr + sz/8, newArr);
            std::uninitialized_move(arr, arr + sz / 8, newArr);
            // memcpy(newArr, arr, sz / 8);
            delete[] arr;
            arr = newArr;
        }
        BitReference(arr, sz) = value;
        ++sz;
    }
    size_t size() { return sz; }
    friend class iterator;
    class iterator {
      public:
        iterator(Vector<bool>& v) : v(v) {}
        iterator(Vector<bool>& v, bool) : v(v), index(v.size()) {}
        iterator(const iterator& other) : v(other.v) { *this = other; }
        const iterator& operator=(const iterator& other) {
            *this = other;
            return *this;
        }

      public:
        bool operator+=(size_t val) {
            index += val;
            return v[index];
        }
        bool operator++() { return v[++index]; }
        bool operator++(int) { return v[index++]; }
        bool operator--() { return v[--index]; }
        bool operator--(int) { return v[index--]; }
        bool operator*() { return v[index]; }
        bool operator==(const iterator& it) { return index == it.index; }
        bool operator!=(const iterator& it) { return index != it.index; }

      private:
        Vector<bool>& v;
        size_t index = 0;
    };
    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(*this, true); }

  private:
    char* arr;
    size_t sz;
    size_t cap;
    static constexpr size_t CAP = 1;
};

#endif // VECT_H
