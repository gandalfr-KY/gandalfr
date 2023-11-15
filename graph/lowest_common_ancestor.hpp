#pragma once
#include "../data_structure/sparse_table.hpp"
#include "graph.hpp"

/**
 * @brief 無向単純木の最小共通祖先を求めるクラス
 */
template <typename Weight> class lowest_common_ancestor {
  private:
    using PAIR = std::pair<int, int>;

    std::vector<int> idx;
    std::vector<PAIR> depth;
    RmQ_sparse_table<PAIR> sps;
    std::vector<Weight> dist;

    void Euler_tour(const graph<Weight, false> &G, int cu, int pa, int dep,
                    int &cnt) {
        idx[cu] = cnt;
        for (auto &e : G[cu]) {
            int to = e->opp(cu);
            if (to == pa)
                continue;
            depth.push_back({dep, cu});
            Euler_tour(G, to, cu, dep + 1, ++cnt);
        }
        depth.push_back({dep, cu});
        cnt++;
    }

  public:
    lowest_common_ancestor(const graph<Weight, false> &G)
        : idx(G.num_nodes()), dist(G.distances(0, -1)) {
        assert(G.is_tree());
        int cnt = 0;
        Euler_tour(G, 0, -1, 0, cnt);
        sps.init(depth);
    }

    int get_ancestor(int a, int b) {
        int idxl = idx[a], idxr = idx[b];
        if (idxl > idxr)
            std::swap(idxl, idxr);
        return sps.get(idxl, idxr + 1).second;
    }

    Weight distance(int u, int v) {
        return dist[u] + dist[v] - 2 * dist[get_ancestor(u, v)];
    }
};
