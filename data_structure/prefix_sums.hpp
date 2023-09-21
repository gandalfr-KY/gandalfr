#pragma once
#include <functional>
#include <vector>

#include "operations.hpp"

// [l, r) で区間和を得る
template <class T, typename Group> class prefix_sums {
  private:
    int n;
    std::vector<T> acm;

  public:
    prefix_sums(const std::vector<T> &v): n(v.size()) {
        acm.reserve(n + 1);
        acm.push_back(Group::id());
        for (const T &x : v) {
            acm.push_back(Group::op(acm.back(), x));
        }
    }

    T get(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return Group::id();
        return Group::op(acm[r], Group::rev(acm[l]));
    }
};

// verify: https://atcoder.jp/contests/abc203/submissions/45759205
template <typename T, typename Group> class prefix_sums_2d {
  public:
    int h, w;
    std::vector<std::vector<T>> acm;

  public:
    prefix_sums_2d(const std::vector<std::vector<T>> &v): h(v.size()), w(v[0].size()), acm(h + 1, std::vector<T>(w + 1, Group::id())) {
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                acm[i][j] = Group::op(acm[i][j - 1], v[i - 1][j - 1]);
            }
            for (int j = 1; j <= w; j++) {
                acm[i][j] = Group::op(acm[i][j], acm[i - 1][j]);
            }
        }
    }

    T get(int h_begin, int h_end, int w_begin, int w_end) {
        assert(0 <= h_begin && h_begin <= h_end && h_end <= h);
        assert(0 <= w_begin && w_begin <= w_end && w_end <= w);
        if (h_begin == h_end || w_begin == w_end)
            return Group::id();
        // acm[h_end][w_end] - acm[h_end][w_begin] - acm[h_begin][w_end] +
        // acm[h_begin][w_begin] みたいな感じ
        return Group::op(Group::op(Group::op(acm[h_end][w_end], Group::rev(acm[h_end][w_begin])),
                       Group::rev(acm[h_begin][w_end])),
                 acm[h_begin][w_begin]);
    }
};

template <typename T> using RSQ_prefix_sums = prefix_sums<T, group::Plus<T>>;
template <typename T> using RSQ_prefix_sums_2d = prefix_sums_2d<T, group::Plus<T>>;
