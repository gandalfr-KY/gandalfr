#ifndef COUNT_INDEGREE
#define COUNT_INDEGREE
#include "gandalfr/graph/graph.hpp"

template<typename GRAPH_TYPE>
std::vector<int> count_indegree(const GRAPH_TYPE &graph){
    std::vector<int> cnt(graph.nodes(), 0);
    for(auto &e : graph.edge_set()) cnt[e.to]++;
    return cnt;
}

#endif