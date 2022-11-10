#ifndef LOWEST_COMMON_ANCESTOR
#define LOWEST_COMMON_ANCESTOR
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/data_structure/sparse_table.hpp"

/* 最小共通祖先を求める
 * 構築   O(NlogN)
 * 値取得 O(1)
 */
template<typename GRAPH>
class lowest_common_ancestor{
  private:
    using PAIR = std::pair<int, int>;
    
    GRAPH graph;
    std::vector<int> idx;
    std::vector<PAIR> depth;
    sparse_table<PAIR> sps;

    void Euler_tour(int cu, int pa, int dep, int &cnt){
        idx[cu] = cnt;

        for(const unweighted_edge &e : graph[cu]){
            if(e.to == pa) continue;
            
            depth.push_back({dep, cu});
            cnt++;

            Euler_tour(e.to, cu, dep + 1, cnt);
        }

        depth.push_back({dep, cu});
        cnt++;
    }
    
  public:
    lowest_common_ancestor(const GRAPH &G, int root_node = 0) : 
    graph(G), idx(G.N), sps([](const PAIR &a, const PAIR &b){ return std::min(a, b); })
    {
        int cnt = 0;
        Euler_tour(root_node, -1, 0, cnt);
        sps.init(depth);
    }

    int get_ancestor(int a, int b){
        int idxl = idx[a], idxr = idx[b];
        if(idxl > idxr) std::swap(idxl, idxr);
        return sps.get(idxl, idxr + 1).second;
    }

};

#endif