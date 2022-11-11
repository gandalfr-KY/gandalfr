#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include <queue>
#include "gandalfr/graph/graph.hpp"

/* 単一または複数のノードfromから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 * 重み無し : O(N)
 * 重み有り : O(NlogN)
 * verify : https://onlinejudge.u-aizu.ac.jp/status/users/Gandalfr/submissions/1/GRL_1_A/judge/7093571/C++14
 */
template<bool is_directed>
std::vector<int> shortest_path(const unweighted_graph<is_directed> &graph, int from){
    std::queue<int> q;
    std::vector<int> dist(graph.nodes(), -1);
    q.push(from);
    dist[from] = 0;
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(unweighted_edge &e : graph[cu]){
            if(dist[e.to] != -1) continue;
            dist[e.to] = dist[cu] + 1;
            q.push(e.to);
        }
    }
    return dist;
}

template<bool is_directed>
std::vector<int> shortest_path(const unweighted_graph<is_directed> &graph, const std::vector<int> &froms){
    std::queue<int> q;
    std::vector<int> dist(graph.nodes(), -1);
    for(int from : froms){
        q.push(from);
        dist[from] = 0;
    }
    while(!q.empty()){
        int cu = q.front();
        q.pop();
        for(unweighted_edge &e : graph[cu]){
            if(dist[e.to] != -1) continue;
            dist[e.to] = dist[cu] + 1;
            q.push(e.to);
        }
    }
    return dist;
}


template<typename WEIGHT, bool is_directed>
std::vector<WEIGHT> shortest_path(const weighted_graph<WEIGHT, is_directed> &graph, int from){
    // first := current_distance, second := next
    using PAIR = std::pair<WEIGHT, int>;
    WEIGHT ma = std::numeric_limits<WEIGHT>::max();
    std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>> q;
    std::vector<WEIGHT> dist(graph.nodes(), ma);
    std::vector<bool> vis(graph.nodes(), false);

    q.push({0, from});
    dist[from] = 0;

    while(!q.empty()){
        WEIGHT cur_dist = q.top().first;
        int cu = q.top().second;
        q.pop();

        if(vis[cu]) continue;
        vis[cu] = true;

        for(const weighted_edge<WEIGHT> &e : graph[cu]){
            WEIGHT alt = cur_dist + e.cost;
            if(dist[e.to] <= alt) continue;
            dist[e.to] = alt;
            q.push({alt, e.to});
        }
    }

    for(WEIGHT &x : dist) if(x == ma) x = -1; 
    return dist;
}

template<typename WEIGHT, bool is_directed>
std::vector<WEIGHT> shortest_path(const weighted_graph<WEIGHT, is_directed> &graph, const std::vector<int> &froms){
    // first := current_distance, second := next
    using PAIR = std::pair<WEIGHT, int>;
    WEIGHT ma = std::numeric_limits<WEIGHT>::max();
    std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>> q;
    std::vector<WEIGHT> dist(graph.nodes(), ma);
    std::vector<bool> vis(graph.nodes(), false);
    for(int from : froms){
        q.push({0, from});
        dist[from] = 0;
    }

    while(!q.empty()){
        WEIGHT cur_dist = q.top().first;
        int cu = q.top().second;
        q.pop();

        if(vis[cu]) continue;
        vis[cu] = true;

        for(const weighted_edge<WEIGHT> &e : graph[cu]){
            WEIGHT alt = cur_dist + e.cost;
            if(dist[e.to] <= alt) continue;
            dist[e.to] = alt;
            q.push({alt, e.to});
        }
    }
    
    for(WEIGHT &x : dist) if(x == ma) x = -1; 
    return dist;
}

#endif