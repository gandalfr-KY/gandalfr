#pragma once
#include "gandalfr/data_structure/SparseTable.hpp"
#include "gandalfr/graph/Graph.hpp"
#include <algorithm>

namespace gandalfr {

/**
 * @brief 無向単純木の最小共通祖先を求めるクラス
 */
template <bool is_weighted> class LCA {
  private:
    using Edge_t = Edge<is_weighted>;
    using Cost = typename Edge<is_weighted>::Cost;
    using Pair = std::pair<i32, i32>;
    using Graph_t = Graph<is_weighted, UNDIRECTED>;

    static Pair min(Pair a, Pair b) { return a.first < b.first ? a : b; }
    static constexpr Pair e() { return {0, 0}; }

    const Graph_t *G = nullptr;
    std::vector<i32> idx;
    std::vector<Pair> depth;
    SparseTable<Pair, LCA::min, LCA::e> sps;
    std::vector<Cost> dist;

    void EulerTour(i32 cu, i32 pa, i32 dep, i32 &cnt) {
        idx[cu] = cnt;
        for (auto &e : (*G)[cu]) {
            i32 to = e->dst(cu);
            if (to == pa)
                continue;
            depth.emplace_back(Pair{dep, cu});
            EulerTour(to, cu, dep + 1, ++cnt);
        }
        depth.emplace_back(Pair{dep, cu});
        cnt++;
    }

  public:
    LCA() = default;
    LCA(const Graph_t &graph, i32 root) { init(graph, root); }

    void init(const Graph_t &graph, i32 root) {
        G = &graph;
        idx.resize(graph.numNodes());
        dist = graph.distances(root, -1);
        i32 cnt = 0;
        EulerTour(root, -1, 0, cnt);
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
};
} // namespace gandalfr
