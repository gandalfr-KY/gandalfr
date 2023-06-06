#ifndef REVERSED_GRAPH
#define REVERSED_GRAPH
#include "gandalfr/graph/graph.hpp"

// 有向グラフの辺の向きを逆にしたグラフを作る
template<typename WEIGHT>
graph<WEIGHT, true> reversed_graph(const graph<WEIGHT, true> &G){
    graph<WEIGHT, true> ret(G.count_nodes());
    for(auto e : G.edges()) {
        std::swap(e.from, e.to);
        ret.add_edge(e);
    }
    return ret;
}

#endif