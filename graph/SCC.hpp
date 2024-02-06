#pragma once
#include "gandalfr/graph/Graph.hpp"

namespace gandalfr {

/* 強連結成分分解
 * groups() := 同一連結成分をまとめた二次元配列を返す
 * group_id()[i] := ノード i が groups() のどのインデックスに格納されているか
 * simplified_graph() :=
 * 強連結成分を簡約したグラフを返す。ただし、自己ループ無し、多重辺あり 前処理
 * O(N) verify : https://atcoder.jp/contests/practice2/submissions/50042809
 */
template <bool is_weighted> class SCC {
  private:
    using Edge_t = Edge<is_weighted>;
    using Edge_ptr = std::shared_ptr<Edge_t>;
    using Cost = typename Edge_t::Cost;
    using Graph_t = Graph<is_weighted, DIRECTED>;
    std::vector<i32> grp_id;
    std::vector<std::vector<i32>> grps;
    const Graph_t *G = nullptr;
    Graph_t S;

    void dfs1(i32 cu, std::vector<i32> &ord, std::vector<bool> &used) {
        if (used[cu])
            return;
        used[cu] = true;
        for (auto &e : (*G)[cu])
            dfs1(e->v1, ord, used);
        ord.push_back(cu);
    }

    void dfs2(const Graph_t &R, i32 cu, i32 id) {
        if (grp_id[cu] != -1)
            return;
        grp_id[cu] = id;
        for (auto &e : R[cu])
            dfs2(R, e->v1, id);
    }

  public:
    SCC() = default;
    SCC(const Graph_t &graph) { init(graph); }

    void init(const Graph_t &graph) {
        G = &graph;
        i32 N = G->numNodes();
        grp_id.resize(N, -1);
        std::vector<bool> used(N, false);
        std::vector<i32> ord;
        Graph_t R(G->rev());
        for (i32 i = 0; i < N; i++) {
            dfs1(i, ord, used);
        }

        i32 id = 0;
        for (i32 i = N - 1; i >= 0; i--) {
            if (grp_id[ord[i]] == -1) {
                dfs2(R, ord[i], id);
                id++;
            }
        }

        grps.resize(id);
        for (i32 i = 0; i < N; i++) {
            grps[grp_id[i]].push_back(i);
        }

        S.resize(grps.size());
        S.reserve(G->numEdges());
        for (auto &e : G->getAllEdges()) {
            S.addEdge({grp_id[e->v0], grp_id[e->v1], e->cost, e->id});
        }
    }

    const std::vector<std::vector<i32>> &groups() { return grps; }
    const std::vector<i32> &groupId() { return grp_id; }
    const Graph_t &simplifiedGraph() { return S; };
};
} // namespace gandalfr
