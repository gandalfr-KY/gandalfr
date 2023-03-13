#ifndef STRONGLY_CONNECTED_COMPONENTS
#define STRONGLY_CONNECTED_COMPONENTS
#include "gandalfr/graph/reversed_graph.hpp"

/* 強連結成分分解
 * groups() := 同一連結成分をまとめた二次元配列を返す
 * group_id()[i] := ノード i が groups() のどのインデックスに格納されているか
 * simplified_graph() := 強連結成分を簡約したグラフを返す。ただし、自己ループ無し、多重辺あり
 * 前処理 O(N)
 * verify : https://atcoder.jp/contests/practice2/submissions/36388906
 */
template<typename WEIGHT>
class strongly_connected_components{
  private:
    std::vector<int> grp_id;
    std::vector<std::vector<int>> grps;
    internal::_base_graph<WEIGHT, true> S;

    void dfs1(const internal::_base_graph<WEIGHT, true> &G, int cu, std::vector<int> &ord, std::vector<bool> &used){
        if(used[cu]) return;
        used[cu] = true;
        for(const internal::_base_edge<WEIGHT> &e : G[cu]) dfs1(G, e.to, ord, used);
        ord.push_back(cu);
    }

    void dfs2(const internal::_base_graph<WEIGHT, true> &G, int cu, int id){
        if(grp_id[cu] != -1) return;
        grp_id[cu] = id;
        for(const internal::_base_edge<WEIGHT> &e : G[cu]) dfs2(G, e.to, id);
    }

  public:
    strongly_connected_components(const internal::_base_graph<WEIGHT, true> &G) : grp_id(G.nodes(), -1) {
        int N = G.nodes();
        std::vector<bool> used(N, false);
        std::vector<int> ord;
        internal::_base_graph<WEIGHT, true> R(reversed_graph(G));

        for(int i = 0; i < N; i++) {
            dfs1(G, i, ord, used);
        }

        int id = 0;
        for(int i = N - 1; i >= 0; i--) if(grp_id[ord[i]] == -1) {
            dfs2(R, ord[i], id);
            id++;
        }

        grps.resize(id);
        for(int i=0; i < N; i++) grps[grp_id[i]].push_back(i);

        S.expand(grps.size());
        for(internal::_base_edge<WEIGHT> e : G.edge_set()){
            e.from = grp_id[e.from];
            e.to = grp_id[e.to];
            if(e.from != e.to) S.add_edge(e);
        }
    }


    const std::vector<std::vector<int>> &groups(){ return grps; }
    const std::vector<int> &group_id(){ return grp_id; }
    const internal::_base_graph<WEIGHT, true> &simplified_graph(){ return S; };

};


#endif