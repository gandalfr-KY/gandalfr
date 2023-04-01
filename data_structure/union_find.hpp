#ifndef UNION_FIND
#define UNION_FIND
#include <vector>
#include <algorithm>
#include <assert.h>

class union_find{
  private:
    int N;
    std::vector<int> par, group_siz;
    int group_num; // 集合の数

  public:
    union_find() : N(0) {}
    union_find(int n) : N(n), par(n, -1), group_siz(n, 1), group_num(n) {}

    void expand(int n){
        if(n <= N) return;
        N = n;
        par.resize(n, -1);
        group_siz.resize(n, 1);
        group_num += n - N;
    }

    int leader(int x){
        if(par[x] == -1) return x;
        else return par[x] = leader(par[x]);
    }
 
    bool same(int x, int y){
        return leader(x) == leader(y);
    }
 
    bool merge(int x, int y){
        x = leader(x); y = leader(y);
        if(x == y) return false;
        // 小さいほうに統合
        if(group_siz[x] < group_siz[y]) std::swap(x, y);
        par[y] = x;
        group_siz[x] += group_siz[y];
        group_num--;
        return true;
    }

    // x の属するグループのサイズを返す
    int size(int x){
        return group_siz[leader(x)];
    }

    int count_groups() const {
        return group_num;
    }

    std::vector<std::vector<int>> groups(){
        std::vector<std::vector<int>> result(N);
        for(int i = 0; i < N; i++) result[i].reserve(group_siz[i]);
        for(int i = 0; i < N; i++) result[leader(i)].push_back(i);
        result.erase(
            std::remove_if(result.begin(), result.end(),
            [&](const std::vector<int>& v) { return v.empty(); }), result.end());
        return result;
    }
};

#endif