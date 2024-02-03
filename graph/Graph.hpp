#pragma once
#include <assert.h>
#include <queue>
#include <vector>
#include <utility>

#include "gandalfr/graph/BaseGraph.hpp"
#include "gandalfr/math/Matrix.hpp"

namespace gandalfr {

constexpr bool DIRECTED = true;
constexpr bool UNDIRECTED = false;

/**
 * @brief グラフを管理するクラス。
 * @tparam is_weighted i32 なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <bool is_weighted, bool is_directed>
class Graph : public impl::BaseGraph<is_weighted> {
  private:
    using Edge_t = Edge<is_weighted>;
    using Cost = typename Edge<is_weighted>::Cost;
    using Pair = std::pair<Cost, i32>;
    Cost cost_sum = 0;
    Cost CMAX = std::numeric_limits<Cost>::max(), CMIN = std::numeric_limits<Cost>::lowest();

  public:
    Graph() {}
    Graph(i32 n, i32 m)
        : impl::BaseGraph<is_weighted>(n, m) {}
    Graph(const Graph &other) : impl::BaseGraph<is_weighted>(other.N, other.num_edges()) {
        for (auto &e : other.E) {
            add_edge(e);
        }
    }

    /**
     * @return グラフの重み
     */
    Cost weight() const { return cost_sum; }

    /**
     * @param e 辺
     * @attention 渡した辺の id は保持される
     */
    void addEdge(const Edge_t &e) {
        assert(this->E.size() < this->E.capacity());
        this->E.push_back(e);
        auto shared_ptr_to_edge = std::make_shared<Edge_t>(this->E.back());
        this->G[e.v0].push_back(shared_ptr_to_edge);

        if constexpr (!is_directed) {
            if (e.v0 != e.v1) {
                this->G[e.v1].push_back(shared_ptr_to_edge);
            }
        }
        cost_sum += e.cost;
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が i32 だとエラー
     */
    void addEdge(i32 from, i32 to, Cost cost) {
        static_assert(is_weighted);
        addEdge({from, to, cost, (i32)this->E.size()});
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が i32 以外だとエラー
     */
    void addEdge(i32 from, i32 to) {
        static_assert(!is_weighted);
        addEdge({from, to, (i32)this->E.size()});
    }

    /**
     * @brief グラフを隣接行列に変換
     * @param invalid 辺のないときの値
     * @attention 自己ループが含まれていない限り、対角成分は 0
     * @attention 多重辺を持たないと仮定
     */
    Matrix<Cost> toMatrix(Cost invalid) const {
        Matrix<Cost> ret(this->N, this->N, invalid);
        for (i32 i = 0; i < this->N; i++)
            ret(i, i) = 0;
        for (auto &e : this->E) {
            ret(e.v[0], e.v[1]) = e.cost;
            if constexpr (!is_directed) {
                ret(e.v[1], e.v[0]) = e.cost;
            }
        }
        return ret;
    }

  private:


    std::vector<std::shared_ptr<Edge_t>> run_Dijkstra(std::vector<Cost> &dist, i32 start_node) const {
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
        q.push({0, start_node});
        std::vector<std::shared_ptr<Edge_t>> prev_edge(this->N, nullptr);
        std::vector<bool> visited(this->N, false);
        while (!q.empty()) {
            Cost cur_dist = q.top().first;
            i32 cu = q.top().second;
            q.pop();

            if (visited[cu])
                continue;
            visited[cu] = true;

            for (auto &e : this->G[cu]) {
                i32 to = e->dst(cu);
                Cost alt = cur_dist + e->cost;
                if (dist[to] <= alt)
                    continue;
                prev_edge[to] = e;
                dist[to] = alt;
                q.push({alt, to});
            }
        }
        return prev_edge;
    }

    std::vector<std::shared_ptr<Edge_t>> run_bfs(std::vector<i32> &dist, i32 start_node) const {
        std::queue<i32> q;
        q.push(start_node);
        std::vector<std::shared_ptr<Edge_t>> prev_edge(this->N, nullptr);
        while (!q.empty()) {
            i32 cu = q.front();
            q.pop();
            for (auto &e : this->G[cu]) {
                i32 to = e->dst(cu);
                if (dist[to] != CMAX)
                    continue;
                prev_edge[to] = e;
                dist[to] = dist[cu] + 1;
                q.push(to);
            }
        }
        return prev_edge;
    }

  public:
    /**
     * @brief 最短距離を計算する
     * @param start_node 始点
     * @param invalid 到達不能な頂点に格納される値
     * @return 各ノードまでの最短距離のリスト
     */
    std::vector<Cost> distances(i32 start_node, Cost invalid) const {
        std::vector<Cost> dist(this->N, CMAX);
        dist[start_node] = 0;
        
        if constexpr (is_weighted) {
            run_Dijkstra(dist, start_node);
        } else {            
            run_bfs(dist, start_node);
        }

        for (auto &x : dist)
            if (x == CMAX)
                x = invalid;
        return dist;
    }

    /**
     * @brief 復元付き最短経路
     * @attention 到達可能でないとき、空の配列で返る
     * @attention 負閉路があるとき正しい動作を保証しない
     */
    std::vector<Edge_t> shortestPath(int start_node, int end_node) const {
        std::vector<Cost> dist(this->N, CMAX);
        dist[start_node] = 0;
        std::vector<std::shared_ptr<Edge_t>> prev_edge(this->N, nullptr);

        if constexpr (is_weighted) {
            prev_edge = run_Dijkstra(dist, start_node);
        } else {            
            prev_edge = run_bfs(dist, start_node);
        }

        if (dist[end_node] == CMAX)
            return {};

        int cu = end_node;
        std::vector<Edge_t> route;
        while (cu != start_node) {
            auto e = prev_edge[cu];
            if (cu == e->v0) {
                route.push_back(e->rev());
            } else {
                route.push_back(*e);
            }
            cu = e->dst(cu);
        }
        return {route.rbegin(), route.rend()};
    }

    // O(N^3)
    Matrix<Cost> distancesFromAllNodes(Cost invalid = -1) const {
        auto mt(toMatrix(CMAX));

        for (i32 k = 0; k < this->N; k++)         // 経由する頂点
            for (i32 i = 0; i < this->N; i++)     // 始点
                for (i32 j = 0; j < this->N; j++) // 終点
                    if (mt(i, k) != CMAX && mt(k, j) != CMAX)
                        mt(i, j) = std::min(mt(i, j), mt(i, k) + mt(k, j));

        for (i32 i = 0; i < this->N; ++i)
            for (i32 j = 0; j < this->N; ++j)
                if (mt(i, j) == CMAX)
                    mt(i, j) = invalid;
        return mt;
    }

    Graph reverse() const {
        if constexpr (!is_directed) {
            return *this;
        } else {
            Graph ret(this->N);
            for (auto &e : this->E) {
                ret.add_edge(e.reverse());
            }
            return ret;
        }
    }

//     /**
//      * @brief 行きがけ順に dfs
//      */
//     std::vector<i32> preorder(i32 start) const {
//         std::vector<i32> result;
//         reset_visited_flag(start);
//         visited[start] = true;
//         auto dfs = [&](auto self, i32 cu) -> void {
//             result.push_back(cu);
//             for (auto &e : this->G[cu]) {
//                 i32 to = e->dst(cu);
//                 if (visited[to])
//                     continue;
//                 visited[to] = true;
//                 self(self, to);
//             }
//         };
//         dfs(dfs, start);
//         return result;
//     }

//     /**
//      * @brief 通りがけ順に dfs
//      */
//     std::vector<i32> inorder(i32 start) const {
//         std::vector<i32> result;
//         reset_visited_flag(start);
//         visited[start] = true;
//         auto dfs = [&](auto self, i32 cu) -> void {
//             for (auto &e : this->G[cu]) {
//                 i32 to = e->dst(cu);
//                 if (visited[to])
//                     continue;
//                 visited[to] = true;
//                 result.push_back(cu);
//                 self(self, to);
//             }
//             result.push_back(cu);
//         };
//         dfs(dfs, start);
//         return result;
//     }

//     /**
//      * @brief 帰りがけ順に dfs
//      */
//     std::vector<i32> postorder(i32 start) const {
//         std::vector<i32> result;
//         reset_visited_flag(start);
//         visited[start] = true;
//         auto dfs = [&](auto self, i32 cu) -> void {
//             for (auto &e : this->G[cu]) {
//                 i32 to = e->dst(cu);
//                 if (visited[to])
//                     continue;
//                 visited[to] = true;
//                 self(self, to);
//             }
//             result.push_back(cu);
//         };
//         dfs(dfs, start);
//         return result;
//     }

//     /**
//      * @return 最小全域森
//      */
//     Graph minimum_spanning_forest() const {
//         static_assert(!is_directed);
//         Graph ret(this->N, this->N - 1);
//         std::vector<i32> idx(this->E.size());
//         std::iota(idx.begin(), idx.end(), 0);

//         std::sort(idx.begin(), idx.end(), [&](i32 i, i32 j) {
//             auto a = &this->E[i], b = &this->E[j];
//             if (a->cost == b->cost) {
//                 if (a->v[0] == b->v[0]) {
//                     return a->v[1] < b->v[1];
//                 }
//                 return a->v[0] < b->v[0];
//             }
//             return a->cost < b->cost;
//         });

//         for (i32 i : idx) {
//             if (!ret.are_connected(this->E[i].v[0], this->E[i].v[1]))
//                 ret.add_edge(this->E[i]);
//         }
//         return ret;
//     }

//     bool is_bibartite() {
//         std::vector<i32> col(this->N, -1);
//         auto bfs = [&](i32 start) -> bool {
//             std::queue<i32> q;
//             q.push(start);
//             col[start] = 0;
//             while (!q.empty()) {
//                 i32 cur = q.front();
//                 q.pop();
//                 for (auto &e : this->G[cur]) {
//                     i32 to = e->dst(cur);
//                     if (col[to] == -1) {
//                         col[to] = (col[cur] == 0);
//                         q.push(to);
//                     } else if (col[cur] == col[to]) {
//                         return false;
//                     }
//                 }
//             }
//             return true;
//         };
//         for (i32 i = 0; i < this->N; ++i) {
//             if (col[i] == -1 && !bfs(i)) {
//                 return false;
//             }
//         }
//         return true;
//     }
};
}
