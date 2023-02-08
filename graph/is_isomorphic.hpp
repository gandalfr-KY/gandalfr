#ifndef IS_ISOMORPHIC
#define IS_ISOMORPHIC
#include "gandalfr/graph/adjacency_matrix.hpp"

// 多分あってるくらいの気持ちで...
// 同型判定
template<class GRAPH_TYPE>
bool is_isomorphic(const GRAPH_TYPE &graph1, const GRAPH_TYPE &graph2){
    if(graph1.nodes() != graph2.nodes()) return false;
    if(graph1.edges() != graph2.edges()) return false;

    int N = graph1.nodes();
    auto adj1(adjacency_matrix(graph1)), adj2(adjacency_matrix(graph2));

    std::vector<int> nodes_id(N);
    std::iota(nodes_id.begin(), nodes_id.end(), 0);
    do{
        bool ok = true;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) {
            if(adj1[i][j] != adj2[nodes_id[i]][nodes_id[j]]){
                ok = false;
                break;
            }
        }
        if(ok) return true;
    }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
    return false;
}

#endif