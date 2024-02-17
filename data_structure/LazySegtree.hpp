#pragma once

#include <iostream>
#include <vector>

#include "atcoder/lazysegtree.hpp"
#include "gandalfr/types.hpp"

namespace gandalfr {

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct LazySegtree
    : public atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> {
    using atcoder::lazy_segtree<S, op, e, F, mapping, composition,
                                id>::lazy_segtree;
    const S operator[](int x) { return this->get(x); }
    void print(i32 l, i32 r) {
        for (i32 i = l; i < r; ++i) {
            std::cout << this->get(i) << (i < r - 1 ? " " : "");
        }
        std::cout << std::endl;
    }
};
} // namespace gandalfr
