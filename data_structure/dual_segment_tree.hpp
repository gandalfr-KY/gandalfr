#pragma once
#include <assert.h>

#include <functional>
#include <iostream>
#include <optional>
#include <vector>

#include "operations.hpp"

/**
 * @attention 多分非可換でのみ動作
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627486#1
 */
template <typename MonoidAction> class dual_segment_tree {
  private:
    int n, vec_size;
    using T = typename MonoidAction::VType;
    using S = typename MonoidAction::AType;
    std::vector<T> vals;
    std::vector<S> lazy;

  public:
    dual_segment_tree(int siz) : dual_segment_tree(std::vector<T>(siz)) {}
    dual_segment_tree(const std::vector<T> &vec)
        : vec_size(vec.size()), vals(vec) {
        n = 1;
        while (n < vec_size)
            n *= 2;
        lazy.resize(2 * n - 1, MonoidAction::id());
    }

    // pos 番目の値を得る
    T operator[](int pos) const {
        T ret = vals[pos];
        pos += n - 1;
        while (ret = MonoidAction::f(ret, lazy[pos]), pos > 0) {
            pos = (pos - 1) / 2;
        }
        return ret;
    }

    // [l, r) に MonoidAction::f を作用する
    void operator()(int l, int r, S action) {
        assert(0 <= l && l <= r && r <= vec_size);
        if (l == r)
            return;
        act(l, r, 0, 0, n, action);
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const dual_segment_tree &seg) {
        for (int i = 0; i < seg.vec_size; i++) {
            os << seg[i] << (i == seg.vec_size - 1 ? "" : " ");
        }
        return os;
    }

  private:
    void act(int a, int b, int k, int l, int r, S action) {
        if (r <= a || b <= l)
            return;
        if (a <= l && r <= b) {
            lazy[k] = MonoidAction::op(lazy[k], action);
            return;
        }
        act(a, b, 2 * k + 1, l, (l + r) / 2, action);
        act(a, b, 2 * k + 2, (l + r) / 2, r, action);
    }
};
