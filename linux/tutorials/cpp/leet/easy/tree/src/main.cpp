#include "print.h"
#include <stack>

struct Tree {
    struct Node {
        int val;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* top;
    Tree(int v) : top(new Node(v)) {}
    ~Tree() { freemem(top); }
    void freemem(Node* curr) {
        if (curr) {
            freemem(curr->left);
            freemem(curr->right);
            delete curr;
        }
    }
    void push(int v) {
        Node* curr = top;
        if (v < curr->val) {
            curr->left = p(v, curr->left);
        } else {
            curr->right = p(v, curr->right);
        }
    }
    Node* p(int v, Node* curr) {
        if (!curr) {
            curr = new Node(v);
            curr->left = nullptr;
            curr->right = nullptr;
        } else if (v < curr->val) {
            curr->left = p(v, curr->left);
        } else {
            curr->right = p(v, curr->right);
        }
        return curr;
    }
    int pop() {
        int temp;
        return temp;
    }
    void printPre() { preOrderPrint(top); }
    void printIn() { it_inOrderPrint(top); }
    void printPost() { postOrderPrint(top); }
    void inOrderPrint(Node* curr) {
        if (!curr) return;
        if (curr->left) {
            inOrderPrint(curr->left);
        }
        Print::print(curr->val);
        if (curr->right) {
            inOrderPrint(curr->right);
        }
    }
    void preOrderPrint(Node* curr) {
        if (!curr) return;
        Print::print(curr->val);
        if (curr->left) {
            preOrderPrint(curr->left);
        }
        if (curr->right) {
            preOrderPrint(curr->right);
        }
    }
    void postOrderPrint(Node* curr) {
        if (!curr) return;
        if (curr->left) {
            postOrderPrint(curr->left);
        }
        if (curr->right) {
            postOrderPrint(curr->right);
        }
        Print::print(curr->val);
    }
    void it_inOrderPrint(Node* curr) {
        using namespace std;
        if (!curr) return;
        std::stack<Node*> st;
        st.push(curr);
        while (!st.empty()) {
            Node* tmp = st.top();
            st.pop();

            Print::print(tmp->val);
            if (tmp->right) {
                st.push(tmp->right);
            }
            if (tmp->left) {
                st.push(tmp->left);
            }
        }
    }
};

using namespace Print;
int main() {
    Tree t(4);
    t.push(2);
    t.push(6);
    t.push(7);
    t.push(1);
    t.printPre();
    print();
    t.printIn();
    print();
    t.printPost();

    return 0;
}
