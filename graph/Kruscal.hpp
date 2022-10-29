#ifndef KRUSCAL
#define KRUSCAL
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/data_structure/union_find.hpp"

template<typename WEIGHT>
weighted_graph<WEIGHT> Kruscal(weighted_graph<WEIGHT> &graph){
    union_find uf(graph.N);
    weighted_graph<WEIGHT> ret(graph.N);
    std::vector<weighted_edge<WEIGHT>> E = graph.E;
    std::sort(E.begin(), E.end());
    for(weighted_edge<WEIGHT> &e : E){
        if(!uf.same(e.from, e.to)){
            uf.merge(e.from, e.to);
            ret.add_edge(e.from, e.to, e.cost);
        }
    }
    return ret;
}

#endif