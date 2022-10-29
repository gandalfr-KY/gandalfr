#ifndef REVERSED_GRAPH
#define REVERSED_GRAPH
#include "gandalfr/graph/graph.hpp"

unweighted_graph reversed_graph(unweighted_graph &graph){
    assert(graph.is_directed);
    unweighted_graph ret(graph.N, graph.is_directed);
    for(auto &e : graph.E){
        ret.add_edge(e.to, e.from);
    }
    return ret;
}

template<typename WEIGHT>
weighted_graph<WEIGHT> reversed_graph(weighted_graph<WEIGHT> &graph){
    assert(graph.is_directed);
    weighted_graph<WEIGHT> ret(graph.N, graph.is_directed);
    for(auto &e : graph.E){
        ret.add_edge(e.to, e.from, e.cost);
    }
    return ret;
}

#endif