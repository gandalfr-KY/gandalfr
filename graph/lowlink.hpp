#ifndef LOWLINK
#define LOWLINK
#include "gandalfr/graph/graph.hpp"

/* 単純連結無向グラフの関節点・橋を求める
 * 前処理 O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093344
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093485
 */
template<typename EDGE_TYPE, typename GRAPH_TYPE>
class lowlink{
  private:
    std::vector<int> ord, low, apts;
    std::vector<EDGE_TYPE> brids;
    
    void dfs(const GRAPH_TYPE &G, int cu, int pa, int &cnt){
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
    lowlink(const GRAPH_TYPE &G) : ord(G.nodes(), -1), low(G.nodes(), -1) {
        int cnt = 0, root, min_deg = std::numeric_limits<int>::max();
        // 次数が最小のノードは必ず関節点でない
        // そこからDFSすれば、根ノードの関節点判定を行わなくてよい
        for(int i = 0; i < G.nodes(); i++){
            if(min_deg > G[i].size()){
                min_deg = G[i].size();
                root = i;
            }
        }
        dfs(G, root, -1, cnt);
    }

    // unsorted であることに注意
    const std::vector<int> &articulation_points(){ return apts; }
    const std::vector<EDGE_TYPE> &bridges(){ return brids; }

};


#endif