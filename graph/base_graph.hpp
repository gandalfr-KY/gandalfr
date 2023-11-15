#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

namespace internal {
template <class Weight> struct _base_edge {
    int v[2]; //  有向グラフのとき、v[0] が src, v[1] が dst
              //  であることを保証する
    Weight cost;
    int id;
    _base_edge() { v[0] = -1; }
    _base_edge(int from, int to, Weight cost, int id)
        : v{from, to}, cost(cost), id(id) {}

    // デフォルトコンストラクタで初期化された直後は false
    bool is_valid() const { return v[0] == -1; }

    // x から見た反対側の端点を返す
    // 無向グラフのときの dst の取得はこれを使う
    int opp(int x) const {
        if (x == v[0]) {
            return v[1];
        } else if (x == v[1]) {
            return v[0];
        } else {
            std::abort();
        }
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const _base_edge<Weight> &e) {
        e.print(os);
        return os;
    }

  protected:
    virtual void print(std::ostream &os) const = 0;
};
} // namespace internal

template <class Weight> struct edge : public internal::_base_edge<Weight> {
    using internal::_base_edge<Weight>::_base_edge;

    edge reverse() const {
        return {this->v[1], this->v[0], this->cost, this->id};
    }

  protected:
    void print(std::ostream &os) const override {
        os << this->v[0] << " " << this->v[1] << " " << this->cost;
    }
};

template <> struct edge<int> : public internal::_base_edge<int> {
    static inline const int cost = 1;
    using internal::_base_edge<int>::_base_edge;
    edge(int _from, int _to, int _id) : _base_edge<int>(_from, _to, 1, _id) {}

    edge reverse() const { return {v[1], v[0], 1, id}; }

  protected:
    void print(std::ostream &os) const override {
        os << this->v[0] << " " << this->v[1];
    }
};

template <class Flow, class Cost>
struct flow_edge : public internal::_base_edge<Cost> {
  private:
    Flow res, cap;
    using internal::_base_edge<Cost>::cost;

  public:
    flow_edge() {}
    flow_edge(int from, int to, Flow res, Flow cap, int id)
        : internal::_base_edge<Cost>(from, to, 1, id), res(res), cap(cap) {}
    flow_edge(int from, int to, Flow res, Flow cap, Cost cost, int id)
        : internal::_base_edge<Cost>(from, to, cost, id), res(res), cap(cap) {}

    // x から見たコスト
    Cost get_cost(int x) {
        if (x == this->v[0]) {
            return this->cost;
        } else if (x == this->v[1]) {
            return -this->cost;
        } else {
            std::abort();
        }
    }

    flow_edge reverse() const {
        return {this->v[1], this->v[0], cap - res, cap, this->cost, this->id};
    }

    // x から見た残余
    Flow residual(int x) const {
        if (x == this->v[0]) {
            return res;
        } else if (x == this->v[1]) {
            return cap - res;
        } else {
            std::abort();
        }
    }

    // x から見て残余がゼロか？
    Flow is_full(int x) const {
        if (x == this->v[0]) {
            return res == 0;
        } else if (x == this->v[1]) {
            return cap - res == 0;
        } else {
            std::abort();
        }
    }

    // x から流量を d だけ追加
    void add_flow(int x, Flow d) {
        if (x == this->v[0]) {
            res -= d;
        } else if (x == this->v[1]) {
            res += d;
        } else {
            std::abort();
        }
    }

  protected:
    void print(std::ostream &os) const override {
        os << this->v[0] << " " << this->v[1] << " " << cap - res << "/" << cap;
    }
};

namespace internal {

template <typename Edge> class _base_graph {
  protected:
    int N;
    std::vector<std::vector<Edge *>> G;
    std::vector<Edge> E;

  public:
    _base_graph(){};
    _base_graph(int n, int m) : N(n), G(n) { E.reserve(m); };

    virtual void expand(int n, int m) = 0;

    /**
     * @return ノードの数
     */
    int num_nodes() const { return N; }

    /**
     * @return 辺の数
     */
    int num_edges() const { return E.size(); }

    /**
     * @param n ノード番号
     * @return ノード n からの隣接頂点のリストの const 参照
     */
    const std::vector<Edge *> &operator[](int n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<Edge> &get_edges() const { return E; }
    /**
     * @return idx 番目に張られた辺の const 参照
     */
    const Edge &get_edge(int idx) const { return E[idx]; }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for (auto &e : this->E)
            std::cout << e << std::endl;
    }
};
} // namespace internal
