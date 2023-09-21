#pragma once
#include <assert.h>

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include "operations.hpp"

template <typename T, typename Monoid> class segment_tree {
  private:
    int n, vec_size;
    std::vector<T> v;

    // pos 番目の値を val に更新
    void update(int pos, T val) {
        pos += n - 1;
        v[pos] = val;
        while (pos > 0) {
            pos = (pos - 1) / 2;
            v[pos] = Monoid::op(v[2 * pos + 1], v[2 * pos + 2]);
        }
    }

    class RefWrapper {
        segment_tree &seg;
        int pos;

    public:
        RefWrapper(segment_tree &s, int p): seg(s), pos(p) {}
        RefWrapper operator=(const T& value) {
            seg.update(pos, value);
            return *this;
        }
        operator T() const {
            return seg.v[pos + seg.n - 1];
        }
    };

  public:
    // 要素の配列 vec で初期化
    segment_tree(const std::vector<T> &vec): vec_size(vec.size()) {
        n = 1;
        while (n < vec_size)
            n <<= 1;
        v.resize(2 * n - 1, Monoid::id());

        for (int i = 0; i < vec_size; i++)
            v[i + n - 1] = vec[i];
        for (int i = n - 2; i >= 0; i--)
            v[i] = Monoid::op(v[2 * i + 1], v[2 * i + 2]);
    }

    // 長さ siz の単位元の配列で初期化
    segment_tree(int siz): vec_size(siz) {
        n = 1;
        while (n < vec_size)
            n *= 2;
        v.resize(2 * n - 1, Monoid::id());
    }

    // [l, r) の演算結果を得る
    // l == r のとき、Monoid::id() を返す
    T operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= vec_size);
        T vl = Monoid::id(), vr = Monoid::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                vl = Monoid::op(vl, v[l - 1]), l++;
            if (r & 1)
                r--, vr = Monoid::op(v[r - 1], vr);
        }
        return Monoid::op(vl, vr);
    }

    // pos 番目の値を得る
    const T &operator[](int pos) const {
        assert(0 <= pos && pos < vec_size);
        return v[pos + n - 1];
    }

    // pos 番目の値を更新
    // 代入操作のみ受理
    RefWrapper operator[](int pos) {
        assert(0 <= pos && pos < vec_size);
        return RefWrapper(*this, pos);
    }

    friend std::ostream &operator<<(std::ostream &os, const segment_tree &seg) {
        for (int i = 0; i < seg.vec_size; i++)
            os << seg.v[i + seg.n - 1] << (i + 1 != (int)seg.vec_size ? " " : "");
        return os;
    }
};

template <class T> using RSQ_segtree = segment_tree<T, monoid::Plus<T>>;
template <class T> using RmQ_segtree = segment_tree<T, monoid::Min<T>>;
template <class T> using RMQ_segtree = segment_tree<T, monoid::Max<T>>;
