#ifndef UNION_FIND
#define UNION_FIND
#include <vector>
#include <algorithm>
#include <assert.h>

struct union_find{
    union_find() : N(0) {}
    union_find(int n) : N(n), par(n, -1), group_siz(n, 1), group_num(n) {}

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
        if(group_siz[x] < group_siz[y]) std::swap(x, y);
        ///// xに統合 /////
        par[y] = x;
        group_siz[x] += group_siz[y];
        group_num--;
        return true;
    }

    int size(int x){
        return group_siz[leader(x)];
    }

    int count_groups(){
        return group_num;
    }

    std::vector<std::vector<int>> groups(){
        std::vector<int> leader_buf(N), group_size(N);
        for(int i=0; i<N; i++){
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(N);
        for(int i=0; i<N; i++){
            result[i].reserve(group_size[i]);
        }
        for(int i=0; i<N; i++){
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int N;
    std::vector<int> par, group_siz;
    int group_num; // 集合の数
};

#endif