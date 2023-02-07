#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include <queue>
#include "gandalfr/graph/graph.hpp"

namespace internal{
    template<bool is_directed>
    void bfs(const unweighted_graph<is_directed> &graph, std::vector<int> &dist, std::queue<int> &q){
        while(!q.empty()){
            int cu = q.front();
            q.pop();
            for(const unweighted_edge &e : graph[cu]){
                if(dist[e.to] != -1) continue;
                dist[e.to] = dist[cu] + 1;
                q.push(e.to);
            }
        }
    }

    template<typename WEIGHT, bool is_directed>
    void dijkstra(const weighted_graph<WEIGHT, is_directed> &graph, std::vector<WEIGHT> &dist, 
                  std::priority_queue<std::pair<WEIGHT, int>,
                                      std::vector<std::pair<WEIGHT, int>>,
                                      std::greater<std::pair<WEIGHT, int>>> &q){
        std::vector<bool> vis(graph.nodes(), false);
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
    }
}

/* 単一または複数のノードfromから全てのノードに対しての最短経路の長さを返す
 * 到達不能ならば、-1で返る
 * 重み無し : O(N)
 * 重み有り : O(NlogN)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7443620
 */
template<bool is_directed>
std::vector<int> shortest_path(const unweighted_graph<is_directed> &graph, int from){
    std::queue<int> q;
    std::vector<int> dist(graph.nodes(), -1);
    q.push(from);
    dist[from] = 0;
    internal::bfs(graph, dist, q);
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
    internal::bfs(graph, dist, q);
    return dist;
}


template<typename WEIGHT, bool is_directed>
std::vector<WEIGHT> shortest_path(const weighted_graph<WEIGHT, is_directed> &graph, int from){
    // first := current_distance, second := next
    using PAIR = std::pair<WEIGHT, int>;
    WEIGHT ma = std::numeric_limits<WEIGHT>::max();
    std::priority_queue<PAIR, std::vector<PAIR>, std::greater<PAIR>> q;
    std::vector<WEIGHT> dist(graph.nodes(), ma);
    q.push({0, from});
    dist[from] = 0;

    internal::dijkstra(graph, dist, q);
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
    for(int from : froms){
        q.push({0, from});
        dist[from] = 0;
    }

    internal::dijkstra(graph, dist, q);
    for(WEIGHT &x : dist) if(x == ma) x = -1; 
    return dist;
}

#endif