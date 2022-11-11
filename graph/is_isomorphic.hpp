#ifndef IS_ISOMORPHIC
#define IS_ISOMORPHIC
#include "gandalfr/graph/graph.hpp"
/*
// 同型判定
bool is_isomorphic(const unweighted_graph &graph){
    assert(is_directed == graph.is_directed);
    if(N != graph.N) return false;
    if(M != graph.M) return false;
    std::vector<std::vector<std::vector<int>>> adjacency_matrix(2, std::vector<std::vector<int>>(N, std::vector<int>(N, false)));
    for(unweighted_edge &e : E){
        adjacency_matrix[0][e.from][e.to] = true;
        if(!is_directed) adjacency_matrix[0][e.to][e.from] = true;
    }
    for(const unweighted_edge &e : graph.E){
        adjacency_matrix[1][e.from][e.to] = true;
        if(!is_directed) adjacency_matrix[1][e.to][e.from] = true;
    }

    std::vector<int> nodes_id(N);
    std::iota(nodes_id.begin(), nodes_id.end(), 0);
    do{
        bool same = true;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(adjacency_matrix[0][i][j] != adjacency_matrix[1][nodes_id[i]][nodes_id[j]]) same = false;
        if(same) return true;
    }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
    return false;
}

// 同型判定
bool is_isomorphic(const weighted_graph<WEIGHT> &graph){
    assert(is_directed == graph.is_directed);
    if(N != graph.N) return false;
    if(M != graph.M) return false;
    std::vector<std::vector<std::vector<WEIGHT>>> adjacency_matrix(2, std::vector<std::vector<WEIGHT>>(N, std::vector<WEIGHT>(N, 0)));
    for(weighted_edge<WEIGHT> &e : E){
        adjacency_matrix[0][e.from][e.to] = e.cost;
        if(!is_directed) adjacency_matrix[0][e.to][e.from] = e.cost;
    }
    for(const weighted_edge<WEIGHT> &e : graph.E){
        adjacency_matrix[1][e.from][e.to] = e.cost;
        if(!is_directed) adjacency_matrix[1][e.to][e.from] = e.cost;
    }

    std::vector<int> nodes_id(N);
    std::iota(nodes_id.begin(), nodes_id.end(), 0);
    do{
        bool same = true;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(adjacency_matrix[0][i][j] != adjacency_matrix[1][nodes_id[i]][nodes_id[j]]) same = false;
        if(same) return true;
    }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
    return false;
}
*/

#endif