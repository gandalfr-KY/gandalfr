#ifndef BRIDGES_AND_ARTICULATION_POINTS
#define BRIDGES_AND_ARTICULATION_POINTS
#include "gandalfr/standard/chmaxmin.hpp"
#include "gandalfr/graph/graph.hpp"

template<typename GRAPH, typename EDGE>
void bridges_and_articulation_points(GRAPH &graph, std::vector<int> &V, std::vector<EDGE> &E){
    assert(!graph.is_directed);
    std::vector<int> ord(graph.N, -1), low(graph.N, -1);
    int cnt = 0;
    int root = 0, minsiz = std::numeric_limits<int>::max();
    for(int i=0; i<graph.N; i++) if(chmin(minsiz, graph.G[i].size())) root = i;
    _lowlink(graph, V, E, root, -1, cnt, ord, low);
}

template<typename GRAPH, typename EDGE>
void _lowlink(GRAPH &graph, std::vector<int> &V, std::vector<EDGE> &E, int cu, int pa, int &cnt, std::vector<int> &ord, std::vector<int> &low){
    ord[cu] = low[cu] = cnt++;
    bool is_apt = false;
    for(auto &e : graph.G[cu]){
        if(e.to == pa) continue;
        if(ord[e.to] == -1){
            _lowlink(graph, V, E, e.to, cu, cnt, ord, low);
            chmin(low[cu], low[e.to]);
            if(ord[cu] < low[e.to]) E.emplace_back(e);
            if(pa != -1 && ord[cu] <= low[e.to]) is_apt = true;
        }
        else chmin(low[cu], ord[e.to]);
    }
    if(is_apt) V.emplace_back(cu); 
}

#endif