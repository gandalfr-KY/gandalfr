#ifndef REVERSED_GRAPH
#define REVERSED_GRAPH
#include "gandalfr/graph/graph.hpp"

// 有向グラフの辺の向きを逆にしたグラフを作る
unweighted_graph<true> reversed_graph(const unweighted_graph<true> &graph){
    unweighted_graph<true> ret(graph.nodes());
    for(const unweighted_edge &e : graph.edge_set()) ret.add_edge(e.to, e.from);
    return ret;
}

unweighted_graph<false> reversed_graph(const unweighted_graph<false> &graph){
    return graph;
}

template<typename WEIGHT>
weighted_graph<WEIGHT, true> reversed_graph(const weighted_graph<WEIGHT, true> &graph){
    weighted_graph<WEIGHT, true> ret(graph.nodes());
    for(const weighted_edge<WEIGHT> &e : graph.edge_set()) ret.add_edge(e.to, e.from, e.cost);
    return ret;
}

template<typename WEIGHT>
weighted_graph<WEIGHT, false> reversed_graph(const weighted_graph<WEIGHT, false> &graph){
    return graph;
}

#endif