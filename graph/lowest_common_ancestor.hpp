#ifndef LOWEST_COMMON_ANCESTOR
#define LOWEST_COMMON_ANCESTOR
#include "gandalfr/graph/shortest_path.hpp"
#include "gandalfr/data_structure/sparse_table.hpp"

/* 無向単純木の最小共通祖先を求める
 * 構築   O(NlogN)
 * 値取得 O(1)
 * verify : https://atcoder.jp/contests/abc070/submissions/36387992
 */
template<typename WEIGHT>
class lowest_common_ancestor{
  private:
    using PAIR = std::pair<int, int>;
    
    std::vector<int> idx;
    std::vector<PAIR> depth;
    sparse_table<PAIR> sps;
    std::vector<WEIGHT> dist;

    void Euler_tour(const internal::_base_graph<WEIGHT, false> &G, int cu, int pa, int dep, int &cnt){
        idx[cu] = cnt;

        for(auto &e : G[cu]){
            if(e.to == pa) continue;
            
            depth.push_back({dep, cu});
            cnt++;

            Euler_tour(G, e.to, cu, dep + 1, cnt);
        }

        depth.push_back({dep, cu});
        cnt++;
    }
    
  public:
    lowest_common_ancestor(const internal::_base_graph<WEIGHT, false> &G) : 
    idx(G.nodes()), sps([](PAIR a, PAIR b){ return std::min(a, b); }), dist(shortest_path(G, 0)){
        int cnt = 0;
        Euler_tour(G, 0, -1, 0, cnt);
        sps.init(depth);
    }

    int get_ancestor(int a, int b){
        int idxl = idx[a], idxr = idx[b];
        if(idxl > idxr) std::swap(idxl, idxr);
        return sps.get(idxl, idxr + 1).second;
    }

    WEIGHT distance(int u, int v){
        return dist[u] + dist[v] - 2 * dist[get_ancestor(u, v)];
    }

};

#endif