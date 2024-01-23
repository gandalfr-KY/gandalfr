#pragma once

#include <iostream>

#include "atcoder/modint.hpp"

namespace gandalfr {

using Mint998 = atcoder::modint998244353;
using Mint107 = atcoder::modint1000000007;
template <int m> using Mint = atcoder::static_modint<m>;
template <int id> using DMint = atcoder::dynamic_modint<id>;

template <int m> std::ostream &operator<<(std::ostream &os, const Mint<m> &mi) {
    os << mi.val();
    return os;
}
template <int id>
std::ostream &operator<<(std::ostream &os, const DMint<id> &mi) {
    os << mi.val();
    return os;
}

template <int m> std::istream &operator>>(std::istream &is, Mint<m> &mi) {
    long long n;
    is >> n;
    mi = n;
    return is;
}
template <int id> std::istream &operator>>(std::istream &is, DMint<id> &mi) {
    long long n;
    is >> mi;
    mi = n;
    return is;
}
} // namespace gandalfr
