#ifndef SEPARATE
#define SEPARATE
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/data_structure/union_find.hpp"

// グラフを連結成分ごとにvectorに入れて返す
template<typename GRAPH>
std::vector<GRAPH> separate(GRAPH &graph){
    union_find uf(graph.N);
    for(auto&e : graph.E) uf.merge(e.from, e.to);

    std::vector<std::vector<int>> groups = uf.groups();
    int graph_num = groups.size();
    std::vector<int> nodes_group_id(graph.N);
    std::vector<int> nodes_compressed_id(graph.N);
    std::vector<GRAPH> graphs(graph_num, GRAPH(0, graph.is_directed));

    for(int i=0; i<graph_num; i++) for(int x : groups[i]){
        nodes_group_id[x] = i;
        nodes_compressed_id[x] = std::lower_bound(groups[i].begin(), groups[i].end(), x) - groups[i].begin();
    }
    for(int i=0; i<graph_num; i++) graphs[i].resize(groups[i].size());
    for(auto &e : graph.E) graphs[nodes_group_id[e.from]].add_edge(nodes_compressed_id[e.from], nodes_compressed_id[e.to], e.cost);
    return graphs;
}

#endif