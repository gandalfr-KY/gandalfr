#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

#include "gandalfr/types.hpp"

namespace gandalfr {

constexpr bool WEIGHTED = true;
constexpr bool UNWEIGHTED = false;

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

    friend std::ostream &operator<<(std::ostream &os, const Edge& e) {
        os << e.v0 << ' ' << e.v1 << ' ' << e.cost;
        return os;
    }
};

template <> struct Edge<UNWEIGHTED> {

    using Cost = i32;

    i32 v0, v1;
    const Cost cost = 1;
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

    friend std::ostream &operator<<(std::ostream &os, const Edge& e) {
        os << e.v0 << ' ' << e.v1;
        return os;
    }
};

// template <class Flow, class Cost>
// struct flow_edge : public internal::_base_edge<Cost> {
//   private:
//     Flow res, cap;
//     using internal::_base_edge<Cost>::cost;

//   public:
//     flow_edge() {}
//     flow_edge(i32 from, i32 to, Flow res, Flow cap, i32 id)
//         : internal::_base_edge<Cost>(from, to, 1, id), res(res), cap(cap) {}
//     flow_edge(i32 from, i32 to, Flow res, Flow cap, Cost cost, i32 id)
//         : internal::_base_edge<Cost>(from, to, cost, id), res(res), cap(cap) {}

//     // x から見たコスト
//     Cost get_cost(i32 x) {
//         if (x == this->v[0]) {
//             return this->cost;
//         } else if (x == this->v[1]) {
//             return -this->cost;
//         } else {
//             std::abort();
//         }
//     }

//     flow_edge reverse() const {
//         return {this->v[1], this->v[0], cap - res, cap, this->cost, this->id};
//     }

//     // x から見た残余
//     Flow residual(i32 x) const {
//         if (x == this->v[0]) {
//             return res;
//         } else if (x == this->v[1]) {
//             return cap - res;
//         } else {
//             std::abort();
//         }
//     }

//     // x から見て残余がゼロか？
//     Flow is_full(i32 x) const {
//         if (x == this->v[0]) {
//             return res == 0;
//         } else if (x == this->v[1]) {
//             return cap - res == 0;
//         } else {
//             std::abort();
//         }
//     }

//     // x から流量を d だけ追加
//     void add_flow(i32 x, Flow d) {
//         if (x == this->v[0]) {
//             res -= d;
//         } else if (x == this->v[1]) {
//             res += d;
//         } else {
//             std::abort();
//         }
//     }

//     std::ostream &operator<<(std::ostream &os) {
//         os << this->v[0] << " " << this->v[1] << " " << cap - res << "/" << cap;
//     }
// };

namespace impl {

template <bool is_weighted> class BaseGraph {
  protected:
    i32 N;
    std::vector<std::vector<std::shared_ptr<Edge<is_weighted>>>> G;
    std::vector<Edge<is_weighted>> E;

  public:
    BaseGraph(){};
    BaseGraph(i32 n, i32 m) : N(n), G(n) { E.reserve(m); };

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
    const std::vector<std::shared_ptr<Edge<is_weighted>>> &operator[](i32 n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<Edge<is_weighted>> &getAllEdges() const { return E; }
    /**
     * @return idx 番目に張られた辺の const 参照
     */
    const Edge<is_weighted> &getEdge(i32 idx) const { return E[idx]; }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for (auto &e : this->E)
            std::cout << e << std::endl;
    }
};
} // namespace impl



} // namespace gandalfr
