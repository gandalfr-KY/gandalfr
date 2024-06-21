#pragma once

#include "dfs.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
void GRAPH_TYPE::lowlinkImpl(i32 cu, i32 e_id, i32 &id, std::vector<i32> &ord,
                             std::vector<i32> &low,
                             Graph<is_weighted, DIRECTED> &tree) const {
    ord[cu] = low[cu] = id++;
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (e->id == e_id)
            continue;
        if (ord[to] == -1) {
            tree.addEdge({cu, to, e->cost, e->id});
            lowlinkImpl(to, e->id, id, ord, low, tree);
            chmin(low[cu], low[to]);
        } else {
            chmin(low[cu], ord[to]);
        }
    }
}

GRAPH_TEMPLATE
std::tuple<std::vector<i32>, std::vector<i32>, Graph<is_weighted, DIRECTED>>
GRAPH_TYPE::lowlink() const {
    std::vector<i32> ord(N, -1), low(N, i32MAX);
    Graph<is_weighted, DIRECTED> tree(N, N - 1);
    for (i32 i = 0; i < N; ++i) {
        if (ord[i] != -1) {
            continue;
        }
        i32 id = 0;
        lowlinkImpl(i, -1, id, ord, low, tree);
    }
    return {ord, low, tree};
}

GRAPH_TEMPLATE
std::vector<GRAPH_EDGE_TYPE> GRAPH_TYPE::bridges() const {
    auto [ord, low, tree] = lowlink();
    std::vector<EdgeType> res;
    for (auto &e : tree.getAllEdges()) {
        if (ord[e->v0] < low[e->v1]) {
            res.push_back(*e);
        }
    }
    return res;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::articulationPoints() const {
    auto [ord, low, tree] = lowlink();
    std::vector<i32> res;
    std::vector<bool> visited(N, false);
    for (i32 src = 0; src < N; ++src) {
        if (ord[src] == 0) {
            if (tree[src].size() >= 2) {
                res.push_back(src);
            }
        } else {
            for (auto &e : tree[src]) {
                if (ord[src] <= low[e->dst(src)]) {
                    res.push_back(src);
                    break;
                }
            }
        }
    }
    return res;
}

} // namespace gandalfr
