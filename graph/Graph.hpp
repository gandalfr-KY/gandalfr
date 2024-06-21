#pragma once
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "../math/Matrix.hpp"
#include "../types.hpp"

#define GRAPH_TEMPLATE template <bool is_weighted, bool is_directed>
#define GRAPH_TYPE Graph<is_weighted, is_directed>
#define GRAPH_EDGE_PTR typename GRAPH_TYPE::EdgePtr
#define GRAPH_EDGE_TYPE typename GRAPH_TYPE::EdgeType
#define GRAPH_COST_TYPE typename GRAPH_TYPE::Cost

namespace gandalfr {

constexpr bool WEIGHTED = true;
constexpr bool UNWEIGHTED = false;
constexpr bool DIRECTED = true;
constexpr bool UNDIRECTED = false;

template <bool is_weighted> struct Edge {
    Edge() = delete;
};

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
    Graph(const Graph &other)
        : N(other.N), G(other.N), cost_sum(other.cost_sum) {
        for (i32 i = 0; i < (i32)other.G.size(); ++i) {
            for (const auto &e : other[i]) {
                G[i].push_back(std::make_shared<EdgeType>(*e));
            }
        }
        for (const auto &e : other.E) {
            E.push_back(std::make_shared<EdgeType>(*e));
        }
    }
    Graph(Graph &&other) noexcept
        : N(other.N), G(std::move(other.G)), E(std::move(other.E)),
          cost_sum(other.cost_sum) {
        other.N = 0;
        other.cost_sum = 0;
    }

    Graph &operator=(const Graph &other) {
        if (this != &other) {
            N = other.N;
            G.clear(), E.clear();
            G.resize(other.G.size());
            cost_sum = other.cost_sum;
            for (i32 i = 0; i < (i32)other.G.size(); ++i) {
                for (const auto &e : other.G[i]) {
                    G[i].push_back(std::make_shared<EdgeType>(*e));
                }
            }
            for (const auto &e : other.E) {
                E.push_back(std::make_shared<EdgeType>(*e));
            }
        }
        return *this;
    }
    Graph &operator=(Graph &&other) noexcept {
        if (this != &other) {
            N = other.N;
            G = std::move(other.G);
            E = std::move(other.E);
            cost_sum = other.cost_sum;
            other.N = 0;
            other.cost_sum = 0;
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
                                      i32 start_node) const;
    std::vector<EdgePtr> bfsImpl(std::vector<i32> &dist, i32 start_node) const;

  public:
    /**
     * @brief 最短距離を計算する
     * @param start_node 始点
     * @param invalid 到達不能な頂点に格納される値
     * @return 各ノードまでの最短距離のリスト
     * @note "shortestPath.hpp" をインクルードすること
     */
    std::vector<Cost> distances(i32 start_node, Cost invalid) const;

    /**
     * @brief 復元付き最短経路
     * @attention 到達可能でないとき、空の配列で返る
     * @attention 負閉路があるとき正しい動作を保証しない
     * @note "shortestPath.hpp" をインクルードすること
     */
    std::vector<EdgeType> shortestPath(i32 start_node, i32 end_node) const;

    /**
     * @brief ワーシャルフロイド法 O(N^3)
     * @note "shortestPath.hpp" をインクルードすること
     */
    Matrix<Cost> distancesFromAllNodes(Cost invalid) const;

  private:
    void preorderImpl(i32 cu, std::vector<bool> &visited,
                      std::vector<i32> &result) const;

    void inorderImpl(i32 cu, std::vector<bool> &visited,
                     std::vector<i32> &result) const;

    void postorderImpl(i32 cu, std::vector<bool> &visited,
                       std::vector<i32> &result) const;

  public:
    /**
     * @brief 行きがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> preorder(i32 start) const;
    /**
     * @brief visited が false のノードを行きがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> preorder(i32 start, std::vector<bool> &visited) const;

    /**
     * @brief 通りがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> inorder(i32 start) const;
    /**
     * @brief visited が false のノードを行きがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> inorder(i32 start, std::vector<bool> &visited) const;

    /**
     * @brief 帰りがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> postorder(i32 start) const;
    /**
     * @brief visited が false のノードを行きがけ順に dfs
     * @note "dfs.hpp" をインクルードすること
     */
    std::vector<i32> postorder(i32 start, std::vector<bool> &visited) const;

    /**
     * @return 最小全域森
     */
    Graph mst() const;

    /**
     * @return 二部グラフかどうか
     */
    bool isBipartite() const;

    /**
     * @brief 連結成分ごとに分解
     * @return {分解後のグラフ、grp_id, nd_id}
     */
    std::tuple<std::vector<Graph>, std::vector<i32>, std::vector<i32>>
    discomponent() const;

    /**
     * @brief 強連結成分ごとに分解
     * @return {縮約後のグラフ、nd_id}
     */
    std::tuple<Graph, std::vector<i32>> scc() const;

    // private:
    void lowlinkImpl(i32 cu, i32 e_id, i32 &id, std::vector<i32> &ord,
                     std::vector<i32> &low,
                     Graph<is_weighted, DIRECTED> &tree) const;
    std::tuple<std::vector<i32>, std::vector<i32>, Graph<is_weighted, DIRECTED>>
    lowlink() const;

  public:
    /**
     * @brief グラフの橋を求める たぶん非連結でもOK
     */
    std::vector<EdgeType> bridges() const;

    /**
     * @brief グラフの関節点を求める たぶん非連結でもOK
     */
    std::vector<i32> articulationPoints() const;
};
} // namespace gandalfr
