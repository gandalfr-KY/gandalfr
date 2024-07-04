#pragma once

#include <iostream>
#include <vector>

#include "../types.hpp"
#include "atcoder/lazysegtree.hpp"

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

namespace RMinQ_RAQ {
using S = i64;
using F = i64;
S op(S a, S b) { return std::min(a, b); }
S e() { return i64MAX; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }
} // namespace RMinQ_RAQ

namespace RMaxQ_RAQ {
using S = i64;
using F = i64;
S op(S a, S b) { return std::max(a, b); }
S e() { return i64MIN; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }
} // namespace RMaxQ_RAQ

namespace RSQ_RAQ {
struct S {
    i64 value;
    i32 size;
};
using F = i64;
S op(S a, S b) { return {a.value + b.value, a.size + b.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {x.value + f * x.size, x.size}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }
} // namespace RSQ_RAQ

namespace RMinQ_RUQ {
using S = i64;
using F = i64;
S op(S a, S b) { return std::min(a, b); }
S e() { return i64MAX; }
S mapping(F f, S x) { return (f == i64MAX ? x : f); }
F composition(F f, F g) { return (f == i64MAX ? g : f); }
F id() { return i64MAX; }
} // namespace RMinQ_RUQ

namespace RMaxQ_RUQ {
using S = i64;
using F = i64;
S op(S a, S b) { return std::max(a, b); }
S e() { return i64MIN; }
S mapping(F f, S x) { return (f == i64MAX ? x : f); }
F composition(F f, F g) { return (f == i64MAX ? g : f); }
F id() { return i64MAX; }
} // namespace RMaxQ_RUQ

namespace RSQ_RUQ {
struct S {
    i64 value;
    i32 size;
};
using F = i64;
S op(S a, S b) { return {a.value + b.value, a.size + b.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return (f == i64MAX ? x : S{f * x.size, x.size}); }
F composition(F f, F g) { return (f == i64MAX ? g : f); }
F id() { return i64MAX; }
} // namespace RSQ_RUQ

} // namespace gandalfr
