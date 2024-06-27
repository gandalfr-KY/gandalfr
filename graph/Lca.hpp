#pragma once
#include "../data_structure/SparseTable.hpp"
#include "dfs.hpp"
#include "shortestPath.hpp"
#include <algorithm>

namespace gandalfr {

/**
 * @brief 無向単純木の最小共通祖先を求めるクラス
 */
template <bool is_weighted> class Lca {
  private:
    using EdgeType = Edge<is_weighted>;
    using Cost = typename EdgeType::Cost;
    using Pair = std::pair<i32, i32>;
    using GraphType = Graph<is_weighted, UNDIRECTED>;

    static Pair min(Pair a, Pair b) { return a.first < b.first ? a : b; }
    static constexpr Pair e() { return {0, 0}; }

    std::vector<i32> idx;
    std::vector<Pair> depth;
    SparseTable<Pair, Lca::min, Lca::e> sps;
    std::vector<Cost> dist;

  public:
    Lca() = default;
    Lca(const GraphType &G, i32 root) { init(G, root); }

    void init(const GraphType &G, i32 root) {
        idx.resize(G.numNodes());
        dist = G.distances(root, -1);
        depth.clear();
        auto ord = G.inorder(root);
        for (u32 i = 0; i < ord.size(); ++i) {
            depth.emplace_back(dist[ord[i]], ord[i]);
            idx[ord[i]] = i;
        }
        sps.init(depth);
    }

    i32 getAncestor(i32 a, i32 b) {
        i32 idxl = idx[a], idxr = idx[b];
        if (idxl > idxr)
            std::swap(idxl, idxr);
        return sps.get(idxl, idxr + 1).second;
    }

    Cost distance(i32 u, i32 v) {
        return dist[u] + dist[v] - 2 * dist[getAncestor(u, v)];
    }

    Cost getDepth(i32 x) {
        return dist[x];
    }
};
} // namespace gandalfr
