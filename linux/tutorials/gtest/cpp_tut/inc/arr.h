#ifndef ARR_H
#define ARR_H

#include <iterator>
template <typename T, size_t U>
class Arr {
    T arr[U];

  public:
    Arr() = default;
    T& operator[](size_t num) { return arr[num]; }
    Arr(std::initializer_list<T> t) { std::copy(t.begin(), t.end(), arr); }
    class Iterator
    //: public std::iterator_traits<std::random_access_iterator_tag> {
    //: public std::iterator<std::random_access_iterator_tag, T> {
    {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;   // or also value_type*
        using reference = T&; // or also value_type&
        using iterator_category = std::random_access_iterator_tag;

      public:
        Iterator(T* ptr) : m_ptr(ptr) {}
        T& operator*() const { return *m_ptr; }
        T* operator[]() { return m_ptr; }
        Iterator& operator++() {
            ++m_ptr;
            return *this;
        } // preincrement
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        } // postincrement
        Iterator& operator--() {
            --m_ptr;
            return *this;
        } // predecrement
        Iterator operator--(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        } // postdecrement
        Iterator& operator+=(size_t val) {
            m_ptr += val;
            return *this;
        }
        Iterator& operator-=(size_t val) {
            m_ptr -= val;
            return *this;
        }
        size_t operator-(const Iterator& rhs) { return m_ptr - rhs.m_ptr; }
        bool operator<=>(const Iterator&) const = default;
        // bool operator==(const Iterator& rhs) { return (m_ptr == rhs.m_ptr); }
        // bool operator!=(const Iterator& rhs) { return (m_ptr != rhs.m_ptr); }

      private:
        T* m_ptr;
    };
    Iterator begin() { return Iterator(&arr[0]); }
    Iterator end() { return Iterator(&arr[U]); }
};

#endif // ARR_H
