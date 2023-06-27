#pragma once
#include <assert.h>

#include <algorithm>
#include <vector>

class union_find {
  private:
    int N;
    std::vector<int> par, group_siz, nxt;
    int group_num; // 集合の数
 
  public:
    union_find() : N(0) {}
    union_find(int n) : N(n), par(n, -1), group_siz(n, 1), group_num(n),nxt(n) {
        std::iota(nxt.begin(), nxt.end(), 0);
    }
 
    /**
     * @brief 頂点を n 個に増やす
     * @attention 小さくはできない
     */
    void expand(int n) {
        if (n <= N)
            return;
        N = n;
        par.resize(n, -1);
        group_siz.resize(n, 1);
        nxt.resize(n);
        for (int i = N; i < n; ++i)
            nxt[i] = i;
        group_num += n - N;
    }
 
    int leader(int x) {
        if (par[x] == -1)
            return x;
        else
            return par[x] = leader(par[x]);
    }
 
    bool same(int x, int y) { return leader(x) == leader(y); }
 
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y)
            return false;
        if (group_siz[x] < group_siz[y])
            std::swap(x, y); // 小さいほうに統合
 
        par[y] = x;
        group_siz[x] += group_siz[y];
        std::swap(nxt[x], nxt[y]);
        group_num--;
        return true;
    }
 
    // x の属するグループのサイズを返す
    int size(int x) { return group_siz[leader(x)]; }
 
    int count_groups() const { return group_num; }
 
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> result;
        result.reserve(group_num);
        std::vector<bool> used(N, false);
        for (int cur = 0; cur < N; ++cur) {
            if (!used[cur]) {
                used[cur] = true;
                result.push_back({cur});
                result.reserve(size(cur));
                while (!used[cur = nxt[cur]]) {
                    used[cur] = true;
                    result.back().push_back(cur);
                }
            }
        }
        return result;
    }
};
