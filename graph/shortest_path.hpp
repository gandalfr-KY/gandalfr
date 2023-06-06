#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include <queue>
#include "gandalfr/graph/graph.hpp"

namespace internal{
    template<bool is_directed>
    void bfs(const graph<int, is_directed> &G, std::vector<int> &dist, std::queue<int> &q){
        while(!q.empty()){
            int cu = q.front();
            q.pop();
            for(auto &e : G[cu]){
                if(dist[e.to] != -1) continue;
                dist[e.to] = dist[cu] + 1;
                q.push(e.to);
            }
        }
    }

    template<typename WEIGHT, bool is_directed>
    void dijkstra(const graph<WEIGHT, is_directed> &G, std::vector<WEIGHT> &dist, 
        std::priority_queue<std::pair<WEIGHT, int>,
        std::vector<std::pair<WEIGHT, int>>, 
        std::greater<std::pair<WEIGHT, int>>> &q){

        std::vector<bool> vis(G.num_nodes(), false);
        while(!q.empty()){
            WEIGHT cur_dist = q.top().first;
            int cu = q.top().second;
            q.pop();

            if(vis[cu]) continue;
            vis[cu] = true;

            for(auto &e : G[cu]){
                WEIGHT alt = cur_dist + e.cost;
                if(dist[e.to] <= alt) continue;
                dist[e.to] = alt;
                q.push({alt, e.to});
            }
        }
    }
}

/* 単一または複数のノードfromから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 * 重み無し : O(N)
 * 重み有り : O(NlogN)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7443620
 */
template<bool is_directed>
std::vector<int> shortest_path(const graph<int, is_directed> &G, int start_point){
    std::queue<int> q;
    std::vector<int> dist(G.nodes(), -1);
    q.push(start_point);
    dist[start_point] = 0;
    internal::bfs(G, dist, q);
    return dist;
}

template<bool is_directed>
std::vector<int> shortest_path(const graph<int, is_directed> &G, const std::vector<int> &start_points){
    std::queue<int> q;
    std::vector<int> dist(G.nodes(), -1);
    for(int start_point : start_points){
        q.push(start_point);
        dist[start_point] = 0;
    }
    internal::bfs(G, dist, q);
    return dist;
}


template<typename WEIGHT, bool is_directed>
std::vector<WEIGHT> shortest_path(const graph<WEIGHT, is_directed> &G, int start_point){
    // first := current_distance, second := next
    using PAIR = std::pair<WEIGHT, int>;
    WEIGHT ma = std::numeric_limits<WEIGHT>::max();
    std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>> q;
    std::vector<WEIGHT> dist(G.nodes(), ma);
    q.push({0, start_point});
    dist[start_point] = 0;

    internal::dijkstra(G, dist, q);
    for(WEIGHT &x : dist) if(x == ma) x = -1; 
    return dist;
}

template<typename WEIGHT, bool is_directed>
std::vector<WEIGHT> shortest_path(const graph<WEIGHT, is_directed> &G, const std::vector<int> &start_points){
    // first := current_distance, second := next
    using PAIR = std::pair<WEIGHT, int>;
    WEIGHT ma = std::numeric_limits<WEIGHT>::max();
    std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>> q;
    std::vector<WEIGHT> dist(G.nodes(), ma);
    for(int start_point : start_points){
        q.push({0, start_point});
        dist[start_point] = 0;
    }

    internal::dijkstra(G, dist, q);
    for(WEIGHT &x : dist) if(x == ma) x = -1; 
    return dist;
}

#endif