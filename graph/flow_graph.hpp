#pragma once

#include "BaseGraph.hpp"

template <typename Cost, typename Flow>
class flow_graph : public internal::_base_graph<flow_edge<Flow, Cost>> {
  public:
    using internal::_base_graph<flow_edge<Flow, Cost>>::_base_graph;
    flow_graph(const flow_graph &other) : flow_graph(other.N) {
        for (auto &e : other.E) {
            add_edge(e);
        }
    }

    /**
     * @attention 辺の id は保持される
     */
    void add_edge(const flow_edge<Flow, Cost> &e) {
        assert(this->E.size() < this->E.capacity());
        this->E.push_back(e);
        flow_edge<Flow, Cost> &new_edge = this->E.back();
        this->G[e.v[0]].push_back(&new_edge);
        this->G[e.v[1]].push_back(&new_edge);
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void add_edge(int from, int to, Flow capacity) {
        add_edge(flow_edge<Flow, Cost>(from, to, capacity, capacity,
                                       (int)this->E.size()));
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void add_edge(int from, int to, Flow capacity, Cost cost) {
        add_edge(flow_edge<Flow, Cost>(from, to, capacity, capacity, cost,
                                       (int)this->E.size()));
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
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (auto &e : this->G[cur]) {
                    int to = e->opp(cur);
                    if (dist[to] != invalid || e->is_full(cur))
                        continue;
                    dist[to] = dist[cur] + 1;
                    q.push(to);
                }
            }
            if (dist[t] == invalid)
                break;

            while (true) {
                auto dfs = [&](auto self, int cur, Flow f) -> Flow {
                    if (cur == s)
                        return f;
                    for (auto &e : this->G[cur]) {
                        int to = e->opp(cur);
                        if (dist[to] != dist[cur] - 1 || e->is_full(to))
                            continue;
                        Flow tmp =
                            self(self, to, std::min<Flow>(e->residual(to), f));
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

    /**
     * @brief 最小費用流 O(FEV)
     */
    Cost primal_dual(int s, int t, Flow F) {
        const Cost invalid = std::numeric_limits<Cost>::max();
        Cost cst = 0;
        while (F) {
            // コストを重みとした残余グラフ上で最短路を計算
            std::vector<int> prev_path(this->N, -1);
            std::vector<Cost> min_cost(this->N, invalid);
            min_cost[s] = 0;
            for (int i = 0; i < this->N; ++i) {
                bool changed = false;
                for (int j = 0; j < (int)this->E.size(); ++j) {
                    auto e = &(this->E[j]);
                    int src = (*e)->v[0], dst = (*e)->v[1];
                    for (int k = 0; k < 2; ++k) {
                        if (min_cost[src] != invalid && !(*e)->is_full(src)) {
                            Cost alt = min_cost[src] + (*e)->get_cost(src);
                            if (min_cost[dst] > alt) {
                                min_cost[dst] = alt;
                                prev_path[dst] = j;
                                changed = true;
                            }
                        }
                        std::swap(src, dst);
                    }
                }
                if (!changed)
                    break;
            }
            if (min_cost[t] == invalid)
                return -1;

            // 流量を計算
            Flow f = F;
            Cost sum = 0;
            int cur = t;
            while (cur != s) {
                auto e = &(this->E[prev_path[cur]]);
                int src = (*e)->v[(*e)->v[0] == cur];
                f = std::min(f, (*e)->residual(src));
                cur = src;
            }

            // グラフとコストの更新
            cur = t;
            while (cur != s) {
                auto e = &(this->E[prev_path[cur]]);
                int src = (*e)->v[(*e)->v[0] == cur];
                (*e)->add_flow(src, f);
                sum += (*e)->get_cost(src);
                cur = src;
            }
            F -= f;
            cst += f * sum;
        }

        return cst;
    }
};
