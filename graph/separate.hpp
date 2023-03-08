#ifndef SEPARATE
#define SEPARATE
#include "gandalfr/graph/graph.hpp"

// グラフを連結成分ごとにvectorに入れて返す
template<typename GRAPH_TYPE>
std::vector<GRAPH_TYPE> separate(GRAPH_TYPE &graph){
    std::vector<std::vector<int>> groups(graph.connected_groups());
	std::vector<std::pair<int, int>> group_and_node_id(graph.nodes());
	std::vector<GRAPH_TYPE> graphs(groups.size());
	for(int i = 0; i < groups.size(); i++){
		graphs[i].expand(groups[i].size());
		for(int j = 0; j < groups[i].size(); j++){
			group_and_node_id[groups[i][j]] = {i, j};
		}
	}

	for(auto e : graph.edge_set()){
		int group_id = group_and_node_id[e.from].first;
		e.from = group_and_node_id[e.from].second;
		e.to = group_and_node_id[e.to].second;
		graphs[group_id].add_edge(e);
	}
	return graphs;
}

#endif