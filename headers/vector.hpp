#include <bits/stdc++.h>

template <typename T>
class vector {
    using cvref = const vector &;
    using vref = vector &;

    T *p;
    int _size;
    int _used;

    class Iterator {
        vector<T> *myvec;
        int currentpos;

    public:
        Iterator(vector<T> *vec, int cure) : myvec(vec), currentpos(cure) {}
        int getcurrentpos() const {
            return currentpos;
        }
        vector<T> *getmyvec() const {
            return myvec;
        }
        void operator++() {
            currentpos += 1;
        }
        void operator--() {
            currentpos -= 1;
        }
        T &operator*() {
            return myvec->at(currentpos);
        }
        const T &operator*() const {
            return myvec->at(currentpos);
        }
        bool operator==(const Iterator &rhs) const {
            return myvec == rhs.getmyvec() && currentpos == rhs.getcurrentpos();
        }
        bool operator!=(const Iterator &rhs) const {
            return !(*this == rhs);
        };
    };

public:
    vector(int size = 10) : _size(size), _used(0), p(new T[size]) {}
    vector(int size, int defaults) : _size(size), _used(size), p(new T[size]) {
        for (int i = 0; i < size; ++i) {
            p[i] = defaults;
        }
    }
    constexpr int size() const noexcept {
        return _size;
    }

    vector(cvref other) {
        T *p = new T[other._size];
        for (int i = 0; i < _size; ++i) {
            p[i] = other.p[i];
        }
        _size == other.size();
    }
    vector<T> operator=(cvref other) {
        // if (this == &other) // assigning same vector i.e: v1 = v1;
        //     return *this;
        // if (this->size() >= other.size()) {
        //     for (int i = 0; i < other.size(); ++i) {
        //         p[i] = other.p[i];
        //     }
        //     return *this;
        // }
        T *x = new T[other.size()];
        for (int i = 0; i < other.size(); ++i) {
            x[i] = other.p[i];
        }
        delete[] p;
        p = x;
        _size == other.size();
        return *this;
    }

    void emplace_back(const T &data) {
        if (_used == _size) {
            Reallocate();
        }
        p[_used++] = data;
    }
    void pop_back() {
        _used -= 1;
    }
    Iterator begin() {
        return Iterator((this), 0);
    }
    Iterator end() {
        return Iterator((this), _used);
    }
    void Reallocate() {
        T *p2 = new T[_size * 2];
        for (int i = 0; i < _size; ++i) {
            p2[i] = p[i];
        }
        delete[] p;
        p = p2;
        _size = _size * 2;
    }

    const T &operator[](int index) const {
        if (!(index < _used))
            throw std::out_of_range("Given index is not in range");
        return p[index];
    }
    T &operator[](int index) {
        if (!(index < _used))
            throw std::out_of_range("Given index is not in range");
        return p[index];
    }

    T &at(int index) {
        if (!(index < _used))
            throw std::out_of_range("Given index is not in range");
        return p[index];
    }
    const T &at(int index) const {
        if (!(index < _used))
            throw std::out_of_range("Given index is not in range");
        return p[index];
    }

    bool operator==(cvref other) const {
        if (_size != other.size()) {
            return false;
        }
        for (int i = 0; i < _size; ++i) {
            if (p[i] != other.p[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(cvref other) const {
        return !(*this == other);
    }

    bool Empty() const {
        return _used == 0;
    }

    void print() const {
        for (int i = 0; i < _used; ++i) {
            std::cout << p[i] << ' ';
        }
    }
};
