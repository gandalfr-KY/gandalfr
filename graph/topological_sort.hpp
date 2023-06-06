#ifndef TOPOLOGICAL_SORT
#define TOPOLOGICAL_SORT
#include <queue>
#include "graph.hpp"

/* 単純連結有向グラフをトポロジカルソート
 * O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093511
 */
template<typename WEIGHT>
std::vector<int> topological_sort(const graph<WEIGHT, true> &G){
    std::vector<int> indeg(G.count_nodes(), 0), sorted;
    for(auto &e : G.edges()) indeg[e.to]++;

    std::queue<int> q;
    for(int i=0; i < G.count_nodes(); i++) if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(auto &e : G[cu]){
            if(!--indeg[e.to]) q.push(e.to);
        }
        sorted.emplace_back(cu);
    }
    return sorted;
}

#endif