
#ifndef __LIST_CPP__
#define __LIST_CPP__

#include <bits/stdc++.h>

template <typename T>
struct Node {
    Node *next;
    Node *back;
    T data;
    Node(T data, Node *back = nullptr, Node *next = nullptr) :
        data(data), back(back), next(next) {}
};

template <typename T>
class list {
    struct Node {
        Node *next;
        Node *back;
        T data;
        Node(T data, Node *back = nullptr, Node *next = nullptr) :
            data(data), back(back), next(next) {}
        ~Node() {}
    };
    Node *head;
    Node *tail;
    int _size;

    class Iterator {
    private:
        Node *node;

    public:
        Iterator(Node *node) : node(node) {}
        T &operator*() {
            return node->data;
        }
        Iterator operator++() {
            node = node->next;
            return *this;
        }
        Iterator operator--() {
            node = node->back;
            return *this;
        }
        bool operator!=(const Iterator &other) const {
            return node->data != other.node->data;
        }
    };

public:
    list() : head(nullptr), tail(nullptr), _size(0) {}
    constexpr int size() const {
        return _size;
    }
    Node *gethead() const {
        return head;
    }
    void popback() {
        if (size() > 1) {
            tail = tail->back;
            delete tail->next;
            tail->next = nullptr;
        } else if (size() == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            throw std::out_of_range("List is Empty");
        }
        --_size;
    }
    bool empty() const {
        return head == nullptr;
    }

    void pushback(T data) {
        if (size() == 0) {
            head = tail = new Node(data);
        } else {
            tail->next = new Node(data, tail);
            tail = tail->next;
        }
        ++_size;
    }
    void insert(T data, int index) {
        if (index < 0 || index > _size) {
            throw 0;
        } else if (size() == index || size() == 0) {
            pushback(data);
            return;
        } else if (index == 0) {
            head->back = new Node(data, nullptr, head);
            head = head->back;
        } else {
            auto cur = head;
            for (int i = 0; i < index - 1; ++i) {
                cur = cur->next;
            }
            cur->next = cur->next->back = new Node(data, cur, cur->next);
        }
        ++_size;
    }
    void remove(int index) {
        if (size() == 0 || index == size()) {
            throw 0;
        } else if (size() == 1 || size() - 1 == index) {
            popback();
            return;
        } else if (index == 0) {
            head = head->next;
            delete head->back;
            head->back == nullptr;
        } else {
            auto cur = head;
            for (int i = 0; i < index; ++i) {
                cur = cur->next;
            }
            cur->back->next = cur->next;
            cur->next->back = cur->back;
            delete cur;
        }
        --_size;
    }
    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    void print() const {
        std::cout << std::endl;
        for (auto cur = head; cur != nullptr; cur = cur->next) {
            std::cout << cur->data << ' ';
        }
    }
    // ~list() {
    //     delete head;
    //     delete tail;
    //     tail = nullptr;
    //     head = nullptr;
    // }
};
#endif // __LIST_CPP__
