#ifndef DIAMETER
#define DIAMETER
#include "gandalfr/graph/shortest_path.hpp" 

/* 木の直径
 * 重み無し : O(N)
 * 重み有り : O(NlogN)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093593
 */
template<typename GRAPH_TYPE>
int diameter(const GRAPH_TYPE &graph){
    auto dist = shortest_path(graph, 0);
    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = shortest_path(graph, farthest_node);
    return *std::max_element(dist.begin(), dist.end());
}

#endif