#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include <tuple>
#include "gandalfr/graph/edge.hpp"
#include "gandalfr/data_structure/union_find.hpp"

namespace internal{
    template<typename WEIGHT, bool is_directed>
    class _empty_graph{
      protected:
        int N;
        std::vector<std::vector<internal::_base_edge<WEIGHT>>> G;
        std::vector<internal::_base_edge<WEIGHT>> E;
        union_find uf;
        WEIGHT W = 0;

      public:
        _empty_graph(): N(0), G(0), uf(0) {};
        _empty_graph(int n): N(n), G(n), uf(n) {};

        // ノードの数を返す
        int nodes() const { return N; }

        // 辺の数を返す
        int edges() const { return E.size(); }
        
        // ノードの数を変更
        void expand(int n){
            if(n <= N) return;
            N = n;
            G.resize(n);
            uf.expand(n);
        }

        // ノード n に接続した辺集合にアクセス
        const std::vector<internal::_base_edge<WEIGHT>> &operator[](int n) const { return G[n]; }

        // グラフ全体の辺集合にアクセス
        const std::vector<internal::_base_edge<WEIGHT>> &edge_set() const { return E; }

        // x, y が連結かどうか
        bool is_connected(int x, int y) { return uf.same(x, y); }

        // 連結なグラフの数を返す
        int count_connected_components() const { return uf.count_groups(); }

        std::vector<std::vector<int>> connected_components(){ return uf.groups(); }

        WEIGHT weight() const { return W; }

        // id は保たれる
        void add_edge(internal::_base_edge<WEIGHT> e){
            E.emplace_back(e);
            uf.merge(e.from, e.to);
            this->G[e.from].emplace_back(e);
            if(!is_directed && e.from != e.to) {
                std::swap(e.from, e.to);
                G[e.from].emplace_back(e);
            }
            W += e.cost;
        }

        void print() const {
            std::cout << this->N << " " << this->E.size() << std::endl;
            for(const internal::_base_edge<WEIGHT> &e : this->E) std::cout << e << std::endl;
        }

        class iterator {
          private:
            friend class _empty_graph;
            const std::vector<std::vector<internal::_base_edge<WEIGHT>>>* edges;
            std::size_t index;
            iterator(const std::vector<std::vector<internal::_base_edge<WEIGHT>>>* edges, std::size_t index) : edges(edges), index(index) {}

          public:
            bool operator==(const iterator& other) const { return edges == other.edges && index == other.index; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            const std::vector<internal::_base_edge<WEIGHT>> &operator*() const { return (*edges)[index]; }
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

    template <typename WEIGHT, bool is_directed>
    class _base_graph : public _empty_graph<WEIGHT, is_directed> {
      public:
        using _empty_graph<WEIGHT, is_directed>::_empty_graph;
        using edge_type = internal::_base_edge<WEIGHT>;

        void add_edge(int from, int to, WEIGHT cost) {
            int id = this->E.size();
            this->G[from].emplace_back(edge_type{from, to, cost, id});
            this->uf.merge(from, to);
            if (!is_directed && from != to) {
                this->G[to].emplace_back(edge_type{to, from, cost, id});
                if (from > to) std::swap(from, to);
            }
            this->E.emplace_back(edge_type{from, to, cost, id});
            this->W += cost;
        }

        void add_edge(int from, int to) {
            int id = this->E.size();
            this->G[from].emplace_back(edge_type{from, to, id});
            this->uf.merge(from, to);
            if (!is_directed && from != to) {
                this->G[to].emplace_back(edge_type{to, from, id});
                if (from > to) std::swap(from, to);
            }
            this->E.emplace_back(edge_type{from, to, id});
            this->W++;
        }

        using _empty_graph<WEIGHT, is_directed>::add_edge;

        std::tuple<std::vector<_base_graph>, std::vector<int>, std::vector<int>> decompose() {
            std::vector<_base_graph> Gs(this->uf.count_groups());
            std::vector<std::vector<int>> groups(this->uf.groups());
            std::vector<int> group_id(this->nodes()), node_id(this->nodes());
            for (int i = 0; i < groups.size(); i++) {
                Gs[i].expand(groups[i].size());
                for (int j = 0; j < groups[i].size(); j++) {
                    group_id[groups[i][j]] = i;
                    node_id[groups[i][j]] = j;
                }
            }
            for (edge_type& e : this->E) {
                int id = group_id[e.from];
                e.from = node_id[e.from];
                e.to = node_id[e.to];
                Gs[id].add_edge(e);
            }
            return std::make_tuple(Gs, group_id, node_id);
        }
    };
}

using weighted_directed_graph = internal::_base_graph<long long, true>;
using weighted_undirected_graph = internal::_base_graph<long long, false>;
using unweighted_directed_graph = internal::_base_graph<int, true>;
using unweighted_undirected_graph = internal::_base_graph<int, false>;

#endif