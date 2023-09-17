#pragma once
#include "graph.hpp"

/*
 * verify : https://atcoder.jp/contests/abc235/submissions/39688316
 */
template <typename Weight> class doubling {
  private:
    int N;
    Weight MIN = std::numeric_limits<Weight>::min();
    std::vector<int> depth;
    std::vector<short> log_table;
    std::vector<std::vector<int>> par;
    std::vector<std::vector<Weight>> max_cost;

    void dfs(const graph<Weight, false> &G, int cu, int pa) {
        par[cu][0] = pa;
        for (auto &e : G[cu]) {
            if (e.to == pa)
                continue;
            max_cost[e.to] = {e.cost};
            depth[e.to] = depth[cu] + 1;
            dfs(G, e.to, cu);
        }
    }

  public:
    doubling(const graph<Weight, false> &G)
        : N(G.count_nodes()), depth(G.count_nodes(), 0),
          par(G.count_nodes(), std::vector<int>(1)), max_cost(G.count_nodes()) {
        max_cost[0] = {MIN};
        dfs(G, 0, -1);

        log_table.resize(N + 1);
        log_table[0] = 1;
        for (int i = 1; i <= N; i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }
        for (int i = 0; i < N; i++) {
            par[i].reserve(log_table[depth[i]]);
            max_cost[i].reserve(log_table[depth[i]]);
        }

        // すべてのノードについて親を -1 まで調べたら終了
        for (int i = 1, end_lines = 0; end_lines < N; i++) {
            for (int j = 0; j < N; j++) {
                if (par[j].back() == -1) {
                    end_lines++;
                    continue;
                }

                if (par[par[j][i - 1]].size() < i ||
                    par[par[j][i - 1]][i - 1] == -1) {
                    par[j].push_back(-1);
                    max_cost[j].push_back(MIN);
                } else {
                    par[j].push_back(par[par[j][i - 1]][i - 1]);
                    max_cost[j].push_back(std::max(
                        max_cost[j][i - 1], max_cost[par[j][i - 1]][i - 1]));
                }
            }
        }
    }

    Weight get_max_cost(int a, int b) {
        Weight ret = MIN;
        if (depth[a] < depth[b])
            std::swap(a, b);
        for (int i = 0, d = depth[a] - depth[b]; d > 0; d >>= 1, i++) {
            if (d & 1) {
                ret = std::max(ret, max_cost[a][i]);
                a = par[a][i];
            }
        }
        if (a == b)
            return ret;

        for (int i = std::min(par[a].size(), par[b].size()) - 2; i >= 0;
             i = std::min(i - 1,
                          (int)std::min(par[a].size(), par[b].size()) - 2)) {
            if (par[a][i] != par[b][i]) {
                ret = std::max(ret, std::max(max_cost[a][i], max_cost[b][i]));
                a = par[a][i];
                b = par[b][i];
            }
        }
        ret = std::max(ret, std::max(max_cost[a][0], max_cost[b][0]));
        return ret;
    }

    int get_ancestor(int a, int b) {
        if (depth[a] < depth[b])
            std::swap(a, b);
        for (int i = 0, d = depth[a] - depth[b]; d > 0; d >>= 1, i++) {
            if (d & 1)
                a = par[a][i];
        }
        if (a == b)
            return a;

        for (int i = std::min(par[a].size(), par[b].size()) - 2; i >= 0;
             i = std::min(i - 1,
                          (int)std::min(par[a].size(), par[b].size()) - 2)) {
            if (par[a][i] != par[b][i]) {
                a = par[a][i];
                b = par[b][i];
            }
        }
        return par[a][0];
    }
};
