#ifndef IS_ISOMORPHIC
#define IS_ISOMORPHIC
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

// 多分あってるくらいの気持ちで...
// 同型判定
template<typename WEIGHT, bool is_directed>
bool is_isomorphic(const internal::_base_graph<WEIGHT, is_directed> &G1, const internal::_base_graph<WEIGHT, is_directed> &G2){
    if(G1.nodes() != G2.nodes()) return false;
    if(G1.edges() != G2.edges()) return false;

    int N = G1.nodes();
    WEIGHT MIN = std::numeric_limits<WEIGHT>::min();
    matrix<WEIGHT> adj1(G1, MIN), adj2(G2, MIN);

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