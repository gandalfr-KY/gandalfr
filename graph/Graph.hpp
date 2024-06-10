#pragma once
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "gandalfr/data_structure/UnionFind.hpp"
#include "gandalfr/math/Matrix.hpp"
#include "gandalfr/types.hpp"

namespace gandalfr {

constexpr bool WEIGHTED = true;
constexpr bool UNWEIGHTED = false;
constexpr bool DIRECTED = true;
constexpr bool UNDIRECTED = false;

template <bool is_weighted> struct Edge { Edge() = delete; };

template <> struct Edge<WEIGHTED> {

    using Cost = i64;

    i32 v0, v1;
    Cost cost;
    i32 id;

    Edge() = default;
    Edge(i32 src, i32 dst, Cost cost, i32 id)
        : v0(src), v1(dst), cost(cost), id(id) {}

    Edge rev() const { return {this->v1, this->v0, this->cost, this->id}; }

    // x から見た反対側の端点
    // 無向グラフのときの dst の取得はこれを使う
    i32 dst(i32 x) const {
        if (x == v0) {
            return v1;
        } else if (x == v1) {
            return v0;
        }
        std::abort();
    }

    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        os << e.v0 << ' ' << e.v1 << ' ' << e.cost;
        return os;
    }
};

template <> struct Edge<UNWEIGHTED> {

    using Cost = i32;

    i32 v0, v1;
    static const Cost cost = 1;
    i32 id;

    Edge() = default;
    Edge(i32 src, i32 dst, i32 id) : v0(src), v1(dst), id(id) {}
    Edge(i32 src, i32 dst, Cost cost, i32 id) : v0(src), v1(dst), id(id) {
        assert(cost == 1);
    }

    Edge rev() const { return {this->v1, this->v0, this->id}; }

    // x から見た反対側の端点
    // 無向グラフのときの dst の取得はこれを使う
    i32 dst(i32 x) const {
        if (x == v0) {
            return v1;
        } else if (x == v1) {
            return v0;
        }
        std::abort();
    }

    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        os << e.v0 << ' ' << e.v1;
        return os;
    }
};

/**
 * @brief グラフを管理するクラス。
 * @tparam is_weighted i32 なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <bool is_weighted, bool is_directed> class Graph {
  public:
    using EdgeType = Edge<is_weighted>;
    using EdgePtr = std::shared_ptr<EdgeType>;
    using Cost = typename EdgeType::Cost;
    using Pair = std::pair<Cost, i32>;

  private:
    i32 N = 0;
    std::vector<std::vector<EdgePtr>> G;
    std::vector<EdgePtr> E;
    Cost cost_sum = 0;
    static constexpr Cost CMAX = std::numeric_limits<Cost>::max(),
                          CMIN = std::numeric_limits<Cost>::lowest();

  public:
    Graph() {}
    explicit Graph(i32 n) : N(n), G(n) {}
    Graph(i32 n, i32 m) : N(n), G(n) { E.reserve(m); }
    Graph(const Graph &other) : Graph(other.N, other.numEdges()) {
        for (auto &e : other.E) {
            addEdge(*e);
        }
    }

    void resize(i32 n) {
        assert(n >= N);
        N = n;
        G.resize(n);
    }

    void reserve(i32 m) { E.reserve(m); }

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
    const std::vector<EdgePtr> &operator[](i32 n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<EdgePtr> &getAllEdges() const { return E; }
    /**
     * @return idx 番目に張られた辺の const 参照
     */
    const EdgePtr &getEdge(i32 idx) const { return E[idx]; }

    void print() const {
        std::cout << N << " " << E.size() << std::endl;
        for (auto &e : E)
            std::cout << *e << std::endl;
    }

    /**
     * @return グラフの重み
     */
    Cost weight() const { return cost_sum; }

    /**
     * @param e 辺
     * @attention 渡した辺の id は保持される
     */
    void addEdge(const EdgeType &e) {
        auto shared_ptr_to_edge = std::make_shared<EdgeType>(e);
        E.push_back(shared_ptr_to_edge);
        G[e.v0].push_back(shared_ptr_to_edge);
        if constexpr (!is_directed) {
            if (e.v0 != e.v1) {
                G[e.v1].push_back(shared_ptr_to_edge);
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
        addEdge({from, to, cost, (i32)E.size()});
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が i32 以外だとエラー
     */
    void addEdge(i32 from, i32 to) {
        static_assert(!is_weighted);
        addEdge({from, to, (i32)E.size()});
    }

    Graph rev() const {
        if constexpr (!is_directed) {
            return *this;
        } else {
            Graph ret(N, E.size());
            for (auto &e : E) {
                ret.addEdge(e->rev());
            }
            return ret;
        }
    }

    /**
     * @brief グラフを隣接行列に変換
     * @param invalid 辺のないときの値
     * @attention 自己ループが含まれていない限り、対角成分は 0
     * @attention 多重辺を持たないと仮定
     */
    Matrix<Cost> toMatrix(Cost invalid) const {
        Matrix<Cost> ret(N, N, invalid);
        for (i32 i = 0; i < N; i++)
            ret[i][i] = 0;
        for (auto &e : E) {
            ret[e->v0][e->v1] = e->cost;
            if constexpr (!is_directed) {
                ret[e->v1][e->v0] = e->cost;
            }
        }
        return ret;
    }

  private:
    std::vector<EdgePtr> dijkstraImpl(std::vector<Cost> &dist,
                                      i32 start_node) const {
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
        q.push({0, start_node});
        std::vector<EdgePtr> prev_edge(N, nullptr);
        std::vector<bool> visited(N, false);
        while (!q.empty()) {
            Cost cur_dist = q.top().first;
            i32 cu = q.top().second;
            q.pop();

            if (visited[cu])
                continue;
            visited[cu] = true;

            for (auto &e : G[cu]) {
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

    std::vector<EdgePtr> bfsImpl(std::vector<i32> &dist, i32 start_node) const {
        std::queue<i32> q;
        q.push(start_node);
        std::vector<EdgePtr> prev_edge(N, nullptr);
        while (!q.empty()) {
            i32 cu = q.front();
            q.pop();
            for (auto &e : G[cu]) {
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
        std::vector<Cost> dist(N, CMAX);
        dist[start_node] = 0;

        if constexpr (is_weighted) {
            dijkstraImpl(dist, start_node);
        } else {
            bfsImpl(dist, start_node);
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
    std::vector<EdgeType> shortestPath(i32 start_node, i32 end_node) const {
        std::vector<Cost> dist(N, CMAX);
        dist[start_node] = 0;
        std::vector<EdgePtr> prev_edge(N, nullptr);

        if constexpr (is_weighted) {
            prev_edge = dijkstraImpl(dist, start_node);
        } else {
            prev_edge = bfsImpl(dist, start_node);
        }

        if (dist[end_node] == CMAX)
            return {};

        i32 cu = end_node;
        std::vector<EdgeType> route;
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
    Matrix<Cost> distancesFromAllNodes(Cost invalid) const {
        auto mt(toMatrix(CMAX));

        for (i32 k = 0; k < N; k++)         // 経由する頂点
            for (i32 i = 0; i < N; i++)     // 始点
                for (i32 j = 0; j < N; j++) // 終点
                    if (mt[i][k] != CMAX && mt[k][j] != CMAX)
                        mt[i][j] = std::min(mt[i][j], mt[i][k] + mt[k][j]);

        for (i32 i = 0; i < N; ++i)
            for (i32 j = 0; j < N; ++j)
                if (mt[i][j] == CMAX)
                    mt[i][j] = invalid;
        return mt;
    }

  private:
    void preorderImpl(i32 cu, std::vector<bool> &visited,
                      std::vector<i32> &result) const {
        result.push_back(cu);
        for (auto &e : G[cu]) {
            i32 to = e->dst(cu);
            if (visited[to])
                continue;
            visited[to] = true;
            preorderImpl(to, visited, result);
        }
    }

    void inorderImpl(i32 cu, std::vector<bool> &visited,
                     std::vector<i32> &result) const {
        for (auto &e : G[cu]) {
            i32 to = e->dst(cu);
            if (visited[to])
                continue;
            visited[to] = true;
            result.push_back(cu);
            inorderImpl(to, visited, result);
        }
        result.push_back(cu);
    }

    void postorderImpl(i32 cu, std::vector<bool> &visited,
                       std::vector<i32> &result) const {
        for (auto &e : G[cu]) {
            i32 to = e->dst(cu);
            if (visited[to])
                continue;
            visited[to] = true;
            postorderImpl(to, visited, result);
        }
        result.push_back(cu);
    }

  public:
    /**
     * @brief 行きがけ順に dfs
     */
    std::vector<i32> preorder(i32 start) const {
        std::vector<i32> result;
        std::vector<bool> visited(N, false);
        visited[start] = true;
        preorderImpl(start, visited, result);
        return result;
    }

    /**
     * @brief 通りがけ順に dfs
     */
    std::vector<i32> inorder(i32 start) const {
        std::vector<i32> result;
        std::vector<bool> visited(N, false);
        visited[start] = true;
        inorderImpl(start, visited, result);
        return result;
    }

    /**
     * @brief 帰りがけ順に dfs
     */
    std::vector<i32> postorder(i32 start) const {
        std::vector<i32> result;
        std::vector<bool> visited(N, false);
        visited[start] = true;
        postorderImpl(start, visited, result);
        return result;
    }

    /**
     * @return 最小全域森
     */
    Graph MST() const {
        static_assert(is_weighted && !is_directed);
        Graph ret(N, N - 1);
        std::vector<i32> idx(E.size());
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(),
                  [&](i32 i, i32 j) { return E[i]->cost < E[j]->cost; });

        UnionFind uf(N);
        for (i32 i : idx) {
            if (!uf.isSame(E[i]->v0, E[i]->v1)) {
                uf.unite(E[i]->v0, E[i]->v1);
                ret.addEdge(*E[i]);
            }
        }
        return ret;
    }

    bool isBibartite() const {
        static_assert(!is_directed);
        std::vector<i32> col(N, -1);
        for (i32 i = 0; i < N; ++i) {
            if (col[i] == -1) {
                col[i] = 0;
                for (auto x : preorder(i)) {
                    for (auto &e : G[x]) {
                        i32 dst = e->dst(x);
                        if (col[dst] == col[x])
                            return false;
                        col[dst] = !col[x];
                    }
                }
            }
        }
        return true;
    }

    /**
     * @brief 連結成分ごとに分解
     * @return {分解後のグラフ、grp_id, nd_id}
     */
    std::tuple<std::vector<Graph>, std::vector<i32>, std::vector<i32>> discomponent() const {
        UnionFind uf(N);
        for (auto &e : E) {
            uf.unite(e->v0, e->v1);
        }
        i32 n_grps = uf.numGroups();
        auto grps = uf.getAllGroups();

        std::vector<i32> grp_id(N), nd_id(N);
        for (i32 i = 0; i < n_grps; ++i) {
            for (i32 j = 0; j < (i32)grps[i].size(); ++j) {
                grp_id[grps[i][j]] = i;
                nd_id[grps[i][j]] = j;
            }
        }

        std::vector<Graph> Gs(n_grps);
        for (i32 i = 0; i < n_grps; ++i) {
            Gs[i].resize(grps[i].size());
        } 
        for (auto &e : E) {
            i32 id = grp_id[e->v0];
            i32 u = nd_id[e->v0];
            i32 v = nd_id[e->v1];
            Gs[id].addEdge(u, v);
        }
        return {Gs, grp_id, nd_id};
    }

};
} // namespace gandalfr
