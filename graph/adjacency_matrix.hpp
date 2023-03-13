#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

// 多重辺なし
template<bool is_directed>
matrix<int> adjacency_matrix(const internal::_base_graph<int, is_directed> &G, int invalid = 0){
    matrix<int> ret(G.nodes(), G.nodes(), invalid);
    for(const internal::_base_edge<int> &e : G.edge_set()){
        ret[e.from][e.to] = 1;
        if(!is_directed) ret[e.to][e.from] = 1;
    }
    return ret;
}

template<class WEIGHT, bool is_directed>
matrix<WEIGHT> adjacency_matrix(const internal::_base_graph<WEIGHT, is_directed> &G, WEIGHT invalid = -1){
    matrix<WEIGHT> ret(G.nodes(), G.nodes(), invalid);
    for(int i = 0; i < G.nodes(); i++) ret[i][i] = 0;
    for(const internal::_base_edge<WEIGHT> &e : G.edge_set()){
        ret[e.from][e.to] = e.cost;
        if(!is_directed) ret[e.to][e.from] = e.cost;
    }
    return ret;
}

#endif