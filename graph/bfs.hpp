#ifndef BFS
#define BFS
#include <queue>
#include "gandalfr/graph/graph.hpp"

std::vector<int> bfs(unweighted_graph &graph, int from){
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

std::vector<int> bfs(unweighted_graph &graph, std::vector<int> &froms){
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

#endif