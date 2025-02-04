#pragma once

#include <numeric>

#include "../types.hpp"
#include "PersistentArray.hpp"

namespace gandalfr {

struct PersistentUnionFind {
    i32 N;
    mutable PersistentArray<i32> par;
    // https://noshi91.hatenablog.com/entry/2019/07/19/180606
    PersistentArray<i32> nxt;
    std::vector<i32> group_num;

    PersistentUnionFind() : N(0) {}
    PersistentUnionFind(i32 n) : N(n), par(std::vector<i32>(n, -1)), group_num(1, n) {
        std::vector<i32> v(n);
        std::iota(v.begin(), v.end(), 0);
        nxt = PersistentArray<i32>(v);
    }

    i32 version() const { return par.version(); }

    i32 leader(i32 t, i32 x) const {
        i32 tmp;
        while ((tmp = par.get(t, x)) >= 0) {
            x = tmp;
        } 
        return x;
    }

    bool isSame(i32 t, i32 x, i32 y) const { return leader(t, x) == leader(t, y); }

    bool unite(i32 t, i32 x, i32 y) {
        if ((x = leader(t, x)) == (y = leader(t, y))) {
            par.update_batch(t, {}, {});
            nxt.update_batch(t, {}, {});
            return false;
        }
        i32 px = par.get(t, x), py = par.get(t, y);
        if (-px < -py) {
            // unite by size
            std::swap(x, y);
            std::swap(px, py);
        }
        par.update_batch(t, {x, y}, {px + py, x}); // y の親を x にする
        nxt.update_batch(t, {x, y}, {nxt.get(t, y), nxt.get(t, x)});
        
        group_num.push_back(group_num.back() - 1);
        return true;
    }

    i32 size() const { return N; }

    // x の属するグループのサイズを返す
    // O(1)
    i32 groupSize(i32 t, i32 x) const { return -par.get(t, leader(t, x)); }

    // x が含まれるグループを返す
    // O(n)
    std::vector<i32> getGroup(i32 t, i32 x) const {
        std::vector<i32> ret{x};
        for (i32 cu = nxt.get(t, x); cu != ret[0]; cu = nxt.get(t, cu))
            ret.push_back(cu);
        return ret;
    }

    i32 numGroups(i32 t) const { return group_num[t]; }

    std::vector<std::vector<i32>> getAllGroups(i32 t) const {
        std::vector<std::vector<i32>> result;
        result.reserve(group_num[t]);
        std::vector<bool> used(N, false);
        for (i32 i = 0; i < N; ++i) {
            if (!used[i]) {
                result.push_back(getGroup(t, i));
                for (i32 x : result.back()) {
                    used[x] = true;
                }
            }
        }
        return result;
    }
};

} // namespace gandalfr
