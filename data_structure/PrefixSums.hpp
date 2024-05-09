#pragma once
#include <cassert>
#include <vector>

#include "gandalfr/types.hpp"

namespace gandalfr {

// op  := 二項演算
// inv := ある要素に対する逆元
// id  := 単位元
template <class S, S (*op)(S, S), S (*e)(), S (*inv)(S)> class PrefixSums {
  private:
    i32 n = 0;
    std::vector<S> acm;

  public:
    PrefixSums() = default;
    PrefixSums(const std::vector<S> &v) : n(v.size()) { init(v); }

    void init(const std::vector<S> &v) {
        n = v.size();
        acm.clear();
        acm.reserve(n + 1);
        acm.push_back(e());
        for (const S &x : v) {
            acm.push_back(op(acm.back(), x));
        }
    }

    S get(i32 l, i32 r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return e();
        return op(acm[r], inv(acm[l]));
    }

    const std::vector<S> &getAccumulatedData() const { return acm; }
};

// op  := 二項演算
// inv := ある要素に対する逆元
// id  := 単位元
// verify: https://atcoder.jp/contests/abc203/submissions/45759205
template <class S, S (*op)(S, S), S (*e)(), S (*inv)(S)> class PrefixSums2d {
  private:
    i32 h = 0, w = 0;
    std::vector<std::vector<S>> acm;

  public:
    PrefixSums2d() = default;
    PrefixSums2d(const std::vector<std::vector<S>> &v)
        : h(v.size()), w(v[0].size()), acm(h + 1, std::vector<S>(w + 1, e())) {
        for (i32 i = 1; i <= h; i++) {
            for (i32 j = 1; j <= w; j++) {
                acm[i][j] = op(acm[i][j - 1], v[i - 1][j - 1]);
            }
            for (i32 j = 1; j <= w; j++) {
                acm[i][j] = op(acm[i][j], acm[i - 1][j]);
            }
        }
    }

    void init(const std::vector<std::vector<S>> &v) {
        h = v.size();
        w = v[0].size();
        acm = std::vector<std::vector<S>>(h + 1, std::vector<S>(w + 1, e()));
        for (i32 i = 1; i <= h; i++) {
            for (i32 j = 1; j <= w; j++) {
                acm[i][j] = op(acm[i][j - 1], v[i - 1][j - 1]);
            }
            for (i32 j = 1; j <= w; j++) {
                acm[i][j] = op(acm[i][j], acm[i - 1][j]);
            }
        }
    }

    S get(i32 h_begin, i32 h_end, i32 w_begin, i32 w_end) {
        assert(0 <= h_begin && h_begin <= h_end && h_end <= h);
        assert(0 <= w_begin && w_begin <= w_end && w_end <= w);
        if (h_begin == h_end || w_begin == w_end)
            return e();
        return op(op(op(acm[h_end][w_end], inv(acm[h_end][w_begin])),
                     inv(acm[h_begin][w_end])),
                  acm[h_begin][w_begin]);
    }

    const std::vector<std::vector<S>> &getAccumulatedData() const {
        return acm;
    }
};
} // namespace gandalfr
