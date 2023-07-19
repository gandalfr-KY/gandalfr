#pragma once

#include <vector>

class multi_iter {
private:
    int* lim;
    int* it;
    int depth;
    int d;

public:
    multi_iter() : lim(nullptr), it(nullptr), depth(0), d(0) {}
    multi_iter(const std::vector<int>& limits) : depth(limits.size()), d(0) {
        lim = new int[depth];
        it = new int[depth];
        for (int i = 0; i < depth; ++i) {
            lim[i] = limits[i];
            it[i] = 0;
        }
    }

    ~multi_iter() {
        delete[] lim;
        delete[] it;
    }

    multi_iter& operator++() {
        for (d = 0; d < depth && ++it[d] == lim[d]; ++d)
            it[d] = 0;
        return *this;
    }

    multi_iter operator++(int) {
        multi_iter tmp(*this);
        operator++();
        return tmp;
    }

    void init() { std::fill(it, it + depth, 0), d = 0; }

    bool fin() const { return d == depth; }

    int operator[](int idx) const { return it[idx]; }
};
