#ifndef KRUSCAL
#define KRUSCAL
#include "gandalfr/graph/graph.hpp"

/* 単純無向グラフの最小全域木を求める
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7446048
 */
template<typename WEIGHT>
weighted_graph<WEIGHT, false> Kruscal(const weighted_graph<WEIGHT, false> &graph){
    weighted_graph<WEIGHT, false> ret(graph.nodes());
    std::vector<weighted_edge<WEIGHT>> E(graph.edge_set());
    std::sort(E.begin(), E.end());
    for(const weighted_edge<WEIGHT> &e : E) if(!ret.is_connected(e.from, e.to)){ 
        ret.add_edge(e);
    }
    return ret;
}

#endif