#pragma once

#include "dfs.hpp"

namespace gandalfr {

/**
 * @brief 強連結成分ごとに分解
 * @return {縮約後のグラフ、nd_id}
 */
GRAPH_TEMPLATE
std::tuple<GRAPH_TYPE, std::vector<i32>> GRAPH_TYPE::scc() const {
    std::vector<i32> nd_id(N, -1), ord;
    std::vector<bool> used(N, false);

    for (i32 i = 0; i < N; i++) {
        if (used[i]) {
            continue;
        }
        auto tmp = postorder(i, used);
        ord.insert(ord.end(), tmp.begin(), tmp.end());
    }

    i32 id = 0;
    used.assign(N, false);
    auto R(rev());
    for (auto x : std::vector(ord.rbegin(), ord.rend())) {
        if (used[x]) {
            continue;
        }
        for (auto y : R.preorder(x, used)) {
            nd_id[y] = id;
        }
        ++id;
    }
    Graph S(id, numEdges());
    for (auto &e : E) {
        S.addEdge({nd_id[e->v0], nd_id[e->v1], e->cost, e->id});
    }
    return {S, nd_id};
}

} // namespace gandalfr
