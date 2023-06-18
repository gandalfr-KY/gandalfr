#pragma once
#include "graph.hpp"

/**
 * @param G 無向グラフ
 * @return 最小全域森
 */
template <typename WEIGHT>
graph<WEIGHT, false> Kruscal(const graph<WEIGHT, false> &G) {
    graph<WEIGHT, false> ret(G.count_nodes());
    std::vector<edge<WEIGHT>> E(G.edges());
    std::sort(E.begin(), E.end());
    for (auto &e : E)
        if (!ret.are_connected(e.from, e.to)) {
            ret.add_edge(e);
        }
    return ret;
}
