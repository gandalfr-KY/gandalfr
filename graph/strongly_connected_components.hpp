#ifndef STRONGLY_CONNECTED_COMPONENTS
#define STRONGLY_CONNECTED_COMPONENTS
#include "gandalfr/graph/reversed_graph.hpp"

template<typename GRAPH>
void _dfs_for_scc(GRAPH &graph, int cu, std::vector<int> &ord, std::vector<int> &used){
    if(used[cu]) return;
    used[cu] = true;
    for(auto &e : graph.G[cu]) _dfs_for_scc(graph, e.to, ord, used);
    ord.emplace_back(cu);
}

template<typename GRAPH>
void _rdfs_for_scc(GRAPH &graph, int cu, int id, std::vector<int> &group_id){
    if(group_id[cu] != -1) return;
    group_id[cu] = id;
    for(auto &e : graph.G[cu]) _rdfs_for_scc(graph, e.to, id, group_id);
}

template<typename GRAPH>
std::vector<std::vector<int>> strongly_conected_components(GRAPH &graph){
    GRAPH rev = reversed_graph(graph);
    std::vector<int> group_id(graph.N, -1), ord, used(graph.N, false);

    for(int i=0; i<graph.N; i++) _dfs_for_scc(graph, i, ord, used);
    std::reverse(ord.begin(), ord.end());

    int id = 0;
    for(int i : ord) if(group_id[i] == -1) _rdfs_for_scc(rev, i, id, group_id), id++;

    std::vector<std::vector<int>> ret(id);
    for(int i=0; i<graph.N; i++) ret[group_id[i]].push_back(i);
    return ret;
}

#endif