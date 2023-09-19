#pragma once

#include "base_graph.hpp"

template <typename Weight, typename Flow>
class flow_graph : public internal::_base_graph<flow_edge<Weight, Flow>> {
  public:
    using internal::_base_graph<flow_edge<Weight, Flow>>::_base_graph;
    flow_graph(const flow_graph &other) : flow_graph(other.N) {
        for (auto &e : other.E) {
            add_edge(*e);
        }
    }

    /**
     * @brief ノードの数をn個まで増やす
     * @param n サイズ
     * @attention 今のノード数より小さい数を渡したとき、変化なし
     */
    void expand(int n) {
        if (n <= this->N)
            return;
        this->N = n;
        this->G.resize(n);
    }

    /**
     * @attention 辺の id は保持される
     */
    void add_edge(const flow_edge<Weight, Flow> &e) {
        this->E.emplace_back(std::make_unique<flow_edge<Weight, Flow>>(e));
        this->G[e.v[0]].push_back(this->E.back().get());
        this->G[e.v[1]].push_back(this->E.back().get());
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void add_edge(int from, int to, Flow capacity) {
        int id = (int)this->E.size();
        flow_edge<Weight, Flow> e(from, to, capacity, capacity, id);
        this->E.emplace_back(std::make_unique<flow_edge<Weight, Flow>>(e));
        this->G[from].push_back(this->E.back().get());
        this->G[to].push_back(this->E.back().get());
    }

    Flow Ford_Fulkerson(int s, int t) {
        static_assert(std::is_integral<Flow>::value,
                      "Flow must be an integer type");
        Flow flow = 0;
        while (true) {
            std::vector<bool> vis(this->N, false);
            auto dfs = [&](auto self, int cur, Flow f) -> Flow {
                if (cur == t)
                    return f;
                vis[cur] = true;
                for (auto &e : this->G[cur]) {
                    if (vis[e->opp(cur)] || e->is_full(cur))
                        continue;
                    Flow tmp = self(self, e->opp(cur),
                                    std::min<Flow>(e->residual(cur), f));
                    if (tmp > static_cast<Flow>(0)) {
                        e->add_flow(cur, tmp);
                        return tmp;
                    }
                }
                return static_cast<Flow>(0);
            };
            Flow inc = dfs(dfs, s, std::numeric_limits<Flow>::max());
            if (inc == 0)
                break;
            flow += inc;
        }
        return flow;
    }

    Flow Dinic(int s, int t) {
        const int invalid = std::numeric_limits<int>::max();
        Flow flow = 0;
        while (true) {
            std::vector<int> dist(this->N, invalid);
            dist[s] = 0;
            std::queue<int> q;
            q.push(s);
            while(!q.empty()) {
                int cur = q.front();
                q.pop();
                for (auto &e: this->G[cur]) {
                    int to = e->opp(cur);
                    if (dist[to] != invalid || e->is_full(cur))
                        continue;
                    dist[to] = dist[cur] + 1;
                    q.push(to);
                }
            }
            if (dist[t] == invalid) break;

            while (true) {
                auto dfs = [&](auto self, int cur, Flow f) -> Flow {
                    if (cur == s)
                        return f;
                    for (auto &e : this->G[cur]) {
                        int to = e->opp(cur);
                        if (dist[to] != dist[cur] - 1)
                            continue;
                        Flow tmp = self(self, to,
                                        std::min<Flow>(e->residual(to), f));
                        if (tmp > static_cast<Flow>(0)) {
                            e->add_flow(to, tmp);
                            return tmp;
                        }
                    }
                    return static_cast<Flow>(0);
                };
                Flow inc = dfs(dfs, t, std::numeric_limits<Flow>::max());
                if (inc == 0)
                    break;
                flow += inc;
            }
        }
        return flow;
    }

};
