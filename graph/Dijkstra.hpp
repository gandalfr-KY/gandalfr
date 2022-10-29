#ifndef DIJKSTRA
#define DIJKSTRA
#include <queue>
#include "gandalfr/graph/graph.hpp"

template<typename WEIGHT>
std::vector<WEIGHT> Dijkstra(weighted_graph<WEIGHT> &graph, int from){
    // first = current_distance, second = next //
    std::priority_queue<std::pair<WEIGHT, int>, std::vector<std::pair<WEIGHT, int>>, std::greater<std::pair<WEIGHT, int>>> q;
    std::vector<WEIGHT> dist(graph.N, std::numeric_limits<WEIGHT>::max());
    q.push({0, from});
    dist[from] = 0;

    while(!q.empty()){
        WEIGHT cur_dist = q.top().first;
        int cu = q.top().second;
        q.pop();
        for(weighted_edge<WEIGHT> &e : graph.G[cu]){
            WEIGHT alt = cur_dist + e.cost;
            if(dist[e.to] <= alt) continue;
            q.push(std::pair<WEIGHT, int>{alt, e.to});
            dist[e.to] = alt;
        }
    }
    return dist;
}

template<typename WEIGHT>
std::vector<WEIGHT> Dijkstra(weighted_graph<WEIGHT> &graph, std::vector<int> froms){
    // first = current_distance, second = next //
    std::priority_queue<std::pair<WEIGHT, int>, std::vector<std::pair<WEIGHT, int>>, std::greater<std::pair<WEIGHT, int>>> q;
    std::vector<WEIGHT> dist(graph.N, std::numeric_limits<WEIGHT>::max());
    for(int from : froms){
        q.push({0, from});
        dist[from] = 0;
    }

    while(!q.empty()){
        WEIGHT cur_dist = q.top().first;
        int cu = q.top().second;
        q.pop();
        for(weighted_edge<WEIGHT> &e : graph.G[cu]){
            WEIGHT alt = cur_dist + e.cost;
            if(dist[e.to] <= alt) continue;
            q.push(std::pair<WEIGHT, int>{alt, e.to});
            dist[e.to] = alt;
        }
    }
    return dist;
}

#endif