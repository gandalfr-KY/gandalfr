#pragma once

#include <iostream>

#include "atcoder/modint.hpp"

namespace gandalfr {

using Mint998 = atcoder::modint998244353;
using Mint107 = atcoder::modint1000000007;
template <i32 m> using Mint = atcoder::static_modint<m>;
template <i32 id> using DMint = atcoder::dynamic_modint<id>;

template <i32 m> std::ostream &operator<<(std::ostream &os, const Mint<m> &mi) {
    os << mi.val();
    return os;
}
template <i32 id>
std::ostream &operator<<(std::ostream &os, const DMint<id> &mi) {
    os << mi.val();
    return os;
}

template <i32 m> std::istream &operator>>(std::istream &is, Mint<m> &mi) {
    long long n;
    is >> n;
    mi = n;
    return is;
}
template <i32 id> std::istream &operator>>(std::istream &is, DMint<id> &mi) {
    long long n;
    is >> mi;
    mi = n;
    return is;
}
} // namespace gandalfr
