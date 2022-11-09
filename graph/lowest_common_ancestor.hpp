#ifndef LOWEST_COMMON_ANCESTOR
#define LOWEST_COMMON_ANCESTOR
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/data_structure/segment_tree.hpp"

template<class GRAPH>
class lowest_common_ancestor{
  private:
    using PAIR = std::pair<int, int>;
    
    GRAPH graph;
    std::vector<int> idx;
    segment_tree<PAIR> seg;

    void Euler_tour(int cu, int pa, int dep, int &cnt){
        idx[cu] = cnt;

        for(const unweighted_edge &e : graph[cu]){
            if(e.to == pa) continue;
            
            seg.update(cnt, {dep, cu});
            cnt++;

            Euler_tour(e.to, cu, dep + 1, cnt);
        }

        seg.update(cnt, {dep, cu});
        cnt++;
    }
    
  public:
    lowest_common_ancestor(const GRAPH &G, int root_node = 0) :
        graph(G),
        idx(G.N),
        seg(G.N * 2,
            [](const PAIR &a, const PAIR &b){ return std::min(a, b); },
            {std::numeric_limits<int>::max(), -1})
        {
            int cnt = 0;
            Euler_tour(root_node, -1, 0, cnt);
        }

    int get_ancestor(int a, int b){
        int idxl = idx[a], idxr = idx[b];
        if(idxl > idxr) std::swap(idxl, idxr);
        return seg.get(idxl, idxr + 1).second;
    }

};













template<class WEIGHT>
class lowest_common_ancestor<weighted_graph<WEIGHT>>{
  private:
    weighted_graph<WEIGHT> graph;
    std::vector<int> order;
    int root;

    void Euler_tour(int cu, int pa, int cnt){
        order[cu] = cnt;
        for(const unweighted_edge &e : graph[cu]){
            if(e.to == pa) continue;
            Euler_tour(e.to, cu, cnt + 1, 0);
        }
    }
    
  public:
    lowest_common_ancestor(const weighted_graph<WEIGHT> &G, int root_node = 0) : graph(G), order(G.N), root(root_node) {
        int tmp = 0;
        Euler_tour(root, -1, tmp);
    }
};




#endif