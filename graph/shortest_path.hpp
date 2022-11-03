#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include <queue>
#include "gandalfr/graph/graph.hpp"

/* ノードfromから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 */
std::vector<int> shortest_path(unweighted_graph &graph, int from){
    std::queue<int> q;
    std::vector<int> dist(graph.N, -1);
    q.push(from);
    dist[from] = 0;
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(unweighted_edge &e : graph.G[cu]){
            if(dist[e.to] != -1) continue;
            dist[e.to] = dist[cu] + 1;
            q.push(e.to);
        }
    }
    return dist;
}

/* 複数のノードfromsから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 */
std::vector<int> shortest_path(unweighted_graph &graph, std::vector<int> &froms){
    std::queue<int> q;
    std::vector<int> dist(graph.N, -1);
    for(int from : froms){
        q.push(from);
        dist[from] = 0;
    }
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(unweighted_edge &e : graph.G[cu]){
            if(dist[e.to] != -1) continue;
            dist[e.to] = dist[cu] + 1;
            q.push(e.to);
        }
    }
    return dist;
}

/* ノードfromから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 */
template<typename WEIGHT>
std::vector<WEIGHT> shortest_path(weighted_graph<WEIGHT> &graph, int from){
    // first := current_distance, second := next
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

    for(auto &x : dist) if(x ==  std::numeric_limits<WEIGHT>::max()) x = -1; 
    return dist;
}

/* 複数のノードfromsから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 */
template<typename WEIGHT>
std::vector<WEIGHT> shortest_path(weighted_graph<WEIGHT> &graph, std::vector<int> froms){
    // first := current_distance, second := next
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
    
    for(auto &x : dist) if(x ==  std::numeric_limits<WEIGHT>::max()) x = -1; 
    return dist;
}

#endif