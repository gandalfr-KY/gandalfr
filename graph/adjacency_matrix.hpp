#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

// 非隣接 := 0
// 多重辺なし
template<bool is_directed>
matrix<int> adjacency_matrix(const unweighted_graph<is_directed> &graph){
    matrix<int> ret(graph.nodes(), graph.nodes(), 0);
    for(const unweighted_edge &e : graph.edge_set()){
        ret[e.from][e.to] = 1;
        if(!is_directed) ret[e.to][e.from] = 1;
    }
    return ret;
}

// 非隣接 := -1
template<class WEIGHT, bool is_directed>
matrix<WEIGHT> adjacency_matrix(const weighted_graph<WEIGHT, is_directed> &graph){
    matrix<WEIGHT> ret(graph.nodes(), graph.nodes(), -1);
    for(const weighted_edge<WEIGHT> &e : graph.edge_set()){
        ret[e.from][e.to] = e.cost;
        if(!is_directed) ret[e.to][e.from] = e.cost;
    }
    return ret;
}

#endif