#pragma once
#include "graph.hpp"

/* 強連結成分分解
 * groups() := 同一連結成分をまとめた二次元配列を返す
 * group_id()[i] := ノード i が groups() のどのインデックスに格納されているか
 * simplified_graph() :=
 * 強連結成分を簡約したグラフを返す。ただし、自己ループ無し、多重辺あり 前処理
 * O(N) verify : https://atcoder.jp/contests/practice2/submissions/36388906
 */
template <typename Weight> class strongly_connected_components {
  private:
    std::vector<int> grp_id;
    std::vector<std::vector<int>> grps;
    graph<Weight, true> S;

    void dfs1(const graph<Weight, true> &G, int cu, std::vector<int> &ord,
              std::vector<bool> &used) {
        if (used[cu])
            return;
        used[cu] = true;
        for (auto &e : G[cu])
            dfs1(G, e->v[1], ord, used);
        ord.push_back(cu);
    }

    void dfs2(const graph<Weight, true> &G, int cu, int id) {
        if (grp_id[cu] != -1)
            return;
        grp_id[cu] = id;
        for (auto &e : G[cu])
            dfs2(G, e->v[1], id);
    }

  public:
    strongly_connected_components(const graph<Weight, true> &G)
        : grp_id(G.count_nodes(), -1) {
        int N = G.count_nodes();
        std::vector<bool> used(N, false);
        std::vector<int> ord;
        graph<Weight, true> R(G.reverse());

        for (int i = 0; i < N; i++) {
            dfs1(G, i, ord, used);
        }

        int id = 0;
        for (int i = N - 1; i >= 0; i--)
            if (grp_id[ord[i]] == -1) {
                dfs2(R, ord[i], id);
                id++;
            }

        grps.resize(id);
        for (int i = 0; i < N; i++)
            grps[grp_id[i]].push_back(i);

        S.expand(grps.size());
        for (auto &e : G.edges()) {
            e->v[0] = grp_id[e->v[0]];
            e->v[1] = grp_id[e->v[1]];
            if (e->v[0] != e->v[1])
                S.add_edge(*e);
        }
    }

    const std::vector<std::vector<int>> &groups() { return grps; }
    const std::vector<int> &group_id() { return grp_id; }
    const graph<Weight, true> &simplified_graph() { return S; };
};
