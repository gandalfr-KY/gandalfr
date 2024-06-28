#pragma once

#include "../standard/HashMap.hpp"
#include "Lca.hpp"
#include <stack>

namespace gandalfr {

GRAPH_TEMPLATE
std::tuple<std::vector<Graph<WEIGHTED, UNDIRECTED>>,
           std::vector<std::vector<i32>>>
GRAPH_TYPE::auxiliaryTree(i32 root, const std::vector<i32> &gr_id) const {
    static_assert(!is_directed);
    i32 num_group = *max_element(gr_id.begin(), gr_id.end()) + 1;
    Lca lca(*this, root);
    std::vector<Graph<WEIGHTED, UNDIRECTED>> Aux(num_group);
    std::vector<std::vector<i32>> components(num_group), lcas(num_group),
        rev_id(num_group);
    std::vector<HashMap<i32, i32>> nd_id_map(num_group);

    for (i32 gr = 0; gr < num_group; ++gr) {
        nd_id_map[gr][root] = 0;
        rev_id[gr].push_back(root);
    }
    for (auto x : preorder(root)) {
        i32 gr = gr_id[x];
        if (gr < 0)
            continue;
        components[gr].push_back(x);
        i32 l = components[gr].size();
        i32 anc = lca.getAncestor(components[gr][l - 2], components[gr][l - 1]);
        lcas[gr].push_back(anc);
        if (nd_id_map[gr].find(x) == nd_id_map[gr].end()) {
            nd_id_map[gr][x] = nd_id_map[gr].size();
            rev_id[gr].push_back(x);
        }
        if (nd_id_map[gr].find(anc) == nd_id_map[gr].end()) {
            nd_id_map[gr][anc] = nd_id_map[gr].size();
            rev_id[gr].push_back(anc);
        }
    }

    for (i32 gr = 0; gr < num_group; ++gr) {
        Aux[gr].resize(nd_id_map[gr].size());
        Aux[gr].reserve(nd_id_map[gr].size() - 1);
        std::stack<i32> stk;
        stk.push(root);
        for (u32 i = 0; i < components[gr].size(); ++i) {
            i32 w = lca.getAncestor(stk.top(), components[gr][i]);
            if (w != stk.top()) {
                while (lca.getDepth(w) <= lca.getDepth(stk.top())) {
                    i32 p = stk.top();
                    stk.pop();
                    if (stk.empty())
                        break;
                    i32 pp = stk.top();
                    if (lca.getDepth(w) <= lca.getDepth(pp) && pp != p) {
                        Aux[gr].addEdge(nd_id_map[gr][pp], nd_id_map[gr][p],
                                        lca.distance(pp, p));
                    } else if (w != p) {
                        Aux[gr].addEdge(nd_id_map[gr][w], nd_id_map[gr][p],
                                        lca.distance(w, p));
                    }
                }
                stk.push(w);
            }
            stk.push(components[gr][i]);
        }
        while (!stk.empty()) {
            i32 p = stk.top();
            stk.pop();
            if (!stk.empty() && stk.top() != p) {
                Aux[gr].addEdge(nd_id_map[gr][stk.top()], nd_id_map[gr][p],
                                lca.distance(stk.top(), p));
            }
        }
    }
    return {Aux, rev_id};
}
} // namespace gandalfr
