#ifndef TOPOLOGICAL_SORT
#define TOPOLOGICAL_SORT
#include <queue>
#include "gandalfr/graph/graph.hpp"

namespace internal{
    template<typename WEIGHT>
    std::vector<int> count_indegree(const internal::_base_graph<WEIGHT, true> &G){
        int N = G.nodes();
        std::vector<int> cnt(N, 0);
        for(int i = 0; i < N; i++) for(auto &e : G[i]) cnt[e.to]++;
        return cnt;
    }
    template<typename WEIGHT>
    std::vector<int> count_indegree(const internal::_base_graph<WEIGHT, false> &G){
        int N = G.nodes();
        std::vector<int> cnt(N, 0);
        for(int i = 0; i < N; i++) cnt[i] = G[i].size();
        return cnt;
    }
}

/* 単純連結有向グラフをトポロジカルソート
 * O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093511
 */
template<typename WEIGHT>
std::vector<int> topological_sort(const internal::_base_graph<WEIGHT, true> &G){
    std::vector<int> indeg(internal::count_indegree(G)), ret;
    std::queue<int> q;
    for(int i=0; i < G.nodes(); i++) if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(const internal::_base_edge<WEIGHT> &e : G[cu]){
            if(!indeg[e.to]) continue;
            if(!--indeg[e.to]) q.push(e.to);
        }
        ret.emplace_back(cu);
    }
    return ret;
}

#endif