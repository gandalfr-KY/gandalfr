#ifndef IS_DIRECTED_ACYCLIC_GRAPH
#define IS_DIRECTED_ACYCLIC_GRAPH
#include "gandalfr/graph/topological_sort.hpp"

template<typename GRAPH>
bool is_directed_acyclic_graph(GRAPH &graph){
    assert(graph.is_directed);
    return topological_sort(graph).size() == graph.N;
}

#endif