#include <bits/stdc++.h>

class SearchTree {
    struct Node {
        long long data;
        Node *left;
        Node *right;
        Node(long long data, Node *left = nullptr, Node *right = nullptr) :
            data(data), left(left), right(right) {}
    };
    Node *root;
    void insertt(Node *cur, long long data) {
        if (cur->data > data) {
            if (cur->left != nullptr)
                insertt(cur->left, data);
            else {
                cur->left = new Node(data);
            }
        } else {
            if (cur->right != nullptr)
                insertt(cur->right, data);
            else {
                cur->right = new Node(data);
            }
        }
    }

public:
    SearchTree() : root(nullptr) {}
    void insert(long long data) {
        if (root == nullptr) {
            root = new Node(data);
        } else
            insertt(root, data);
    }
    bool search(long long num) {
        auto cur = root;
        while (cur != nullptr) {
            if (cur->data == num) {
                return true;
            } else if (cur->data < num) {
                cur = cur->right;
            } else
                cur = cur->left;
        }
        return false;
    }
};
