#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

/* 多重辺なし
 * invalid := 非隣接のときの値
 */
template<typename WEIGHT, bool is_directed>
matrix<int> adjacency_matrix(const internal::_base_graph<WEIGHT, is_directed> &G, int invalid){
    matrix<int> ret(G.nodes(), G.nodes(), invalid);
    for(const internal::_base_edge<WEIGHT> &e : G.edge_set()){
        ret[e.from][e.to] = e.cost;
        if(!is_directed) ret[e.to][e.from] = e.cost;
    }
    return ret;
}

#endif