#pragma once
#include <algorithm>
#include <assert.h>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

#include "../data_structure/union_find.hpp"
#include "../math/matrix.hpp"
#include "edge.hpp"

namespace internal {

template <typename Edge> class _base_graph {
  protected:
    int N;
    std::vector<std::vector<Edge>> G;
    std::vector<Edge> E;

  public:
    _base_graph() {};
    _base_graph(int n) : N(n), G(n) {};

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
    const std::vector<Edge> &operator[](int n) const { return G[n]; }

    /**
     * @return グラフ全体の辺のリストの const 参照
     */
    const std::vector<Edge> &edges() const { return E; }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for (const Edge &e : this->E)
            std::cout << e << std::endl;
    }
};
}

/**
 * @brief グラフを管理するクラス。
 * @tparam Weight int なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <typename Weight, bool is_directed> class graph: public internal::_base_graph<edge<Weight>> {
  private:
    union_find uf;
    mutable std::vector<bool> visited; // dfs / bfs のための領域
    Weight W = 0;
    bool forest_flag = true;
    static const Weight WEIGHT_MAX = std::numeric_limits<Weight>::max();

    void reset_visited_flag(int node) const {
        for (int x : uf.group_containing_node(node))
            visited[x] = false;
    }

    void reset_visited_flag() const { visited.assign(this->N, false); }

  public:
    graph() {}
    graph(int n) : internal::_base_graph<edge<Weight>>(n), uf(n), visited(n) {}

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
        visited.resize(n);
        uf.expand(n);
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
        forest_flag &= uf.merge(e.from, e.to);

        this->G[e.from].emplace_back(e);
        if (!is_directed && e.from != e.to)
            this->G[e.to].emplace_back(e.reverse());

        if constexpr (is_directed) {
            this->E.emplace_back(e);
        } else {
            this->E.emplace_back(e.minmax());
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
    int count_connected_components() const { return uf.count_groups(); }

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
        std::vector<int> group_id(this->N), node_id(this->N);
        for (int i = 0; i < (int)groups.size(); i++) {
            Gs[i].expand(groups[i].size());
            for (int j = 0; j < (int)groups[i].size(); j++) {
                group_id[groups[i][j]] = i;
                node_id[groups[i][j]] = j;
            }
        }
        for (auto e : this->E) {
            int id = group_id[e.from];
            e.from = node_id[e.from];
            e.to = node_id[e.to];
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
    matrix<Weight> to_adjajency(Weight invalid = 0) const {
        matrix<Weight> ret(this->N, this->N, invalid);
        for (int i = 0; i < this->N; i++)
            ret(i, i) = 0;
        for (int i = 0; i < this->N; i++)
            for (auto &e : this->G[i])
                ret(i, e.to) = e.cost;
        return ret;
    }

  private:
    using PAIR = std::pair<Weight, int>;
    using Dijkstra_queue =
        std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>>;

    void run_bfs(std::vector<int> &dist, std::queue<int> &q) const {
        while (!q.empty()) {
            int cu = q.front();
            q.pop();
            for (auto &e : this->G[cu]) {
                if (dist[e.to] != WEIGHT_MAX)
                    continue;
                dist[e.to] = dist[cu] + 1;
                q.push(e.to);
            }
        }
    }

    void run_Dijkstra(std::vector<Weight> &dist, Dijkstra_queue &q) const {
        while (!q.empty()) {
            Weight cur_dist = q.top().first;
            int cu = q.top().second;
            q.pop();

            if (visited[cu])
                continue;
            visited[cu] = true;

            for (auto &e : this->G[cu]) {
                Weight alt = cur_dist + e.cost;
                if (dist[e.to] <= alt)
                    continue;
                dist[e.to] = alt;
                q.push({alt, e.to});
            }
        }
    }

  public:

    /**
     * @brief 最短距離を計算する
     * @param start_node 始点
     * @param invalid 到達不能な頂点に格納される値
     * @return 各ノードまでの最短距離のリスト
     */
    std::vector<Weight> distances(int start_node, Weight invalid) const {
        std::vector<Weight> dist(this->N, WEIGHT_MAX);
        dist[start_node] = 0;

        if constexpr (std::is_same<Weight, int>::value) {
            // BFS algorithm
            std::queue<int> q;
            q.push(start_node);
            run_bfs(dist, q);
        } else {
            // Dijkstra's algorithm
            Dijkstra_queue q;
            q.push({0, start_node});
            this->reset_visited_flag(start_node);
            run_Dijkstra(dist, q);
        }

        for (auto &x : dist)
            if (x == WEIGHT_MAX)
                x = invalid;
        return dist;
    }

    /**
     * @brief 最短距離を計算する
     * @param start_nodes 始点のリスト
     * @param invalid 到達不能な頂点に格納される値
     * @return 各ノードまでの最短距離のリスト
     */
    std::vector<Weight> distances(const std::vector<int> &start_nodes,
                                  Weight invalid) const {
        std::vector<Weight> dist(this->N, WEIGHT_MAX);
        for (auto &x : start_nodes)
            dist[x] = 0;

        if constexpr (std::is_same<Weight, int>::value) {
            // BFS algorithm
            std::queue<int> q;
            for (auto &x : start_nodes)
                q.push(x);
            run_bfs(dist, q);
        } else {
            // Dijkstra's algorithm
            Dijkstra_queue q;
            std::set<int> st;
            for (auto &x : start_nodes) {
                q.push({0, x});
                st.insert(uf.leader(x));
            }
            for (auto &x : st) {
                this->reset_visited_flag(x);
            }
            run_Dijkstra(dist, q);
        }

        for (auto &x : dist)
            if (x == WEIGHT_MAX)
                x = invalid;
        return dist;
    }

    matrix<Weight> distances_from_all_nodes(Weight invalid = -1) {
        auto mt(to_adjajency(WEIGHT_MAX));

        for (int k = 0; k < this->N; k++)         // 経由する頂点
            for (int i = 0; i < this->N; i++)     // 始点
                for (int j = 0; j < this->N; j++) // 終点
                    if (mt(i, k) != WEIGHT_MAX && mt(k, j) != WEIGHT_MAX)
                        mt(i, j) = std::min(mt(i, j), mt(i, k) + mt(k, j));

        for (int i = 0; i < this->N; ++i)
            for (int j = 0; j < this->N; ++j)
                if (mt(i, j) == WEIGHT_MAX)
                    mt(i, j) = invalid;
        return mt;
    }

    /**
     * @brief 復元付き最短経路
     * @attention 到達可能でないとき、空の配列で返る
     */
    std::vector<edge<Weight>> shortest_path(int start_node, int end_node) {
        if (start_node == end_node)
            return {};

        auto dist = distances(start_node, WEIGHT_MAX);
        if (dist[end_node] == WEIGHT_MAX)
            return {};

        auto R(this->reverse());
        this->reset_visited_flag(end_node);
        visited[end_node] = true;

        int cu = end_node;
        std::vector<edge<Weight>> route;
        while (cu != start_node) {
            for (auto e : R[cu]) {
                if (visited[e.to])
                    continue;
                if (dist[cu] - e.cost == dist[e.to]) {
                    visited[cu = e.to] = true;
                    route.push_back(e.reverse());
                    break;
                }
            }
        }
        std::reverse(route.begin(), route.end());
        return route;
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
        this->reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            result.push_back(cu);
            for (int to : this->G[cu]) {
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
        this->reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            for (int to : this->G[cu]) {
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
        this->reset_visited_flag(start);
        visited[start] = true;
        auto dfs = [&](auto self, int cu) -> void {
            for (int to : this->G[cu]) {
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
        for (int to : this->E)
            indeg[to]++;

        std::queue<int> q;
        for (int i = 0; i < this->N; i++)
            if (!indeg[i])
                q.push(i);
        while (!q.empty()) {
            int cu = q.front();
            q.pop();
            for (int to : this->G[cu]) {
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
        graph ret(this->N);
        std::vector<edge<Weight>> tmp(this->edges());
        std::sort(tmp.begin(), tmp.end(), [](const edge<Weight> &a, const edge<Weight> &b) {
            if (a.cost == b.cost) {
                if (a.from == b.from) {
                    return a.to < b.to;
                }
                return a.from < b.from;
            }
            return a.cost < b.cost;
        });

        for (auto &e : tmp)
            if (!ret.are_connected(e.from, e.to))
                ret.add_edge(e);
        return ret;
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
            if (!visited[e.to]) {
                ++cnt;
                k = run_lowlink(e.to, k, idx, ord, low, brds, apts);
                low[idx] = std::min(low[idx], low[e.to]);
                is_apt |= ~par && low[e.to] >= ord[idx];
                if (ord[idx] < low[e.to]) {
                    brds.emplace_back(e.minmax());
                }
            } else if (e.to != par) {
                low[idx] = std::min(low[idx], ord[e.to]);
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
        this->reset_visited_flag();
        int k = 0;
        for (int i = 0; i < this->N; i++) {
            if (!visited[i])
                k = run_lowlink(i, k, -1, ord, low, brds, apts);
        }
        return {brds, apts};
    }
};

template <typename Weight, typename Flow> class flow_graph: public internal::_base_graph<flow_edge<Weight, Flow>> {
  public:
    using internal::_base_graph<flow_edge<Weight, Flow>>::_base_graph;

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
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる
     */
    void add_edge(int from, int to, Flow capacity) {
        int id = (int)this->E.size();
        flow_edge<Weight, Flow> e(from, to, capacity, capacity, id);
        this->E.push_back(e);
        this->G[from].push_back(e);
        int idx = this->G[from].size() - 1;
        this->G[to].push_back(e.reverse());
        int r_idx = this->G[to].size() - 1;
        this->G[from][idx].r_idx = r_idx;
        this->G[to][r_idx].r_idx = idx;
    }

    Flow Ford_Fulkerson(int s, int t) {

        Flow flow = 0;
        while(true) {
            std::vector<bool> vis(this->N, false);
            auto dfs = [&](auto self, int cur, Flow f) -> Flow {
                if (cur == t) return f;
                vis[cur] = true;
                for (auto &e: this->G[cur]) {
                    if (vis[e.to] || e.residual == static_cast<Flow>(0)) continue;
                    Flow tmp = self(self, e.to, std::min<Flow>(e.residual, f));
                    if (tmp > static_cast<Flow>(0)) {
                        e.residual -= tmp;
                        this->G[e.to][e.r_idx].residual += tmp;
                        return tmp;
                    }
                }
                return static_cast<Flow>(0);
            };
            Flow inc = dfs(dfs, s, std::numeric_limits<Flow>::max());
            if (inc == 0) break;
            flow += inc;
        }
        return flow;
    }

};
