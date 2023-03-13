#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include "gandalfr/graph/edge.hpp"
#include "gandalfr/data_structure/union_find.hpp"

namespace internal{
    template<typename WEIGHT>
    class _empty_graph{
      protected:
        int N;
        std::vector<std::vector<internal::_base_edge<WEIGHT>>> G;
        std::vector<internal::_base_edge<WEIGHT>> E;
        union_find uf;

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
        int count_connected_components() { return uf.count_groups(); }

        // 連結成分をまとめたやつ
        // O(N)なので注意
        std::vector<std::vector<int>> connected_groups() { return uf.groups(); }
        
        void print() const {
            std::cout << this->N << " " << this->E.size() << std::endl;
            for(const internal::_base_edge<WEIGHT> &e : this->E) std::cout << e << std::endl;
        }

    };

    template<typename WEIGHT, bool is_directed>
    class _base_graph : public _empty_graph<WEIGHT>{
      public:
        // コンストラクタ
        using _empty_graph<WEIGHT>::_empty_graph;

        // 辺の追加
        void add_edge(int from, int to, WEIGHT cost){
            int id = this->E.size();
            this->G[from].emplace_back(internal::_base_edge<WEIGHT>{from, to, cost, id});
            if(!is_directed && from != to) {
                this->G[to].emplace_back(internal::_base_edge<WEIGHT>{to, from, cost, id});
                // 無向辺のとき、E に格納する辺は from < to で統一する
                if(from > to) std::swap(from, to);
            }
            this->E.emplace_back(internal::_base_edge<WEIGHT>{from, to, cost, id});
            this->uf.merge(from, to);
        }

        // 辺 id の扱いに注意
        void add_edge(const _base_edge<WEIGHT> &e){
            this->G[e.from].emplace_back(e);
            if(!is_directed && e.from != e.to) this->G[e.to].emplace_back(internal::_base_edge<WEIGHT>{e.to, e.from, e.cost, e.id});
            this->E.emplace_back(e);
            this->uf.merge(e.from, e.to);
        }
        

    };

    template<bool is_directed>
    class _base_graph<int, is_directed> : public _empty_graph<int>{
      public:
        // コンストラクタ
        using _empty_graph<int>::_empty_graph;

        // 辺の追加
        void add_edge(int from, int to){
            int id = this->E.size();
            this->G[from].emplace_back(internal::_base_edge<int>{from, to, id});
            if(!is_directed && from != to) {
                this->G[to].emplace_back(internal::_base_edge<int>{to, from, id});
                // 無向辺のとき、E に格納する辺は from < to で統一する
                if(from > to) std::swap(from, to);
            }
            this->E.emplace_back(internal::_base_edge<int>{from, to, id});
            this->uf.merge(from, to);
        }

        // 辺 id の扱いに注意
        void add_edge(const _base_edge<int> &e){
            this->G[e.from].emplace_back(e);
            if(!is_directed && e.from != e.to) this->G[e.to].emplace_back(internal::_base_edge<int>{e.to, e.from, e.id});
            this->E.emplace_back(e);
            this->uf.merge(e.from, e.to);
        }
    };
}

using weighted_directed_graph = internal::_base_graph<long long, true>;
using weighted_undirected_graph = internal::_base_graph<long long, false>;
using unweighted_directed_graph = internal::_base_graph<int, true>;
using unweighted_undirected_graph = internal::_base_graph<int, false>;

#endif