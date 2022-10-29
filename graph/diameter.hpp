#ifndef DIAMETER
#define DIAMETER
#include "gandalfr/graph/bfs.hpp"
#include "gandalfr/graph/Dijkstra.hpp"

int diameter(unweighted_graph &graph){
    assert(!graph.is_directed);
    std::vector<int> dist = bfs(graph, 0);
    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = bfs(graph, farthest_node);
    return *std::max_element(dist.begin(), dist.end());
}

template<typename WEIGHT>
WEIGHT diameter(weighted_graph<WEIGHT> &graph){
    assert(!graph.is_directed);
    std::vector<WEIGHT> dist = Dijkstra(graph, 0);
    for(WEIGHT &x : dist) if(x == std::numeric_limits<WEIGHT>::max()) x = 0;
    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = Dijkstra(graph, farthest_node);
    for(WEIGHT &x : dist) if(x == std::numeric_limits<WEIGHT>::max()) x = 0;
    return *std::max_element(dist.begin(), dist.end());
}

#endif