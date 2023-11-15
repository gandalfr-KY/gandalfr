#pragma once
#include <assert.h>
#include <queue>
#include <tuple>
#include <vector>

#include "../data_structure/union_find.hpp"
#include "../math/matrix.hpp"
#include "base_graph.hpp"

/**
 * @brief グラフを管理するクラス。
 * @tparam Weight int なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <typename Weight, bool is_directed>
class graph : public internal::_base_graph<edge<Weight>> {
  private:
    union_find uf;
    mutable std::vector<bool> visited; // dfs / bfs のための領域
    Weight W = 0;
    bool forest_flag = true;
    bool does_have_minus_edge = false;

    void reset_visited_flag(int node) const {
        for (int x : uf.group_containing_node(node))
            visited[x] = false;
    }

    void reset_visited_flag() const { visited.assign(this->N, false); }

  public:
    static inline const Weight EDGE_MAX = std::numeric_limits<Weight>::max();
    static inline const Weight EDGE_LOWEST =
        std::numeric_limits<Weight>::lowest();

    graph() {}
    graph(int n, int m)
        : internal::_base_graph<edge<Weight>>(n, m), uf(n), visited(n) {}
    graph(const graph &other) : graph(other.N, other.num_edges()) {
        for (auto &e : other.E) {
            add_edge(e);
        }
    }

    /**
     * @brief ノードの数を V 個、辺の本数を E 本に拡張する
     * @param n サイズ
     * @attention 今のノードの数や辺の本数より小さい数を渡したとき、変化なし
     */
    void expand(int n, int m) override {
        if (n > this->N) {
            this->N = n;
            this->G.resize(n);
            visited.resize(n);
            uf.expand(n);
        }
        if (m > (int)this->E.capacity()) {
            this->E.reserve(m);
            // TODO 拡張後 G を再構成する必要あり
        }
    }

    /**
     * @return 木か
     */
    bool is_tree() const { return forest_flag && uf.count_groups() == 1; }

    /**
     * @return 森か
     */
    bool is_forest() const { return forest_flag; }

    /**
     * @return グラフの重み
     */
    Weight weight() const { return W; }

    /**
     * @param e 辺
     * @attention 渡した辺の id は保持される
     */
    void add_edge(const edge<Weight> &e) {
        assert(this->E.size() < this->E.capacity());
        forest_flag &= uf.merge(e.v[0], e.v[1]);
        does_have_minus_edge |= (e.cost < 0);

        this->E.push_back(e);
        edge<Weight> &new_edge = this->E.back();

        this->G[e.v[0]].push_back(&new_edge);
        if constexpr (!is_directed) {
            if (e.v[0] != e.v[1]) {
                this->G[e.v[1]].push_back(&new_edge);
            }
        }
        W += e.cost;
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が int だとエラー
     */
    void add_edge(int from, int to, Weight cost) {
        static_assert(!std::is_same<Weight, int>::value);
        add_edge({from, to, cost, (int)this->E.size()});
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     * @attention WEIGHT が int 以外だとエラー
     */
    void add_edge(int from, int to) {
        static_assert(std::is_same<Weight, int>::value);
        add_edge({from, to, (int)this->E.size()});
    }

    /**
     * @param x ノード番号
     * @param y ノード番号
     * @return x, y が連結かどうか
     */
    bool are_connected(int x, int y) const { return uf.same(x, y); }

    /**
     * @return 弱連結成分の数
     */
    int num_connected_components() const { return uf.count_groups(); }

    /**
     * @return 弱連結成分のリストのリスト
     */
    std::vector<std::vector<int>> weakly_connected_components() const {
        return uf.all_groups();
    }

    /**
     * @brief ノード x が含まれている弱連結成分のリストを返す
     */
    std::vector<int> component_containing_node(int x) {
        return uf.group_containing_node(x);
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
        std::vector<int> group_id(this->N), node_id(this->N),
            cnt_edges(uf.count_groups(), 0);

        for (int i = 0; i < (int)groups.size(); i++) {
            for (int j = 0; j < (int)groups[i].size(); j++) {
                group_id[groups[i][j]] = i;
                node_id[groups[i][j]] = j;
            }
        }
        for (auto &e : this->E) {
            ++cnt_edges[group_id[e.v[0]]];
        }
        for (int i = 0; i < (int)Gs.size(); ++i) {
            Gs[i].expand(groups[i].size(), cnt_edges[i]);
        }

        for (auto e : this->E) {
            int id = group_id[e.v[0]];
            e.v[0] = node_id[e.v[0]];
            e.v[1] = node_id[e.v[1]];
            Gs[id].add_edge(e);
        }
        return std::make_tuple(std::move(Gs), std::move(group_id),
                               std::move(node_id));
    }

    /**
     * @brief グラフを隣接行列に変換
     * @param invalid 辺のないときの値
     * @attention 自己ループが含まれていない限り、対角成分は 0
     * @attention 多重辺を持たないと仮定
     */
    matrix<Weight> to_adjajency(Weight invalid) const {
        matrix<Weight> ret(this->N, this->N, invalid);
        for (int i = 0; i < this->N; i++)
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
    using PAIR = std::pair<Weight, int>;
    using Dijkstra_queue =
        std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>>;

    void run_bfs(std::vector<const edge<Weight> *> &prev_edge,
                 std::vector<int> &dist, std::queue<int> &q) const {
        while (!q.empty()) {
            int cu = q.front();
            q.pop();
            for (auto &e : this->G[cu]) {
                int to = e->opp(cu);
                if (dist[to] != EDGE_MAX)
                    continue;
                prev_edge[to] = e;
                dist[to] = dist[cu] + 1;
                q.push(to);
            }
        }
    }

    // verify : https://atcoder.jp/contests/abc137/submissions/47602884
    bool run_BellmanFord(std::vector<const edge<Weight> *> &prev_edge,
                         std::vector<Weight> &dist) const {
        bool has_negative_cycle = false;
        for (int i = 0; i < 2 * this->N; ++i) {
            bool changed = false;
            for (auto &e : this->E) {
                auto upd = [&](int s, int t) {
                    if (dist[s] != EDGE_MAX) {
                        Weight alt =
                            (dist[s] == EDGE_LOWEST ? EDGE_LOWEST
                                                    : dist[s] + e.cost);
                        if (dist[t] > alt) {
                            dist[t] = (i < this->N ? alt : EDGE_LOWEST);
                            prev_edge[t] = &e;
                            changed = true;
                        }
                    }
                };
                upd(e.v[0], e.v[1]);
                if constexpr (!is_directed) {
                    upd(e.v[1], e.v[0]);
                }
            }
            if (!changed) {
                break;
            } else if (i == this->N - 1) {
                has_negative_cycle = true;
            }
        }
        return has_negative_cycle;
    }

    void run_Dijkstra(std::vector<const edge<Weight> *> &prev_edge,
                      std::vector<Weight> &dist, Dijkstra_queue &q) const {
        while (!q.empty()) {
            Weight cur_dist = q.top().first;
            int cu = q.top().second;
            q.pop();

            if (visited[cu])
                continue;
            visited[cu] = true;

            for (auto &e : this->G[cu]) {
                int to = e->opp(cu);
                Weight alt = cur_dist + e->cost;
                if (dist[to] <= alt)
                    continue;
                prev_edge[to] = e;
                dist[to] = alt;
                q.push({alt, to});
            }
        }
    }

  public:
    /**
     * @brief 最短距離を計算する
     * @param start_node 始点
     * @param invalid 到達不能な頂点に格納される値
     * @return 各ノードまでの最短距離のリスト
     * @attention 負閉路に影響を受ける頂点は EDGE_LOWEST が代入される
     */
    std::vector<Weight> distances(int start_node, Weight invalid) const {
        std::vector<Weight> dist(this->N, EDGE_MAX);
        dist[start_node] = 0;
        std::vector<const edge<Weight> *> prev_edge(this->N, nullptr);
        if constexpr (std::is_same<Weight, int>::value) {
            std::queue<int> q;
            q.push(start_node);
            run_bfs(prev_edge, dist, q);
        } else if (does_have_minus_edge) {
            run_BellmanFord(prev_edge, dist);
        } else {
            Dijkstra_queue q;
            q.push({0, start_node});
            reset_visited_flag(start_node);
            run_Dijkstra(prev_edge, dist, q);
        }

        for (auto &x : dist)
            if (x == EDGE_MAX)
                x = invalid;
        return dist;
    }

    matrix<Weight> distances_from_all_nodes(Weight invalid = -1) {
        auto mt(to_adjajency(EDGE_MAX));

        for (int k = 0; k < this->N; k++)         // 経由する頂点
            for (int i = 0; i < this->N; i++)     // 始点
                for (int j = 0; j < this->N; j++) // 終点
                    if (mt(i, k) != EDGE_MAX && mt(k, j) != EDGE_MAX)
                        mt(i, j) = std::min(mt(i, j), mt(i, k) + mt(k, j));

        for (int i = 0; i < this->N; ++i)
            for (int j = 0; j < this->N; ++j)
                if (mt(i, j) == EDGE_MAX)
                    mt(i, j) = invalid;
        return mt;
    }

    /**
     * @brief 復元付き最短経路
     * @attention 到達可能でないとき、空の配列で返る
     * @attention 負閉路があるとき正しい動作を保証しない
     */
    std::vector<edge<Weight>> shortest_path(int start_node, int end_node) {
        std::vector<const edge<Weight> *> prev_path;
        std::vector<Weight> dist(this->N, EDGE_MAX);
        dist[start_node] = 0;
        std::vector<const edge<Weight> *> prev_edge(this->N, nullptr);

        if constexpr (std::is_same<Weight, int>::value) {
            std::queue<int> q;
            q.push(start_node);
            run_bfs(prev_edge, dist, q);
        } else if (does_have_minus_edge) {
            assert(!run_BellmanFord(prev_edge, dist));
        } else {
            Dijkstra_queue q;
            q.push({0, start_node});
            reset_visited_flag(start_node);
            run_Dijkstra(prev_edge, dist, q);
        }

        if (dist[end_node] == EDGE_MAX)
            return {};

        int cu = end_node;
        std::vector<edge<Weight>> route;
        while (cu != start_node) {
            auto e = prev_edge[cu];
            if (cu == e->v[0]) {
                route.push_back(e->reverse());
            } else {
                route.push_back(*e);
            }
            cu = e->opp(cu);
        }
        return {route.rbegin(), route.rend()};
    }

    Weight diameter() const {
        static_assert(!is_directed);
        assert(is_tree());
        std::vector<Weight> dist(distances(0, -1));
        dist = distances(
            std::max_element(dist.begin(), dist.end()) - dist.begin(), -1);
        return *std::max_element(dist.begin(), dist.end());
    }

    graph reverse() const {
        if constexpr (!is_directed) {
            return *this;
        } else {
            graph ret(this->N);
            for (auto &e : this->E) {
                ret.add_edge(e.reverse());
            }
            return ret;
        }
    }

    /**
     * @brief 行きがけ順に dfs
     */
    std::vector<int> preorder(int start) const {
        std::vector<int> result;
        reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            result.push_back(cu);
            for (auto &e : this->G[cu]) {
                int to = e->opp(cu);
                if (visited[to])
                    continue;
                visited[to] = true;
                self(self, to);
            }
        };
        dfs(dfs, start);
        return result;
    }

    /**
     * @brief 通りがけ順に dfs
     */
    std::vector<int> inorder(int start) const {
        std::vector<int> result;
        reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            for (auto &e : this->G[cu]) {
                int to = e->opp(cu);
                if (visited[to])
                    continue;
                visited[to] = true;
                result.push_back(cu);
                self(self, to);
            }
            result.push_back(cu);
        };
        dfs(dfs, start);
        return result;
    }

    /**
     * @brief 帰りがけ順に dfs
     */
    std::vector<int> postorder(int start) const {
        std::vector<int> result;
        reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            for (auto &e : this->G[cu]) {
                int to = e->opp(cu);
                if (visited[to])
                    continue;
                visited[to] = true;
                self(self, to);
            }
            result.push_back(cu);
        };
        dfs(dfs, start);
        return result;
    }

    std::vector<int> topological_sort() {
        static_assert(is_directed);
        std::vector<int> indeg(this->N, 0), sorted;
        for (auto &e : this->E) {
            indeg[e.v[1]]++;
        }

        std::queue<int> q;
        for (int i = 0; i < this->N; i++)
            if (!indeg[i])
                q.push(i);
        while (!q.empty()) {
            int cu = q.front();
            q.pop();
            for (auto e : this->G[cu]) {
                int to = e->opp(cu);
                if (!--indeg[to])
                    q.push(to);
            }
            sorted.push_back(cu);
        }
        return sorted;
    }

    /**
     * @return 最小全域森
     */
    graph minimum_spanning_forest() const {
        static_assert(!is_directed);
        graph ret(this->N, this->N - 1);
        std::vector<int> idx(this->E.size());
        std::iota(idx.begin(), idx.end(), 0);

        std::sort(idx.begin(), idx.end(), [&](int i, int j) {
            auto a = &this->E[i], b = &this->E[j];
            if (a->cost == b->cost) {
                if (a->v[0] == b->v[0]) {
                    return a->v[1] < b->v[1];
                }
                return a->v[0] < b->v[0];
            }
            return a->cost < b->cost;
        });

        for (int i : idx) {
            if (!ret.are_connected(this->E[i].v[0], this->E[i].v[1]))
                ret.add_edge(this->E[i]);
        }
        return ret;
    }

    bool is_bibartite() {
        std::vector<int> col(this->N, -1);
        auto bfs = [&](int start) -> bool {
            std::queue<int> q;
            q.push(start);
            col[start] = 0;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (auto &e : this->G[cur]) {
                    int to = e->opp(cur);
                    if (col[to] == -1) {
                        col[to] = (col[cur] == 0);
                        q.push(to);
                    } else if (col[cur] == col[to]) {
                        return false;
                    }
                }
            }
            return true;
        };
        for (int i = 0; i < this->N; ++i) {
            if (col[i] == -1 && !bfs(i)) {
                return false;
            }
        }
        return true;
    }

  private:
    /**
     * @see https://ei1333.github.io/luzhiled/snippets/graph/lowlink.html
     * @attention 非連結でも動作
     */
    int run_lowlink(int idx, int k, int par, std::vector<int> &ord,
                    std::vector<int> &low, std::vector<edge<Weight>> &brds,
                    std::vector<int> &apts) {
        visited[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_apt = false;
        int cnt = 0;
        for (auto &e : this->G[idx]) {
            int to = e->opp(idx);
            if (!visited[to]) {
                ++cnt;
                k = run_lowlink(to, k, idx, ord, low, brds, apts);
                low[idx] = std::min(low[idx], low[to]);
                is_apt |= ~par && low[to] >= ord[idx];
                if (ord[idx] < low[to]) {
                    brds.emplace_back(*e);
                }
            } else if (to != par) {
                low[idx] = std::min(low[idx], ord[to]);
            }
        }
        is_apt |= par == -1 && cnt > 1;
        if (is_apt)
            apts.push_back(idx);
        return k;
    }

  public:
    /**
     * @return pair<vector<橋>, vector<関節点>>
     */
    std::pair<std::vector<edge<Weight>>, std::vector<int>> lowlink() {
        static_assert(!is_directed);
        std::vector<edge<Weight>> brds;
        std::vector<int> apts, ord(this->N, 0), low(this->N, 0);
        reset_visited_flag();
        int k = 0;
        for (int i = 0; i < this->N; i++) {
            if (!visited[i])
                k = run_lowlink(i, k, -1, ord, low, brds, apts);
        }
        return {brds, apts};
    }

    // verify: https://atcoder.jp/contests/abc232/submissions/45715440
    // 同型判定
    bool operator==(const graph &other) const {
        if (this->N != other.num_nodes())
            return false;
        if (this->num_edges() != other.num_edges())
            return false;
        if (this->count_connected_components() !=
            other.count_connected_components())
            return false;

        matrix<Weight> adj1(to_adjajency()), adj2(other.to_adjajency());

        std::vector<int> nodes_id(this->N);
        std::iota(nodes_id.begin(), nodes_id.end(), 0);
        do {
            bool ok = true;
            for (int i = 0; i < this->N; i++)
                for (int j = 0; j < this->N; j++) {
                    if (adj1(i, j) != adj2(nodes_id[i], nodes_id[j])) {
                        ok = false;
                        break;
                    }
                }
            if (ok)
                return true;
        } while (std::next_permutation(nodes_id.begin(), nodes_id.end()));
        return false;
    }

    bool operator!=(const graph &other) const { return !operator==(other); }
};
