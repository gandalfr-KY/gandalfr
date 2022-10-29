#ifndef COUNT_INDEGREE
#define COUNT_INDEGREE
#include "gandalfr/graph/graph.hpp"

template<typename GRAPH>
std::vector<int> count_indegree(GRAPH &graph){
    std::vector<int> cnt(graph.N, 0);
    for(auto &E : graph.G) for(auto &e : E) cnt[e.to]++;
    return cnt;
}

#endif