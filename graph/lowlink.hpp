#ifndef LOWLINK
#define LOWLINK
#include <utility>
#include "graph.hpp"

/* 単純無向グラフの関節点・橋を求める
 * 前処理 O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093344
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093485
 */
template<typename WEIGHT>
class lowlink{
  private:
    std::vector<int> ord, low, apts;
    std::vector<edge<WEIGHT>> brids;
    
    void dfs(const graph<WEIGHT, false> &G, int cu, int pa, int &cnt){
        ord[cu] = low[cu] = cnt++;
        bool is_apt = false;
        for(auto &e : G[cu]){
            if(e.to == pa) continue;
            if(ord[e.to] == -1){
                dfs(G, e.to, cu, cnt);
                if(low[cu] > low[e.to]) low[cu] = low[e.to];
                if(ord[cu] < low[e.to]) brids.emplace_back(e);
                if(pa != -1 && ord[cu] <= low[e.to]) is_apt = true;
            }
            else if(low[cu] > ord[e.to]) low[cu] = ord[e.to];
        }
        if(is_apt) apts.emplace_back(cu); 
    }

  public:
    lowlink(graph<WEIGHT, false> &G) : ord(G.count_nodes(), -1), low(G.count_nodes(), -1) {
        // 次数が最小のノードは必ず関節点でない
        // そこからDFSすれば、根ノードの関節点判定を行わなくてよい
        std::vector<int> deg(G.count_nodes(), 0);
        for(int i = 0; i < G.count_nodes(); i++) deg[i] = G[i].size(); 
        
        const std::vector<std::vector<int>> groups = G.connected_components();
        int sz = groups.size();
        std::vector<std::pair<int, int>> group_min_deg(sz, {std::numeric_limits<int>::max(), -1});
        for(int i = 0; i < sz; i++) for(int x : groups[i]) if(group_min_deg[i].first > deg[x]){
            group_min_deg[i] = {deg[x], x};
        }

        for(auto[ign, x] : group_min_deg){
            int cnt = 0;
            dfs(G, x, -1, cnt);
        }
    }

    // unsorted であることに注意
    const std::vector<int> &articulation_points(){ return apts; }
    const std::vector<edge<WEIGHT>> &bridges(){ return brids; }

};


#endif