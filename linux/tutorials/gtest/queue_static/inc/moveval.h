#ifndef MOVEVAL
#define MOVEVAL

#include "print.h"

template <typename T>
class MoveVal {
  public:
    MoveVal() {}
    constexpr MoveVal(T t) : t_(new T(t)){};
    MoveVal(const MoveVal& o) {
        print("copy ctor");
        if (t_) delete t_;
        t_ = new T(*o.t_);
    }
    MoveVal(MoveVal&& o) {
        if (o == *this) return;
        print("move ctor");
        if (t_) delete t_;
        t_ = o.t_;
        o.t_ = nullptr;
        // std::swap(*this, rhs);
    }
    MoveVal& operator=(const MoveVal& rhs) {
        print("copy operator=");
        if (t_) delete t_;
        t_ = new T(*rhs.t_);
        return *this;
    }
    MoveVal& operator=(MoveVal&& rhs) {
        if (rhs == *this) return *this;
        print("move operator=");
        //std::swap(*this, rhs);
        swap(rhs);
        return *this;
    }
    ~MoveVal() { delete t_; }
    bool operator<=>(const MoveVal& rhs) const = default;
    // bool operator==(const MoveVal& rhs) const { return t_ == rhs.t_; }
    T& getVal() const { return *t_; }
    void swap(MoveVal& o) { std::swap(t_, o.t_); }

  private:
    T* t_ = nullptr;
};
template <typename T>
std::ostream& operator<<(std::ostream& os, const MoveVal<T>& rhs) {
    os << rhs.getVal();
    return os;
}
// specialization
template <typename T>
std::ostream& operator<<(std::ostream& os, const MoveVal<std::string>& rhs) {
    std::stringstream ss;
    ss << rhs.getVal();
    os << ss.str();
    return os;
}
#endif // MOVEVAL
