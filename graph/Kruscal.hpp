#ifndef KRUSCAL
#define KRUSCAL
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/data_structure/union_find.hpp"

/* 単純無向グラフの最小全域木を求める
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7094624
 */
template<typename WEIGHT, bool is_directed>
weighted_graph<WEIGHT, is_directed> Kruscal(const weighted_graph<WEIGHT, is_directed> &graph){
    union_find uf(graph.nodes());
    weighted_graph<WEIGHT, is_directed> ret(graph.nodes());
    std::vector<weighted_edge<WEIGHT>> E(graph.edge_set());
    std::sort(E.begin(), E.end());
    for(weighted_edge<WEIGHT> &e : E){
        if(uf.merge(e.from, e.to)){ 
            ret.add_edge(e.from, e.to, e.cost);
        }
    }
    return ret;
}

#endif