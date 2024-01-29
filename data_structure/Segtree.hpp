#pragma once
#include <assert.h>

#include <functional>
#include <iostream>
#include <vector>

#include "atcoder/segtree.hpp"
#include "gandalfr/types.hpp"

namespace gandalfr {

template <class S, S (*op)(S, S), S (*e)()>
struct Segtree : public atcoder::segtree<S, op, e> {
    using atcoder::segtree<S, op, e>::segtree;
    const S operator[](int x) const { return this->get(x); }
    void print(i32 l, i32 r) const {
        for (i32 i = l; i < r; ++i) {
            std::cout << this->get(i) << (i == r - 1 ? " " : "");
        }
        std::cout << std::endl;
    }
};
} // namespace gandalfr
