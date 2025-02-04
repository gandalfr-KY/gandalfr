#pragma once
#include <assert.h>

#include <numeric>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

class UnionFind {
  private:
    i32 N;
    mutable std::vector<i32> par;
    // https://noshi91.hatenablog.com/entry/2019/07/19/180606
    std::vector<i32> nxt;
    i32 group_num;

  public:
    UnionFind() : N(0), group_num(0) {}
    UnionFind(i32 n) : N(n), par(n, -1), nxt(n), group_num(n) {
        std::iota(nxt.begin(), nxt.end(), 0);
    }

    void expand(i32 n) {
        if (n <= N)
            return;
        par.resize(n, -1);
        nxt.resize(n);
        for (i32 i = N; i < n; ++i)
            nxt[i] = i;
        group_num += n - N;
        N = n;
    }

    i32 leader(i32 x) const {
        return (par[x] < 0 ? x : par[x] = leader(par[x]));
    }

    bool isSame(i32 x, i32 y) const { return leader(x) == leader(y); }

    bool unite(i32 x, i32 y) {
        if ((x = leader(x)) == (y = leader(y)))
            return false;
        if (-par[x] < -par[y]) // unite by size
            std::swap(x, y);

        par[x] += par[y];
        par[y] = x;
        std::swap(nxt[x], nxt[y]);
        group_num--;
        return true;
    }

    i32 size() const { return N; }

    // x の属するグループのサイズを返す
    // O(1)
    i32 groupSize(i32 x) const { return -par[leader(x)]; }

    // x が含まれるグループを返す
    // O(n)
    std::vector<i32> getGroup(i32 x) const {
        std::vector<i32> ret{x};
        for (i32 cu = nxt[x]; cu != ret[0]; cu = nxt[cu])
            ret.push_back(cu);
        return ret;
    }

    i32 numGroups() const { return group_num; }

    std::vector<std::vector<i32>> getAllGroups() const {
        std::vector<std::vector<i32>> result;
        result.reserve(group_num);
        std::vector<bool> used(N, false);
        for (i32 i = 0; i < N; ++i) {
            if (!used[i]) {
                result.push_back(getGroup(i));
                for (i32 x : result.back()) {
                    used[x] = true;
                }
            }
        }
        return result;
    }
};
} // namespace gandalfr
