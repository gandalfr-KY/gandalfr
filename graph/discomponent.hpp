#pragma once

#include "../data_structure/UnionFind.hpp"
#include "dfs.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
std::tuple<std::vector<GRAPH_TYPE>, std::vector<i32>, std::vector<i32>>
GRAPH_TYPE::discomponent() const {
    auto uf = buildUnionFind();
    i32 n_grps = uf.numGroups();
    auto grps = uf.getAllGroups();

    std::vector<i32> grp_id(N), nd_id(N);
    for (i32 i = 0; i < n_grps; ++i) {
        for (i32 j = 0; j < (i32)grps[i].size(); ++j) {
            grp_id[grps[i][j]] = i;
            nd_id[grps[i][j]] = j;
        }
    }

    std::vector<Graph> Gs(n_grps);
    for (i32 i = 0; i < n_grps; ++i) {
        Gs[i].resize(grps[i].size());
    }
    for (auto e : E) {
        i32 id = grp_id[e->v0];
        e->v0 = nd_id[e->v0];
        e->v1 = nd_id[e->v1];
        Gs[id].addEdge(*e);
    }
    return {Gs, grp_id, nd_id};
}

} // namespace gandalfr
