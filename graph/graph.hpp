#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include <tuple>
#include "gandalfr/graph/edge.hpp"
#include "gandalfr/data_structure/union_find.hpp"

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
            G[e.to].emplace_back(e);
        }
        if (!is_directed && e.from > e.to) std::swap(e.from, e.to);
        E.emplace_back(e);
        W += e.cost;
    }

  public:
    graph(): N(0), G(0), uf(0) {};
    graph(int n): N(n), G(n), uf(n) {};

    // ノードの数を返す
    int num_nodes() const { return N; }

    // 辺の数を返す
    int num_edges() const { return E.size(); }
    
    // ノードの数を変更
    void expand(int n){
        if(n <= N) return;
        N = n;
        G.resize(n);
        uf.expand(n);
    }

    // ノード n に接続した辺集合にアクセス
    const std::vector<edge<WEIGHT>> &operator[](int n) const { return G[n]; }

    // グラフ全体の辺集合にアクセス
    const std::vector<edge<WEIGHT>> &edge_set() const { return E; }

    // x, y が連結かどうか
    bool are_connected(int x, int y) { return uf.same(x, y); }

    // 連結なグラフの数を返す
    int num_connected_components() const { return uf.count_groups(); }

    std::vector<std::vector<int>> connected_components(){ return uf.groups(); }

    WEIGHT weight() const { return W; }

    void add_edge(const edge<WEIGHT> &e){
        internal_add_edge(e);
    }

    template<typename T = WEIGHT>
    typename std::enable_if<!std::is_same<T, int>::value>::type 
    add_edge(int from, int to, WEIGHT cost) {
        internal_add_edge(edge<WEIGHT>(from, to, cost, E.size()));
    }

    template<typename T = WEIGHT>
    typename std::enable_if<std::is_same<T, int>::value>::type 
    add_edge(int from, int to) {
        internal_add_edge(edge<int>(from, to, E.size()));
    }

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