#ifndef STRONGLY_CONNECTED_COMPONENTS
#define STRONGLY_CONNECTED_COMPONENTS
#include "gandalfr/graph/reversed_graph.hpp"

/* 強連結成分分解
 * groups() := 同一連結成分をまとめた二次元配列を返す
 * group_id()[i] := ノード i が groups() のどのインデックスに格納されているか
 * O(N)
 * verify : https://atcoder.jp/contests/practice2/submissions/36388906
 */
template<typename GRAPH_TYPE>
class strongly_connected_components{
  private:
    std::vector<int> grp_id;
    std::vector<std::vector<int>> grps;
    GRAPH_TYPE S;

    void dfs1(const GRAPH_TYPE &G, int cu, std::vector<int> &ord, std::vector<bool> &used){
        if(used[cu]) return;
        used[cu] = true;
        for(auto &e : G[cu]) dfs1(G, e.to, ord, used);
        ord.push_back(cu);
    }

    void dfs2(const GRAPH_TYPE &G, int cu, int id){
        if(grp_id[cu] != -1) return;
        grp_id[cu] = id;
        for(auto &e : G[cu]) dfs2(G, e.to, id);
    }

  public:
    strongly_connected_components(const GRAPH_TYPE &G) : grp_id(G.nodes(), -1) {
        std::vector<bool> used(G.nodes(), false);
        std::vector<int> ord;
        GRAPH_TYPE R(reversed_graph(G));

        for(int i=0; i<G.nodes(); i++) dfs1(G, i, ord, used);
        std::reverse(ord.begin(), ord.end());

        int id = 0;
        for(int i : ord) if(grp_id[i] == -1){
            dfs2(R, i, id);
            id++;
        }

        grps.resize(id);
        for(int i=0; i<G.nodes(); i++) grps[grp_id[i]].push_back(i);

        S.resize(grps.size());
        for(auto e : G.edge_set()){
            e.from = group_id[e.from];
            e.to = group_id[e.to];
            if(e.from != e.to) S.add_edge(e);
        }

    }

    const std::vector<std::vector<int>> &groups(){ return grps; }
    const std::vector<int> &group_id(){ return grp_id; }
    const GRAPH_TYPE &simplified_graph(){ return S; };

};


#endif