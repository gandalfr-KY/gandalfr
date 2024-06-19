#pragma once

#include "Graph.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
void GRAPH_TYPE::sccForward(i32 cu, std::vector<i32> &ord,
                            std::vector<bool> &used) const {
    if (used[cu])
        return;
    used[cu] = true;
    for (auto &e : G[cu])
        sccForward(e->v1, ord, used);
    ord.push_back(cu);
}

GRAPH_TEMPLATE
void GRAPH_TYPE::sccBackward(const Graph &R, i32 cu, i32 id,
                             std::vector<i32> &nd_id) const {
    if (nd_id[cu] != -1)
        return;
    nd_id[cu] = id;
    for (auto &e : R[cu])
        sccBackward(R, e->v1, id, nd_id);
}

/**
 * @brief 強連結成分ごとに分解
 * @return {縮約後のグラフ、nd_id}
 */
GRAPH_TEMPLATE
std::tuple<GRAPH_TYPE, std::vector<i32>> GRAPH_TYPE::scc() const {
    std::vector<i32> nd_id(N, -1);
    std::vector<bool> used(N, false);
    std::vector<i32> ord;

    for (i32 i = 0; i < N; i++) {
        sccForward(i, ord, used);
    }
    i32 id = 0;
    auto R(rev());
    for (i32 i = N - 1; i >= 0; i--) {
        if (nd_id[ord[i]] == -1) {
            sccBackward(R, ord[i], id, nd_id);
            id++;
        }
    }
    Graph S(id, numEdges());
    for (auto &e : E) {
        S.addEdge({nd_id[e->v0], nd_id[e->v1], e->cost, e->id});
    }
    return {S, nd_id};
}

} // namespace gandalfr
