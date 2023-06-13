#ifndef IS_ISOMORPHIC
#define IS_ISOMORPHIC
#include <numeric>
#include "graph.hpp"
#include "../math/matrix.hpp"

// 多分あってるくらいの気持ちで...
// 同型判定
template<typename WEIGHT, bool is_directed>
bool is_isomorphic(const graph<WEIGHT, is_directed> &G1, const graph<WEIGHT, is_directed> &G2){
    if(G1.count_nodes() != G2.count_nodes()) return false;
    if(G1.count_nodes() != G2.count_nodes()) return false;

    int N = G1.count_nodes();
    matrix<WEIGHT> adj1(G1.to_adjajency()), adj2(G2.to_adjajency());

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