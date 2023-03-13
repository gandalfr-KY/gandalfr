#ifndef SEPARATE
#define SEPARATE
#include "gandalfr/graph/graph.hpp"

// グラフを連結成分ごとにvectorに入れて返す
template<typename WEIGHT, bool is_directed>
std::vector<internal::_base_graph<WEIGHT, is_directed>> separate(const internal::_base_graph<WEIGHT, is_directed> &G){
    std::vector<std::vector<int>> groups(G.connected_groups());
	std::vector<std::pair<int, int>> group_and_node_id(G.nodes());
	std::vector<internal::_base_graph<WEIGHT, is_directed>> Gs(G.size());
	for(int i = 0; i < groups.size(); i++){
		Gs[i].expand(groups[i].size());
		for(int j = 0; j < groups[i].size(); j++){
			group_and_node_id[groups[i][j]] = {i, j};
		}
	}

	for(internal::_base_edge<WEIGHT> e : G.edge_set()){
		int group_id = group_and_node_id[e.from].first;
		e.from = group_and_node_id[e.from].second;
		e.to = group_and_node_id[e.to].second;
		Gs[group_id].add_edge(e);
	}
	return Gs;
}

#endif