#pragma once

#include <algorithm>
#include <type_traits>

#include "atcoder/fenwicktree.hpp"
#include "../types.hpp"

namespace gandalfr {

/**
 * 関数を [t, f] または [f, t] の範囲で二分探索する
 * f: Func は f(x: T) の形で呼び出せ、返り値の型が bool の関数であることを要請する
 */
template <class T, class Func> void bisection(T &t, T &f, const Func &F) {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>,
                  "T must be a signed integral type.");
    static_assert(std::is_invocable_r_v<bool, Func, T>,
                  "Func must be invocable with T and return bool.");
    assert(F(t) && !F(f));
    while (std::abs(t - f) > 1) {
        T mid = (t & f) + ((t ^ f) >> 1); // (t + f) / 2 without overflow
        (F(mid) ? t : f) = mid;
    }
}

/**
 * 引数に与えた関数を [t, f] または [f, t] の範囲で二分探索する
 * f: Func は f(x: double) の形で呼び出せ、返り値の型が bool の関数であることを要請する
 * 終了条件は |t - f| < eps 
 */
template <class Func>
void bisection(double &t, double &f, const Func &F, double eps = 1e-9) {
    static_assert(std::is_invocable_r_v<bool, Func, double>);
    assert(F(t) && !F(f));
    while (std::abs(t - f) > eps) {
        double mid = (t + f) / 2;
        (F(mid) ? t : f) = mid;
    }
}

/**
 * vector を座標圧縮する
 * 最小の要素は 0 になる
 */
template <typename T>
std::vector<i32> compress(const std::vector<T> &vec) {
    std::vector<i32> ret(vec.size());
    std::vector<T> w(vec);
    std::sort(w.begin(), w.end());
    w.erase(std::unique(w.begin(), w.end()), w.end());
    for (size_t i = 0; i < vec.size(); ++i) {
        ret[i] = std::lower_bound(w.begin(), w.end(), vec[i]) - w.begin();
    }
    return ret;
}

/**
 * vector の転倒数を求める
 * 区間長が 0 ならば 0
 */
template <class T>
i64 inversion(const std::vector<T>& v) {
    if (v.empty()) return 0;
    int N = v.size();
    std::vector<i32> cmp(compress(v));
    atcoder::fenwick_tree<i64> bit(
            *std::max_element(cmp.begin(), cmp.end()) + 1);

    i64 ret = (i64)N * (N + 1) / 2;
    for (auto &x : cmp) {
        bit.add(x, 1);
        ret -= bit.sum(0, x + 1);
    }
    return ret;
}

/**
 * 要素の集合が等しい vector を二つ指定。一方をもう一方と同じように並べ替えるための swap のコスト
 * 要素の集合が不一致ならば -1、区間長が 0 ならば 0
 */
template <class T>
i64 inversion(std::vector<T> a, std::vector<T> b) {
    if (a.size() != b.size()) return -1;
    if (a.empty()) return 0;
    i32 N = a.size();

    auto a_srt(a), b_srt(b);
    std::sort(a_srt.begin(), a_srt.end());
    std::sort(b_srt.begin(), b_srt.end());
    if (a_srt != b_srt) return -1;

    a = compress(a);
    b = compress(b);
    std::vector<std::vector<i32>> ord(
        *std::max_element(b.begin(), b.end()) + 1);
    for (int i = 0; i < N; i++)
        ord[b[i]].push_back(i);
    for (int i = N - 1; i >= 0; i--) {
        int tmp = ord[a[i]].back();
        ord[a[i]].pop_back();
        a[i] = tmp;
    }
    return inversion(a);
}

/**
 * 最長部分増加列のの長さを求める
 * strict ? 狭義増加 : 広義増加
 */
template <typename T>
i32 LIS(const std::vector<T>& v, bool strict = false) {
    std::vector<T> dp;
    auto dp_it = dp.begin();
    for (auto x : v) {
        if (strict) {
            dp_it = std::lower_bound(dp.begin(), dp.end(), x);
        } else {
            dp_it = std::upper_bound(dp.begin(), dp.end(), x);
        }
        if (dp_it == dp.end()) {
            dp.push_back(x);
        } else {
            *dp_it = x;
        }
    }
    return dp.size();
}
}
