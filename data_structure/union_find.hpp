#pragma once
#include <assert.h>

#include <algorithm>
#include <vector>

class union_find {
  private:
    int N;
    mutable std::vector<int> par;
    std::vector<int> nxt;
    int group_num; // 集合の数

  public:
    union_find() : N(0), group_num(0) {}
    union_find(int n) : N(n), par(n, -1), nxt(n), group_num(n) {
        std::iota(nxt.begin(), nxt.end(), 0);
    }

    /**
     * @brief 頂点を n 個に増やす
     * @attention 小さくはできない
     */
    void expand(int n) {
        if (n <= N)
            return;
        par.resize(n, -1);
        nxt.resize(n);
        for (int i = N; i < n; ++i)
            nxt[i] = i;
        group_num += n - N;
        N = n;
    }

    int leader(int x) const {
        return (par[x] < 0 ? x : par[x] = leader(par[x]));
    }

    bool same(int x, int y) const { return leader(x) == leader(y); }

    bool merge(int x, int y) {
        if ((x = leader(x)) == (y = leader(y)))
            return false;
        if (-par[x] > -par[y])
            std::swap(x, y);

        par[x] += par[y];
        par[y] = x;
        std::swap(nxt[x], nxt[y]);
        group_num--;
        return true;
    }

    /**
     * @brief x の属するグループのサイズを返す
     */
    int size(int x) const { return -par[leader(x)]; }

    /**
     * @brief すべてのノードの数
     */
    int size() const { return N; }

    std::vector<int> contained_group(int x) const {
        std::vector<int> ret{x};
        for (int cu = nxt[x]; cu != ret[0]; cu = nxt[cu])
            ret.push_back(cu);
        return ret;
    }

    int count_groups() const { return group_num; }

    std::vector<std::vector<int>> all_groups() const {
        std::vector<std::vector<int>> result;
        result.reserve(group_num);
        std::vector<bool> used(N, false);
        for (int i = 0; i < N; ++i) {
            if (!used[i]) {
                result.emplace_back(contained_group(i));
                for (int x : result.back()) {
                    used[x] = true;
                }
            }
        }
        return result;
    }
};
