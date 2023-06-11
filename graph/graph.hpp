#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include <tuple>
#include "edge.hpp"
#include "../data_structure/union_find.hpp"

/**
 * @brief グラフを管理するクラス。
 * @tparam WEIGHT int なら重みなし、そうでないなら重みつきグラフ
 * @tparam is_directed 有向グラフかとうか
 */
template <typename WEIGHT, bool is_directed>
class graph{
    private:
    int N;
    std::vector<std::vector<edge<WEIGHT>>> G;
    std::vector<edge<WEIGHT>> E;
    union_find uf;
    WEIGHT W = 0;

    void internal_add_edge(edge<WEIGHT> e) {
        uf.merge(e.from, e.to);
        G[e.from].emplace_back(e);
        if (!is_directed && e.from != e.to) {
            std::swap(e.from, e.to);
            G[e.from].emplace_back(e);
        }
        if (!is_directed && e.from > e.to) std::swap(e.from, e.to);
        E.emplace_back(e);
        W += e.cost;
    }

  public:
    graph(): N(0), G(0), uf(0) {};
    graph(int n): N(n), G(n), uf(n) {};

    /**
     * @brief ノードの数をn個まで増やす
     * @param n サイズ
     * @attention 今のノード数より小さい数を渡したとき、変化なし
     */ 
    void expand(int n){
        if(n <= N) return;
        N = n;
        G.resize(n);
        uf.expand(n);
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
    std::vector<std::vector<int>> connected_components(){ return uf.groups(); }

    /**
     * @return グラフの重み
     */
    WEIGHT weight() const { return W; }

    /**
     * @param e 辺
     * @attention 渡した辺の id は保持される 
     */
    void add_edge(const edge<WEIGHT> &e){
        internal_add_edge(e);
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる 
     * @attention WEIGHT が int だとエラー
     */
    template<typename T = WEIGHT>
    typename std::enable_if<!std::is_same<T, int>::value>::type 
    add_edge(int from, int to, WEIGHT cost) {
        internal_add_edge(edge<WEIGHT>(from, to, cost, E.size()));
    }

    /**
     * @attention 辺の id は、(現在の辺の本数)番目 が振られる 
     * @attention WEIGHT が int 以外だとエラー
     */
    template<typename T = WEIGHT>
    typename std::enable_if<std::is_same<T, int>::value>::type 
    add_edge(int from, int to) {
        internal_add_edge(edge<int>(from, to, E.size()));
    }

    /**
     * @brief グラフを連結なグラフに分けてリストにして返す
     * @example auto[Gs, gr, nd] = G.decompose();
     * @returns
     * 1.グラフのリスト 
     * 2.各ノードがグラフのリストの何番目に属するか 
     * 3.各ノードがグラフのどのノードになっているか 
    */
    std::tuple<std::vector<graph>, std::vector<int>, std::vector<int>> decompose() {
        std::vector<graph> Gs(uf.count_groups());
        std::vector<std::vector<int>> groups(uf.groups());
        std::vector<int> group_id(N), node_id(N);
        for (int i = 0; i < groups.size(); i++) {
            Gs[i].expand(groups[i].size());
            for (int j = 0; j < groups[i].size(); j++) {
                group_id[groups[i][j]] = i;
                node_id[groups[i][j]] = j;
            }
        }
        for (auto& e : E) {
            int id = group_id[e.from];
            e.from = node_id[e.from];
            e.to = node_id[e.to];
            Gs[id].add_edge(e);
        }
        return std::make_tuple(Gs, group_id, node_id);
    }

    void print() const {
        std::cout << this->N << " " << this->E.size() << std::endl;
        for(const edge<WEIGHT> &e : this->E) std::cout << e << std::endl;
    }

    class iterator {
      private:
        friend class graph;
        const std::vector<std::vector<edge<WEIGHT>>>* edges;
        std::size_t index;
        iterator(const std::vector<std::vector<edge<WEIGHT>>>* edges, std::size_t index) : edges(edges), index(index) {}

      public:
        bool operator==(const iterator& other) const { return edges == other.edges && index == other.index; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        const std::vector<edge<WEIGHT>> &operator*() const { return (*edges)[index]; }
        iterator& operator++() {
            index++;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
    };
    iterator begin() const { return iterator(&G, 0); }
    iterator end() const { return iterator(&G, G.size()); }
};

#endif