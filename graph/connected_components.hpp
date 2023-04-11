#ifndef CONNECTED_COMPONENTS
#define CONNECTED_COMPONENTS
#include "gandalfr/graph/graph.hpp"

// グラフを連結成分ごとにvectorに入れて返す
template<typename WEIGHT, bool is_directed>
class connected_components{
  private:
    std::vector<std::vector<int>> groups;
    std::vector<std::pair<int, int>> group_and_node_id;
    std::vector<internal::_base_graph<WEIGHT, is_directed>> Gs;

  public:
    connected_components(internal::_base_graph<WEIGHT, is_directed> &G)
         : groups(G.connected_groups()), group_and_node_id(G.nodes()), Gs(G.count_connected_components()) {
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
    }
    
    std::vector<internal::_base_graph<WEIGHT, is_directed>> &get_decomposed_graphs(){ return Gs; }
    // {<グループ番号, ノード番号>}
    const std::vector<std::pair<int, int>> get_mapping_table(){ return group_and_node_id; } 

};

#endif