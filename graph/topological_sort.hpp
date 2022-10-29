#ifndef TOPOLOGICAL_SORT
#define TOPOLOGICAL_SORT
#include <queue>
#include "gandalfr/graph/count_indegree.hpp"

template<typename GRAPH>
std::vector<int> topological_sort(GRAPH &graph){
    assert(graph.is_directed);
    std::vector<int> indegree = count_indegree(graph), sorted;
    std::queue<int> q;
    for(int i=0; i<graph.N; i++) if(!indegree[i]) q.push(i);
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(auto &e : graph.G[cu]){
            if(!indegree[e.to]) continue;
            if(!--indegree[e.to]) q.push(e.to);
        }
        sorted.emplace_back(cu);
    }
    return sorted;
}

#endif