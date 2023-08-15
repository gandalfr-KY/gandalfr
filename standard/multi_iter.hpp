#pragma once
#define ENABLE_MULTI_FOR

#include <algorithm>
#include <utility>
#include <vector>

using multirange = std::vector<std::pair<int, int>>;

class multi_iter {
  private:
    int *lim;
    int *bs;
    int *it;
    int depth, d;

  public:
    multi_iter(const std::vector<int> &limits)
        : depth(limits.size()), d(depth - 1) {
        lim = new int[depth];
        bs = new int[depth];
        it = new int[depth];
        for (int i = 0; i < depth; ++i) {
            lim[i] = limits[i];
            bs[i] = it[i] = 0;
        }
    }
    multi_iter(const multirange &rngs) : depth(rngs.size()), d(depth - 1) {
        lim = new int[depth];
        bs = new int[depth];
        it = new int[depth];
        for (int i = 0; i < depth; ++i) {
            lim[i] = rngs[i].second;
            bs[i] = it[i] = rngs[i].first;
        }
    }

    ~multi_iter() {
        delete[] lim;
        delete[] bs;
        delete[] it;
    }

    multi_iter &operator++() {
        for (d = depth - 1; d >= 0 && ++it[d] == lim[d]; --d)
            it[d] = bs[d];
        return *this;
    }

    multi_iter operator++(int) {
        multi_iter tmp(*this);
        operator++();
        return tmp;
    }

    void init() { std::copy(bs, bs + depth, it); }

    bool fin() const { return d == -1; }

    int operator[](int idx) const { return it[idx]; }
};
