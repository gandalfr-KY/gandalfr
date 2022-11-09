#ifndef DIAMETER
#define DIAMETER
#include "gandalfr/graph/shortest_path.hpp" 

int diameter(unweighted_graph &graph){
    assert(!graph.is_directed && graph.M == graph.N - 1);
    std::vector<int> dist = shortest_path(graph, 0);
    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = shortest_path(graph, farthest_node);
    return *std::max_element(dist.begin(), dist.end());
}

template<typename WEIGHT>
WEIGHT diameter(weighted_graph<WEIGHT> &graph){
    assert(!graph.is_directed && graph.M == graph.N - 1);
    std::vector<WEIGHT> dist = shortest_path(graph, 0);
    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = shortest_path(graph, farthest_node);
    return *std::max_element(dist.begin(), dist.end());
}

#endif