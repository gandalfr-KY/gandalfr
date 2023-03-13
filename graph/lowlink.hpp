#ifndef LOWLINK
#define LOWLINK
#include "gandalfr/graph/topological_sort.hpp"

/* 単純連結無向グラフの関節点・橋を求める
 * 前処理 O(N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093344
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7093485
 */
template<typename WEIGHT>
class lowlink{
  private:
    std::vector<int> ord, low, apts;
    std::vector<internal::_base_edge<WEIGHT>> brids;
    
    void dfs(const internal::_base_graph<WEIGHT, false> &G, int cu, int pa, int &cnt){
        ord[cu] = low[cu] = cnt++;
        bool is_apt = false;
        for(const internal::_base_edge<WEIGHT> &e : G[cu]){
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
    lowlink(const internal::_base_graph<WEIGHT, false> &G) : ord(G.nodes(), -1), low(G.nodes(), -1) {
        int cnt = 0, root, min_deg = std::numeric_limits<int>::max();
        // 次数が最小のノードは必ず関節点でない
        // そこからDFSすれば、根ノードの関節点判定を行わなくてよい
        std::vector<int> indeg(internal::count_indegree(G));
        dfs(G, min_element(indeg.begin(), indeg.end()) - indeg.begin(), -1, cnt);
    }

    // unsorted であることに注意
    const std::vector<int> &articulation_points(){ return apts; }
    const std::vector<internal::_base_edge<WEIGHT>> &bridges(){ return brids; }

};


#endif