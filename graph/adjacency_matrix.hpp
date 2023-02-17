#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

// 多重辺なし
template<bool is_directed>
matrix<int> adjacency_matrix(const unweighted_graph<is_directed> &graph, int invalid = 0){
    matrix<int> ret(graph.nodes(), graph.nodes(), invalid);
    for(const unweighted_edge &e : graph.edge_set()){
        ret[e.from][e.to] = 1;
        if(!is_directed) ret[e.to][e.from] = 1;
    }
    return ret;
}

template<class WEIGHT, bool is_directed>
matrix<WEIGHT> adjacency_matrix(const weighted_graph<WEIGHT, is_directed> &graph, WEIGHT invalid = -1){
    matrix<WEIGHT> ret(graph.nodes(), graph.nodes(), invalid);
    for(int i = 0; i < graph.nodes(); i++) ret[i][i] = 0;
    for(const weighted_edge<WEIGHT> &e : graph.edge_set()){
        ret[e.from][e.to] = e.cost;
        if(!is_directed) ret[e.to][e.from] = e.cost;
    }
    return ret;
}

#endif