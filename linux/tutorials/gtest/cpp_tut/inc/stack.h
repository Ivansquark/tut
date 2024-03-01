#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename... Args>
void p(Args&&... args) {
    //((std::cout << args), ...);
    ((std::cout << std::forward<Args>(args)), ..., (std::cout << " "));
    std::cout << std::endl;
}

template <typename U>
struct Heavy {
    Heavy(U t) : t_(new U(t)) { p("create"); }
    Heavy(const Heavy& rhs) {
        p("copy");
        t_ = new U(*rhs.t_);
        // std::copy(t_, t_ + 1, rhs.t_);
    }
    Heavy(Heavy&& rhs) {
        p("move");
        t_ = rhs.t_;
        rhs.t_ = nullptr;
    }
    ~Heavy() {
        p("destroy");
        delete t_;
    }
    U& operator*() { return *t_; }
    U* t_ = nullptr;
};

template <typename T>
class Stack {
  public:
    Stack() {
        // p("create Stack");
    }
    ~Stack() {
        // delete all
        // p("delete Stack");
        Node* temp = top;
        Node* next = top;
        while (temp) {
            next = temp->prev;
            delete temp;
            temp = next;
        }
    }
    struct Node {
        // Node(T t) : val(t) {}
        template <typename... Args>
        Node(Args&&... uref) : val(std::forward<Args>(uref)...) {}
        Node* prev = nullptr;
        T val;
    };
    Node* top = nullptr;
    // Node* head = nullptr;
    size_t size() {
        Node* temp = top;
        size_t count = 0;
        while (temp) {
            ++count;
            temp = temp->prev;
        }
        return count;
    }
    template <typename U>
    void push(U&& val) {
        if (!top) {
            top = new Node(std::forward<U>(val));
            // top = head;
        } else {
            Node* cur = top;
            top = new Node(std::forward<U>(val));
            top->prev = cur;
        }
    }
    // void push(T&& val) {
    //     if (!top) {
    //         top = new Node(std::move(val));
    //         // top = head;
    //     } else {
    //         Node* cur = top;
    //         top = new Node(std::move(val));
    //         top->prev = cur;
    //     }
    // }
    // void push(T& val) {
    //     if (!top) {
    //         top = new Node(val);
    //         // top = head;
    //     } else {
    //         Node* cur = top;
    //         top = new Node(val);
    //         top->prev = cur;
    //     }
    // }
    T pop() {
        if (!top) _exit(1);
        Node* temp = top->prev;
        T val = std::move(top->val);
        delete top;        
        top = temp;
        return val;
    }
    T& operator*() { return *top->val; }
    template <typename... Args>
    // void emplace(Args&&... u);
    void emplace(Args&&... u) {
        if (!top) {
            top = new Node(std::forward<Args>(u)...);
            top->prev = nullptr;
        } else {
            Node* temp = top;
            top = new Node(std::forward<Args>(u)...);
            top->prev = temp;
        }
    }
};

// template <typename T>
// template <typename... Args>
// void Stack<T>::emplace(Args&&... u) {
//     if (!top) {
//         top = new Node(std::forward<Args>(u)...);
//     } else {
//         Node* temp = top;
//         top = new Node(std::forward<Args>(u)...);
//         top->prev = temp;
//     }
// }

#endif // STACK_H
