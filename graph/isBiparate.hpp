#pragma once

#include "dfs.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
bool GRAPH_TYPE::isBipartite() const {
    static_assert(!is_directed);
    std::vector<i32> col(N, -1);
    std::vector<bool> visited(N, false);
    for (i32 i = 0; i < N; ++i) {
        if (col[i] != -1) {
            continue;
        }
        col[i] = 0;
        for (auto x : preorder(i, visited)) {
            for (auto &e : G[x]) {
                i32 dst = e->dst(x);
                if (col[dst] == col[x])
                    return false;
                col[dst] = !col[x];
            }
        }
    }
    return true;
}

} // namespace gandalfr
