#include "print.h"
#include <stack>

struct Tree {
    struct Node {
        int val;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* top;
    Tree(int v) : top(new Node(v)) {
        // top->left = new Node(1);
        // top->right = new Node(1);
        // top->right->right = new Node(3);
        // top->right->left = new Node(3);
        // top->left->right = new Node(3);
        // top->left->left = new Node(3);
    }
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
        inOrderPrint(curr->left);
        Print::print(curr->val);
        inOrderPrint(curr->right);
    }
    void preOrderPrint(Node* curr) {
        if (!curr) return;
        Print::print(curr->val);
        preOrderPrint(curr->left);
        preOrderPrint(curr->right);
    }
    void postOrderPrint(Node* curr) {
        if (!curr) return;
        postOrderPrint(curr->left);
        postOrderPrint(curr->right);
        Print::print(curr->val);
    }
    void it_inOrderPrint(Node* curr) {
        using namespace std;
        if (!curr) return;
        std::stack<Node*> st;
        while (!st.empty() || curr) {
            if (!st.empty()) {
                curr = st.top();
                st.pop();
                Print::print(curr->val);
                if (curr->right) {
                    curr = curr->right;
                } else
                    curr = 0;
            }

            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
        }
    }
    bool isSim() {
        if (!top) return false;
        return isSimHelper(top->left, top->right);
    }
    bool isSimHelper(Node* left, Node* right) {
        if (!left && !right) return true;
        if (!left || !right) return false;
        return (left->val == right->val) &&
               isSimHelper(left->left, right->right) &&
               isSimHelper(right->left, left->right);
    }
};

using namespace Print;
int main() {
    Tree t(5);
    t.push(2);
    t.push(7);
    t.printPre();
    print();
    t.printIn();
    print();
    t.printPost();
    print(t.isSim());

    return 0;
}
