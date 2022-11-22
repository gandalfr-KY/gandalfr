#ifndef GRAPH_STRUCT
#define GRAPH_STRUCT
#include <vector>
#include <algorithm>
#include "gandalfr/graph/edge.hpp"

template<class EDGE_TYPE>
class _base_graph{
  protected:
    int N;
    std::vector<std::vector<EDGE_TYPE>> G;
    std::vector<EDGE_TYPE> E;

  public:
    _base_graph(): N(0), G(0) {};
    _base_graph(int n): N(n), G(n) {};

    // ノードの数を返す
    int nodes() const { return N; }

    // 辺の数を返す
    int edges() const { return E.size(); }
    
    // ノードの数を変更
    void resize(int n){
        N = n;
        G.resize(n);
    }

    // ノード n に接続した辺集合にアクセス
    const std::vector<EDGE_TYPE> &operator[](int n) const { return G[n]; }

    // グラフ全体の辺集合にアクセス
    const std::vector<EDGE_TYPE> &edge_set() const { return E; }

    void print() const {
        std::cout << N << " " << E.size() << std::endl;
        for(const EDGE_TYPE &e : E) std::cout << e << std::endl;
    }

};

template<bool is_directed>
class unweighted_graph : public _base_graph<unweighted_edge>{
  private:
    using UWE = unweighted_edge;
    using BG = _base_graph<UWE>;
  public:
    // コンストラクタ
    using BG::_base_graph;

    // 辺の追加
    void add_edge(int from, int to){
        int id = BG::E.size();
        BG::G[from].emplace_back(UWE{from, to, id});
        if(!is_directed && from != to) {
            BG::G[to].emplace_back(UWE{to, from, id});
            // 無向辺のときは from < to で統一する
            if(from > to) std::swap(from, to);
        }
        BG::E.emplace_back(UWE{from, to, id});
    }

    // 辺 id の扱いに注意
    void add_edge(const UWE &e){
        BG::G[e.from].emplace_back(e);
        if(!is_directed && e.from != e.to) BG::G[e.to].emplace_back(UWE{e.to, e.from, e.id});
        BG::E.emplace_back(e);
    }

};

template<class WEIGHT, bool is_directed>
class weighted_graph : public _base_graph<weighted_edge<WEIGHT>>{
  private:
    using WE = weighted_edge<WEIGHT>;
    using BG = _base_graph<WE>;
  public:
    // コンストラクタ
    using BG::_base_graph;

    // 辺の追加
    void add_edge(int from, int to, WEIGHT cost){
        int id = BG::E.size();
        BG::G[from].emplace_back(WE{from, to, cost, id});
        if(!is_directed && from != to) {
            BG::G[to].emplace_back(WE{to, from, cost, id});
            // 無向辺のときは from < to で統一する
            if(from > to) std::swap(from, to);
        }
        BG::E.emplace_back(WE{from, to, cost, id});
    }

    // 辺を直接追加する場合、有向辺として追加することに注意
    // 辺 id の扱いに注意
    void add_edge(const WE &e){
        BG::G[e.from].emplace_back(e);
        if(!is_directed && e.from != e.to) BG::G[e.to].emplace_back(WE{e.to, e.from, e.cost, e.id});
        BG::E.emplace_back(e);
    }

};

#endif