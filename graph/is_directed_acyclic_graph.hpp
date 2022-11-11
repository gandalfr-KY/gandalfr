#ifndef IS_DIRECTED_ACYCLIC_GRAPH
#define IS_DIRECTED_ACYCLIC_GRAPH
#include "gandalfr/graph/topological_sort.hpp"

// 単純有向グラフが非巡回であるか
template<typename GRAPH>
bool is_directed_acyclic_graph(const GRAPH &graph){
    return topological_sort(graph).size() == graph.N;
}

#endif