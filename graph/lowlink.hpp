#pragma once
#include <utility>

#include "graph.hpp"

/**
 * @brief 単純無向グラフの関節点・橋を求める
 * @attention 連結でないときの verify ができてない。多分あってるけど...
 */
template <typename WEIGHT> class lowlink {
  private:
    std::vector<int> ord, low, apts;
    std::vector<edge<WEIGHT>> brids;

    void dfs(const graph<WEIGHT, false> &g, int cu, int pa, int &cnt,
             const std::vector<int> &id, std::vector<bool> &is_apt,
             std::vector<bool> &is_bridge) {
        ord[cu] = low[cu] = cnt++;
        for (auto &e : g[cu]) {
            if (e.to == pa)
                continue;
            if (ord[e.to] == -1) {
                dfs(g, e.to, cu, cnt, id, is_apt, is_bridge);
                if (low[cu] > low[e.to])
                    low[cu] = low[e.to];
                if (ord[cu] < low[e.to])
                    is_bridge[e.id] = true;
                if (pa != -1 && ord[cu] <= low[e.to])
                    is_apt[id[cu]] = true;
            } else if (low[cu] > ord[e.to])
                low[cu] = ord[e.to];
        }
    }

  public:
    lowlink(graph<WEIGHT, false> &G)
        : ord(G.count_nodes(), -1), low(G.count_nodes(), -1) {
        int C = G.count_connected_components(), N = G.count_nodes(),
            M = G.count_edges();
        std::vector<bool> is_apt(N, false), is_bridge(M, false);
        auto [decomposed, gr_id, nd_id] = G.decompose();
        std::vector<std::vector<int>> id(
            N); // i 番目のグラフのノード j の、もとのグラフのノードの番号
        for (int c = 0; c < C; c++)
            id[c].resize(decomposed[c].count_nodes());
        for (int i = 0; i < N; i++)
            id[gr_id[i]][nd_id[i]] = i;

        std::vector<std::pair<int, int>> st(C, {0x7fffffff, -1}); // <次数, id>
        for (int c = 0; c < C; c++) {
            // 次数が最小のノードは必ず関節点でない
            // そこからDFSすれば、根ノードの関節点判定を行わなくてよい
            for (int i = 0; i < decomposed[c].count_nodes(); i++) {
                st[c] = std::min(st[c], {(int)decomposed[c][i].size(), i});
            }
        }

        for (int c = 0; c < C; c++) {
            int cnt = 0;
            dfs(decomposed[c], st[c].second, -1, cnt, id[c], is_apt, is_bridge);
        }
        for (int i = 0; i < N; i++)
            if (is_apt[i])
                apts.push_back(i);
        for (int i = 0; i < M; i++)
            if (is_bridge[i])

                brids.emplace_back(G.edges()[i]);
    }

    // unsorted であることに注意
    const std::vector<int> &articulation_points() { return apts; }
    const std::vector<edge<WEIGHT>> &bridges() { return brids; }
};
