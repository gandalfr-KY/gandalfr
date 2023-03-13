#ifndef IS_DIRECTED_ACYCLIC_GRAPH
#define IS_DIRECTED_ACYCLIC_GRAPH
#include "gandalfr/graph/topological_sort.hpp"

// 単純有向グラフが非巡回であるか
template<typename WEIGHT>
bool is_directed_acyclic_graph(const internal::_base_graph<WEIGHT, true> &G){
    return topological_sort(G).size() == G.nodes();
}

#endif