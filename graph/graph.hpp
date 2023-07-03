#pragma once
#include <algorithm>
#include <stack>
#include <tuple>
#include <vector>
#include <assert.h>

#include "../data_structure/union_find.hpp"
#include "../math/matrix.hpp"
#include "edge.hpp"

/**
 * @brief グラフを管理するクラス。
 * @tparam WEIGHT int なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <typename WEIGHT, bool is_directed> class graph {
  private:
    int N;
    std::vector<std::vector<edge<WEIGHT>>> G;
    std::vector<edge<WEIGHT>> E;
    union_find uf;
    WEIGHT W = 0;

    std::vector<bool> visited;

  public:
    graph() : N(0), G(0), uf(0), visited(0) {};
    graph(int n) : N(n), G(n), uf(n), visited(n) {};

    /**
     * @brief ノードの数をn個まで増やす
     * @param n サイズ
     * @attention 今のノード数より小さい数を渡したとき、変化なし
     */
    void expand(int n) {
        if (n <= N)
            return;
        N = n;
        G.resize(n);
        uf.expand(n);
        visited.resize(n);
    }

    /**
     * @return ノードの数
     */
    int count_nodes() const { return N; }

    /**
     * @return 辺の数
     */
    int count_edges() const { return E.size(); }

    /**
     * @param n ノード番号
     * @return ノード n からの隣接頂点のリストの const 参照
     */
    const std::vector<edge<WEIGHT>> &operator[](int n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<edge<WEIGHT>> &edges() const { return E; }

    /**
     * @param x ノード番号
     * @param y ノード番号
     * @return x, y が連結かどうか
     */
    bool are_connected(int x, int y) { return uf.same(x, y); }

    /**
     * @return 連結成分の数
     */
    int count_connected_components() const { return uf.count_groups(); }

    /**
     * @return 連結成分のリストのリスト
     */
    std::vector<std::vector<int>> connected_components() const { return uf.all_groups(); }

    /**
     * @return 木か
     */
    bool is_tree() const {
        return (uf.count_groups() == 1 && (int)E.size() == N - 1);
    }

    /**
     * @return グラフの重み
     */
    WEIGHT weight() const { return W; }

    /**
     * @param e 辺
     * @attention 渡した辺の id は保持される
     */
    void add_edge(edge<WEIGHT> e) {
        uf.merge(e.from, e.to);
        E.emplace_back(e);
        G[e.from].emplace_back(e);
        if (!is_directed && e.from != e.to) {
            std::swap(e.from, e.to);
            G[e.from].emplace_back(e);
        }
        W += e.cost;
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が int だとエラー
     */
    void add_edge(int from, int to, WEIGHT cost) {
        static_assert(!std::is_same<WEIGHT, int>::value);
        if (!is_directed && from > to)
            std::swap(from, to);
        add_edge(edge<WEIGHT>(from, to, cost, E.size()));
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が int 以外だとエラー
     */
    void add_edge(int from, int to) {
        static_assert(std::is_same<WEIGHT, int>::value);
        if (!is_directed && from > to)
            std::swap(from, to);
        add_edge(edge<int>(from, to, E.size()));
    }

    /**
     * @brief グラフを連結なグラフに分けてリストにして返す
     * @example auto[Gs, gr, nd] = G.decompose();
     * @returns
     * 1.グラフのリスト
     * 2.各ノードがグラフのリストの何番目に属するか
     * 3.各ノードがグラフのどのノードになっているか
     */
    std::tuple<std::vector<graph>, std::vector<int>, std::vector<int>>
    decompose() const {
        std::vector<graph> Gs(uf.count_groups());
        std::vector<std::vector<int>> groups(uf.all_groups());
        std::vector<int> group_id(N), node_id(N);
        for (int i = 0; i < groups.size(); i++) {
            Gs[i].expand(groups[i].size());
            for (int j = 0; j < groups[i].size(); j++) {
                group_id[groups[i][j]] = i;
                node_id[groups[i][j]] = j;
            }
        }
        for (auto e : E) {
            int id = group_id[e.from];
            e.from = node_id[e.from];
            e.to = node_id[e.to];
            Gs[id].add_edge(e);
        }
        return std::make_tuple(Gs, group_id, node_id);
    }

    /**
     * @brief グラフを隣接行列に変換
     * @param invalid 辺のないときの値
     * @attention G に自己ループが含まれていない限り、対角成分は 0
     */
    matrix<WEIGHT> to_adjajency(WEIGHT invalid = 0) const {
        int N = count_nodes();
        matrix<WEIGHT> ret(N, N, invalid);
        for (int i = 0; i < N; i++)
            ret[i][i] = 0;
        for (int i = 0; i < N; i++) {
            for (auto &e : G[i]) {
                ret[e.from][e.to] = e.cost;
            }
        }
        return ret;
    }

    /**
     * @brief 行きがけ順に bfs
     * @attention グラフは連結であることが必要
    */
    std::vector<int> preorder(int start) {
        assert(uf.count_groups() == 1);
        std::vector<int> result;
        std::stack<std::pair<int, int>> stk;
        for(int x : uf.contained_group(start))
            visited[x] = false;
        visited[start] = true;
        stk.push({start, 0});

        while (!stk.empty()) {
            auto &[cu, idx] = stk.top();
            if (idx == 0)
                result.push_back(cu);
            if (idx == G[cu].size()) {
                stk.pop();
            } else {
                int to = G[cu][idx++];
                if (!visited[to]) {
                    visited[to] = true;
                    stk.push({to, 0});
                }
            }
        }
        return result;
    }
    
    std::vector<int> inorder(int start) {
        std::vector<int> result;
        std::stack<std::pair<int, int>> stk;
        for(int x : uf.contained_group(start))
            visited[x] = false;
        stk.push({start, 0});

        while (!stk.empty()) {
            auto &[cu, idx] = stk.top();
            if (idx == G[cu].size()) {
                stk.pop();
                result.push_back(cu);
            } else {
                int to = G[cu][idx++];
                if (!visited[to]) {
                    visited[to] = true;
                    stk.push({to, 0});
                    result.push_back(cu);
                }
            }
        }
        return result;
    }

    std::vector<int> postorder(int start) {
        std::vector<int> result;
        std::stack<std::pair<int, int>> stk;
        for(int x : uf.contained_group(start))
            visited[x] = false;
        visited[start] = true;
        stk.push({start, 0});

        while (!stk.empty()) {
            auto &[cu, idx] = stk.top();
            if (idx == G[cu].size()) {
                stk.pop();
                result.push_back(cu);
            } else {
                int to = G[cu][idx++];
                if (!visited[to]) {
                    visited[to] = true;
                    stk.push({to, 0});
                }
            }
        }
        return result;
    }

    graph<WEIGHT, is_directed> reverse() const {
        if (!is_directed)
            return *this;
        graph<WEIGHT, is_directed> ret(count_nodes());
        for (auto e : edges()) {
            std::swap(e.from, e.to);
            ret.add_edge(e);
        }
        return ret;
    }

    /**
     * @return 最小全域森
     */
    graph<WEIGHT, false> minimum_spanning_tree() const {
        static_assert(!is_directed);
        graph<WEIGHT, false> ret(count_nodes());
        std::vector<edge<WEIGHT>> E(edges());
        std::sort(E.begin(), E.end());
        for (auto &e : E)
            if (!ret.are_connected(e.from, e.to)) {
                ret.add_edge(e);
            }
        return ret;
    }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for (const edge<WEIGHT> &e : this->E)
            std::cout << e << std::endl;
    }
};
