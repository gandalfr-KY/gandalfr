#ifndef GRAPH_STRUCTURE
#define GRAPH_STRUCTURE
#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stl_numeric.h>
#include <assert.h>
#include <iostream>

template<class EDGE_TYPE>
class _base_graph{
  protected:
    int N, M = 0;
    std::vector<std::vector<EDGE_TYPE>> G;
    std::vector<EDGE_TYPE> E;

  public:
    _base_graph(): N(0), G(0) {};
    _base_graph(int n): N(n), G(n) {};

    // ノードの数を返す
    int nodes() const { return N; }

    // 辺の数を返す
    int edges() const { return M; }
    
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
        std::cout << N << " " << M << std::endl;
        for(EDGE_TYPE &e : E) std::cout << e << std::endl;
    }

};

struct unweighted_edge{
    int from;
    int to;
    int id;
    friend bool operator>(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to > e2.to;
        }
        return e1.from > e2.from;
    }
    friend bool operator>=(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to >= e2.to;
        }
        return e1.from > e2.from;
    }
    friend bool operator<(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to < e2.to;
        }
        return e1.from < e2.from;
    }
    friend bool operator<=(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to <= e2.to;
        }
        return e1.from < e2.from;
    }
    friend std::ostream &operator<<(std::ostream &os, const unweighted_edge &e) {
        os << e.from << " " << e.to << " " << e.id;
        return os;
    }
};

template<class WEIGHT>
struct weighted_edge{
    int from;
    int to;
    WEIGHT cost;
    int id;
    friend bool operator>(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to > e2.to;
            }
            return e1.from > e2.from;
        }
        return e1.cost > e2.cost;
    }
    friend bool operator>=(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to >= e2.to;
            }
            return e1.from > e2.from;
        }
        return e1.cost > e2.cost;
    }
    friend bool operator<(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to < e2.to;
            }
            return e1.from < e2.from;
        }
        return e1.cost < e2.cost;
    }
    friend bool operator<=(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to <= e2.to;
            }
            return e1.from < e2.from;
        }
        return e1.cost < e2.cost;
    }
    friend std::ostream &operator<<(std::ostream &os, const weighted_edge &e) {
        os << e.from << " " << e.to << " " << e.cost << " " << e.id;
        return os;
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
        if(is_directed){
            BG::G[from].emplace_back(unweighted_edge{from, to, BG::M});
            BG::E.emplace_back(unweighted_edge{from, to, BG::M++});
        }
        else{
            BG::G[from].emplace_back(unweighted_edge{from, to, BG::M});
            BG::G[to].emplace_back(unweighted_edge{to, from, BG::M});
            BG::E.emplace_back(unweighted_edge{std::min(from, to), std::max(from, to), M++});
        }
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
    void add_edge(int from, int to, WEIGHT weight){
        if(is_directed){
            BG::G[from].emplace_back(WE{from, to, weight, BG::M});
            BG::E.emplace_back(WE{from, to, weight, BG::M++});
        }
        else{
            BG::G[from].emplace_back(WE{from, to, weight, BG::M});
            BG::G[to].emplace_back(WE{to, from, weight, BG::M});
            BG::E.emplace_back(WE{std::min(from, to), std::max(from, to), weight, BG::M++});
        }
    }


};

#endif