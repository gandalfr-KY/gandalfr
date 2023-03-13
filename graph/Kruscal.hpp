#ifndef KRUSCAL
#define KRUSCAL
#include "gandalfr/graph/graph.hpp"

/* 単純無向グラフの最小全域木を求める
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7446048
 * verify : https://atcoder.jp/contests/abc235/submissions/39688316
 */
template<typename WEIGHT>
internal::_base_graph<WEIGHT, false> Kruscal(const internal::_base_graph<WEIGHT, false> &G){
    internal::_base_graph<WEIGHT, false> ret(G.nodes());
    std::vector<internal::_base_edge<WEIGHT>> E(G.edge_set());
    std::sort(E.begin(), E.end());
    for(internal::_base_edge<WEIGHT> &e : E) if(!ret.is_connected(e.from, e.to)){ 
        ret.add_edge(e);
    }
    return ret;
}

#endif