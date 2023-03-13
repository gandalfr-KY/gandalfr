#ifndef REVERSED_GRAPH
#define REVERSED_GRAPH
#include "gandalfr/graph/graph.hpp"

// 有向グラフの辺の向きを逆にしたグラフを作る
template<typename WEIGHT>
internal::_base_graph<WEIGHT, true> reversed_graph(const internal::_base_graph<WEIGHT, true> &G){
    internal::_base_graph<WEIGHT, true> ret(G.nodes());
    for(internal::_base_edge<WEIGHT> e : G.edge_set()) {
        std::swap(e.from, e.to);
        ret.add_edge(e);
    }
    return ret;
}

#endif