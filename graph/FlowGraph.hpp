#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>

#include "../types.hpp"

namespace gandalfr {

struct FlowEdge {
  public:
    using Flow = i64;
    using Cost = i64;

  private:
    Flow res, cap;

  public:
    i32 v0, v1;
    Cost cost;
    i32 id;

    FlowEdge() {}
    FlowEdge(i32 src, i32 dst, Flow res, Flow cap, i32 id)
        : res(res), cap(cap), v0(src), v1(dst), id(id) {}
    FlowEdge(i32 src, i32 dst, Flow res, Flow cap, Cost cost, i32 id)
        : res(res), cap(cap), v0(src), v1(dst), cost(cost), id(id) {}

    // x から見た反対側の端点
    i32 dst(i32 x) const {
        if (x == v0) {
            return v1;
        } else if (x == v1) {
            return v0;
        }
        std::abort();
    }

    // x から見たコスト
    Cost getCost(i32 x) {
        if (x == v0) {
            return this->cost;
        } else if (x == v1) {
            return -this->cost;
        }
        std::abort();
    }

    FlowEdge rev() const {
        return {v1, v0, cap - res, cap, this->cost, this->id};
    }

    // x から見た残余
    Flow residual(i32 x) const {
        if (x == v0) {
            return res;
        } else if (x == v1) {
            return cap - res;
        }
        std::abort();
    }

    // x から見て残余がゼロか？
    bool isFull(i32 x) const {
        if (x == v0) {
            return res == 0;
        } else if (x == v1) {
            return cap - res == 0;
        }
        std::abort();
    }

    // x から流量を d だけ追加
    void addFlow(i32 x, Flow d) {
        if (x == v0) {
            res -= d;
            return;
        } else if (x == v1) {
            res += d;
            return;
        }
        std::abort();
    }

    friend std::ostream &operator<<(std::ostream &os, const FlowEdge &e) {
        os << e.v0 << ' ' << e.v1 << ' ' << e.cap - e.res << '/' << e.cap;
        return os;
    }
};

class FlowGraph {
  private:
    using Edge_ptr = std::shared_ptr<FlowEdge>;
    using Cost = typename FlowEdge::Cost;
    using Flow = typename FlowEdge::Flow;
    i32 N = 0;
    std::vector<std::vector<Edge_ptr>> G;
    std::vector<Edge_ptr> E;

  public:
    /**
     * @return ノードの数
     */
    i32 numNodes() const { return N; }

    /**
     * @return 辺の数
     */
    i32 numEdges() const { return E.size(); }

    /**
     * @param n ノード番号
     * @return ノード n からの隣接頂点のリストの const 参照
     */
    const std::vector<Edge_ptr> &operator[](i32 n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<Edge_ptr> &getAllEdges() const { return E; }
    /**
     * @return idx 番目に張られた辺の const 参照
     */
    const Edge_ptr &getEdge(i32 idx) const { return E[idx]; }

    FlowGraph() {}
    explicit FlowGraph(i32 n) : N(n), G(n) {}
    FlowGraph(i32 n, i32 m) : N(n), G(n) { E.reserve(m); }
    FlowGraph(const FlowGraph &other) : N(other.N), G(other.N) {
         for (i32 i = 0; i < (i32)other.G.size(); ++i) {
            for (const auto &e : other[i]) {
                G[i].push_back(std::make_shared<FlowEdge>(*e));
            }
        }
        for (const auto &e : other.E) {
            E.push_back(std::make_shared<FlowEdge>(*e));
        }
    }

    FlowGraph(FlowGraph &&other) noexcept
        : N(other.N), G(std::move(other.G)), E(std::move(other.E)) {
        other.N = 0;
    }

    FlowGraph &operator=(const FlowGraph &other) {
        if (this != &other) {
            N = other.N;
            G.clear(), E.clear();
            G.resize(other.G.size());
            for (i32 i = 0; i < (i32)other.G.size(); ++i) {
                for (const auto &e : other.G[i]) {
                    G[i].push_back(std::make_shared<FlowEdge>(*e));
                }
            }
            for (const auto &e : other.E) {
                E.push_back(std::make_shared<FlowEdge>(*e));
            }
        }
        return *this;
    }
    FlowGraph &operator=(FlowGraph &&other) noexcept {
        if (this != &other) {
            N = other.N;
            G = std::move(other.G);
            E = std::move(other.E);
            other.N = 0;
        }
        return *this;
    }
    
    void resize(i32 n) {
        assert(n >= N);
        N = n;
        G.resize(n);
    }

    void reserve(i32 m) { E.reserve(m); }

    /**
     * @attention 辺の id は保持される
     */
    void addEdge(const FlowEdge &e) {
        auto shared_ptr_to_edge = std::make_shared<FlowEdge>(e);
        E.push_back(shared_ptr_to_edge);
        G[e.v0].push_back(shared_ptr_to_edge);
        G[e.v1].push_back(shared_ptr_to_edge);
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void addEdge(i32 src, i32 dst, Flow capacity) {
        addEdge(FlowEdge(src, dst, capacity, capacity, (i32)this->E.size()));
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void addEdge(i32 src, i32 dst, Flow capacity, Cost cost) {
        addEdge(
            FlowEdge(src, dst, capacity, capacity, cost, (i32)this->E.size()));
    }

  private:
    Flow fordFulkersonImpl(i32 src, Flow f, std::vector<bool> &vis,
                           const i32 t) {
        if (src == t)
            return f;
        vis[src] = true;
        for (auto &e : this->G[src]) {
            i32 dst = e->dst(src);
            if (vis[dst] || e->isFull(src))
                continue;
            Flow tmp = fordFulkersonImpl(
                dst, std::min<Flow>(e->residual(src), f), vis, t);
            if (tmp > 0) {
                e->addFlow(src, tmp);
                return tmp;
            }
        }
        return 0;
    }

  public:
    Flow fordFulkerson(i32 s, i32 t) {
        Flow flow = 0;
        while (true) {
            std::vector<bool> vis(this->N, false);
            Flow inc =
                fordFulkersonImpl(s, std::numeric_limits<Flow>::max(), vis, t);
            if (inc == 0)
                break;
            flow += inc;
        }
        return flow;
    }

  private:
    Flow dinicImpl(i32 src, Flow f, const std::vector<i32> &dist, const i32 s) {
        if (src == s)
            return f;
        for (auto &e : this->G[src]) {
            i32 dst = e->dst(src);
            if (dist[dst] != dist[src] - 1 || e->isFull(dst))
                continue;
            Flow tmp =
                dinicImpl(dst, std::min<Flow>(e->residual(dst), f), dist, s);
            if (tmp > 0) {
                e->addFlow(dst, tmp);
                return tmp;
            }
        }
        return 0;
    }

  public:
    Flow dinic(i32 s, i32 t) {
        const i32 INVALID = std::numeric_limits<i32>::max();
        Flow flow = 0;
        while (true) {
            std::vector<i32> dist(this->N, INVALID);
            dist[s] = 0;
            std::queue<i32> q;
            q.push(s);
            while (!q.empty()) {
                i32 src = q.front();
                q.pop();
                for (auto &e : this->G[src]) {
                    i32 dst = e->dst(src);
                    if (dist[dst] != INVALID || e->isFull(src))
                        continue;
                    dist[dst] = dist[src] + 1;
                    q.push(dst);
                }
            }
            if (dist[t] == INVALID)
                break;

            while (true) {
                Flow inc =
                    dinicImpl(t, std::numeric_limits<Flow>::max(), dist, s);
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
    Cost primalDual(i32 s, i32 t, Flow F) {
        const Cost INVALID = std::numeric_limits<Cost>::max();
        Cost cst = 0;
        std::vector<i32> prev_path;
        std::vector<Cost> min_cost;
        while (F) {
            // コストを重みとした残余グラフ上で最短路を計算
            prev_path.assign(this->N, -1);
            min_cost.assign(this->N, INVALID);
            min_cost[s] = 0;
            for (i32 i = 0; i < this->N; ++i) {
                bool changed = false;
                for (u32 j = 0; j < this->E.size(); ++j) {
                    auto &e = this->E[j];
                    i32 src = e->v0, dst = e->v1;
                    for (i32 k = 0; k < 2; ++k) {
                        if (min_cost[src] != INVALID && !e->isFull(src)) {
                            Cost alt = min_cost[src] + e->getCost(src);
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
            if (min_cost[t] == INVALID)
                return -1;

            // 流量を計算
            Flow f = F;
            Cost sum = 0;
            i32 cur = t;
            while (cur != s) {
                auto &e = this->E[prev_path[cur]];
                i32 src = e->dst(cur);
                f = std::min(f, e->residual(src));
                cur = src;
            }

            // グラフとコストの更新
            cur = t;
            while (cur != s) {
                auto &e = this->E[prev_path[cur]];
                i32 src = e->dst(cur);
                e->addFlow(src, f);
                sum += e->getCost(src);
                cur = src;
            }
            F -= f;
            cst += f * sum;
        }
        return cst;
    }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for (auto &e : this->E)
            std::cout << *e << std::endl;
    }
};
} // namespace gandalfr
