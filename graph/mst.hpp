#pragma once

#include "../data_structure/UnionFind.hpp"
#include "Graph.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
GRAPH_TYPE GRAPH_TYPE::mst() const {
    static_assert(is_weighted && !is_directed);
    Graph ret(N, N - 1);
    std::vector<i32> idx(E.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),
              [&](i32 i, i32 j) { return E[i]->cost < E[j]->cost; });

    UnionFind uf(N);
    for (i32 i : idx) {
        if (!uf.isSame(E[i]->v0, E[i]->v1)) {
            uf.unite(E[i]->v0, E[i]->v1);
            ret.addEdge(*E[i]);
        }
    }
    return ret;
}

} // namespace gandalfr
