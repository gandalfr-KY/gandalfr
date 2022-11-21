#ifndef IS_ISOMORPHIC
#define IS_ISOMORPHIC
#include "gandalfr/graph/adjacency_matrix.hpp"

// 多分あってるくらいの気持ちで...
// 同型判定
template<bool is_directed>
bool is_isomorphic(const unweighted_graph<is_directed> &graph1, const unweighted_graph<is_directed> &graph2){
    if(graph1.nodes() != graph2.nodes()) return false;
    if(graph1.edges() != graph2.edges()) return false;

    int N = graph1.nodes();
    std::vector<matrix<int>> adj({adjacency_matrix(graph1), adjacency_matrix(graph2)});

    std::vector<int> nodes_id(N);
    std::iota(nodes_id.begin(), nodes_id.end(), 0);
    do{
        bool ok = true;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
            if(adj[0][i][j] != adj[1][nodes_id[i]][nodes_id[j]]){
                ok = false;
                break;
            }
        }
        if(ok) return true;
    }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
    return false;
}

// 同型判定
template<class WEIGHT, bool is_directed>
bool is_isomorphic(const weighted_graph<WEIGHT, is_directed> &graph1, const weighted_graph<WEIGHT, is_directed> &graph2){
    if(graph1.nodes() != graph2.nodes()) return false;
    if(graph1.edges() != graph2.edges()) return false;

    int N = graph1.nodes();
    std::vector<matrix<WEIGHT>> adj({adjacency_matrix(graph1), adjacency_matrix(graph2)});

    std::vector<int> nodes_id(N);
    std::iota(nodes_id.begin(), nodes_id.end(), 0);
    do{
        bool ok = true;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
            if(adj[0][i][j] != adj[1][nodes_id[i]][nodes_id[j]]){
                ok = false;
                break;
            }
        }
        if(ok) return true;
    }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
    return false;
}

#endif