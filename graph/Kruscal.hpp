#ifndef KRUSCAL
#define KRUSCAL
#include "graph.hpp"

/* 単純無向グラフの最小全域木を求める
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7446048
 * verify : https://atcoder.jp/contests/abc235/submissions/39688316
 */
template<typename WEIGHT>
graph<WEIGHT, false> Kruscal(const graph<WEIGHT, false> &G){
    graph<WEIGHT, false> ret(G.count_nodes());
    std::vector<edge<WEIGHT>> E(G.edges());
    std::sort(E.begin(), E.end());
    for(auto &e : E) if(!ret.are_connected(e.from, e.to)){ 
        ret.add_edge(e);
    }
    return ret;
}

#endif