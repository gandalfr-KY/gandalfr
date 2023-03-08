#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include "gandalfr/graph/edge.hpp"
#include "gandalfr/data_structure/union_find.hpp"

template<class EDGE_TYPE>
class _base_graph{
  protected:
    int N;
    std::vector<std::vector<EDGE_TYPE>> G;
    std::vector<EDGE_TYPE> E;
	union_find uf;

  public:
    _base_graph(): N(0), G(0), uf(0) {};
    _base_graph(int n): N(n), G(n), uf(n) {};

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
    const std::vector<EDGE_TYPE> &operator[](int n) const { return G[n]; }

    // グラフ全体の辺集合にアクセス
    const std::vector<EDGE_TYPE> &edge_set() const { return E; }

	// x, y が連結かどうか
	bool is_connected(int x, int y) { return uf.same(x, y); }

    // 連結なグラフの数を返す
    int count_connected_components() { return uf.count_groups(); }

	// 連結成分をまとめたやつ
	// O(N)なので注意
	std::vector<std::vector<int>> connected_groups() { return uf.groups(); }

    void print() const {
        std::cout << N << " " << E.size() << std::endl;
        for(const EDGE_TYPE &e : E) std::cout << e << std::endl;
    }

};

template<bool is_directed>
class unweighted_graph : public _base_graph<unweighted_edge>{
  private:
    using UWE = unweighted_edge;
  public:
    // コンストラクタ
    using _base_graph<UWE>::_base_graph;

    // 辺の追加
    void add_edge(int from, int to){
        int id = this->E.size();
        this->G[from].emplace_back(UWE{from, to, id});
        if(!is_directed && from != to) {
            this->G[to].emplace_back(UWE{to, from, id});
            // 無向辺のとき、E に格納する辺は from < to で統一する
            if(from > to) std::swap(from, to);
        }
        this->E.emplace_back(UWE{from, to, id});
		this->uf.merge(from, to);
    }

    // 辺 id の扱いに注意
    void add_edge(const UWE &e){
        this->G[e.from].emplace_back(e);
        if(!is_directed && e.from != e.to) this->G[e.to].emplace_back(UWE{e.to, e.from, e.id});
        this->E.emplace_back(e);
		this->uf.merge(e.from, e.to);
    }

};

template<class WEIGHT, bool is_directed>
class weighted_graph : public _base_graph<weighted_edge<WEIGHT>>{
  private:
    using WE = weighted_edge<WEIGHT>;
  public:
    // コンストラクタ
    using _base_graph<WE>::_base_graph;

    // 辺の追加
    void add_edge(int from, int to, WEIGHT cost){
        int id = this->E.size();
        this->G[from].emplace_back(WE{from, to, cost, id});
        if(!is_directed && from != to) {
            this->G[to].emplace_back(WE{to, from, cost, id});
            // 無向辺のとき、E に格納する辺は from < to で統一する
            if(from > to) std::swap(from, to);
        }
        this->E.emplace_back(WE{from, to, cost, id});
		this->uf.merge(from, to);
    }

    // 辺を直接追加する場合、有向辺として追加することに注意
    // 辺 id の扱いに注意
    void add_edge(const WE &e){
        this->G[e.from].emplace_back(e);
        if(!is_directed && e.from != e.to) this->G[e.to].emplace_back(WE{e.to, e.from, e.cost, e.id});
        this->E.emplace_back(e);
		this->uf.merge(e.from, e.to);
    }

};

#endif