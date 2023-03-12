#ifndef TOPOLOGICAL_SORT
#define TOPOLOGICAL_SORT
#include <queue>
#include "gandalfr/graph/graph.hpp"

namespace internal{
    template<typename GRAPH_TYPE>
    std::vector<int> count_indegree(const GRAPH_TYPE &graph){
        int N = graph.nodes();
        std::vector<int> cnt(N, 0);
        for(int i = 0; i < N; i++) for(auto &e : graph[i]) cnt[e.to]++;
        return cnt;
    }
}

/* 単純連結有向グラフをトポロジカルソート
 * O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093511
 */
template<typename GRAPH_TYPE>
std::vector<int> topological_sort(const GRAPH_TYPE &graph){
    std::vector<int> indeg(internal::count_indegree(graph)), ret;
    std::queue<int> q;
    for(int i=0; i<graph.nodes(); i++) if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(auto &e : graph[cu]){
            if(!indeg[e.to]) continue;
            if(!--indeg[e.to]) q.push(e.to);
        }
        ret.emplace_back(cu);
    }
    return ret;
}

#endif