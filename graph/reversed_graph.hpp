#ifndef REVERSED_GRAPH
#define REVERSED_GRAPH
#include "gandalfr/graph/graph.hpp"

// 有向グラフの辺の向きを逆にしたグラフを作る
template<bool is_directed>
unweighted_graph<is_directed> reversed_graph(const unweighted_graph<is_directed> &graph){
    unweighted_graph<is_directed> ret(graph.nodes());
    for(const unweighted_edge &e : graph.edge_set()) ret.add_edge(e.to, e.from);
    return ret;
}

template<typename WEIGHT, bool is_directed>
weighted_graph<WEIGHT, is_directed> reversed_graph(const weighted_graph<WEIGHT, is_directed> &graph){
    weighted_graph<WEIGHT, is_directed> ret(graph.nodes());
    for(const weighted_edge<WEIGHT> &e : graph.edge_set()) ret.add_edge(e.to, e.from, e.cost);
    return ret;
}

#endif