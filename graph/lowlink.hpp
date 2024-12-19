#pragma once

#include "../standard/HashMap.hpp"
#include "dfs.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
void GRAPH_TYPE::lowlinkImpl(i32 cu, i32 e_id, i32 &id, std::vector<i32> &ord,
                             std::vector<i32> &low,
                             Graph<is_weighted, DIRECTED> &tree) const {
    ord[cu] = low[cu] = id++;
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (e->id == e_id) // 直前に使った辺を戻らない
            continue;
        if (ord[to] == -1) {
            tree.addEdge({cu, to, e->cost, e->id});
            lowlinkImpl(to, e->id, id, ord, low, tree);
            chmin(low[cu], low[to]);
        } else {
            chmin(low[cu], ord[to]);
        }
    }
}

GRAPH_TEMPLATE
std::tuple<std::vector<i32>, std::vector<i32>, Graph<is_weighted, DIRECTED>>
GRAPH_TYPE::lowlink() const {
    static_assert(!is_directed);
    std::vector<i32> ord(N, -1), low(N, i32MAX);
    Graph<is_weighted, DIRECTED> tree(N, N - 1);
    for (i32 i = 0; i < N; ++i) {
        if (ord[i] != -1) {
            continue;
        }
        i32 id = 0;
        lowlinkImpl(i, -1, id, ord, low, tree);
    }
    return {ord, low, tree};
}

GRAPH_TEMPLATE
std::vector<GRAPH_EDGE_TYPE> GRAPH_TYPE::bridges() const {
    static_assert(!is_directed);
    auto [ord, low, tree] = lowlink();
    std::vector<EdgeType> res;
    for (auto &e : tree.getAllEdges()) {
        if (ord[e->v0] < low[e->v1]) {
            res.push_back(*e);
        }
    }
    return res;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::articulationPoints() const {
    static_assert(!is_directed);
    auto [ord, low, tree] = lowlink();
    std::vector<i32> sep(N, 0);
    for (i32 src = 0; src < N; ++src) {
        if (ord[src] == 0) {
            sep[src] = tree[src].size() - 1;
        } else {
            sep[src] = std::count_if(
                tree[src].begin(), tree[src].end(),
                [&](const EdgePtr &e) { return ord[src] <= low[e->dst(src)]; });
        }
    }
    return sep;
}

GRAPH_TEMPLATE
std::vector<std::vector<i32>> GRAPH_TYPE::twoEdgeConnectedComponent() const {
    static_assert(!is_directed);
    auto tmp = this->bridges();
    std::unordered_set<i32> bridge_id_list;
    for (auto e : tmp)
        bridge_id_list.insert(e.id);

    i32 id = 0;
    std::vector<i32> group_id(N, -1);
    std::queue<i32> q;

    for (i32 i = 0; i < N; ++i) {
        if (group_id[i] != -1)
            continue;
        group_id[i] = id;
        q.push(i);
        while (!q.empty()) {
            i32 cur = q.front();
            q.pop();
            for (auto e : G[cur]) {
                i32 dst = e->dst(cur);
                if (bridge_id_list.contains(e->id) || group_id[dst] != -1)
                    continue;
                group_id[dst] = id;
                q.push(dst);
            }
        }
        ++id;
    }

    std::vector<std::vector<i32>> result(id);
    for (i32 i = 0; i < N; ++i) {
        result[group_id[i]].push_back(i);
    }
    return result;
}

GRAPH_TEMPLATE
std::vector<std::vector<GRAPH_EDGE_TYPE>>
GRAPH_TYPE::biconnectedComponent() const {
    static_assert(!is_directed);
    auto [ord, low, tree] = lowlink();

    // 参考：https://kntychance.hatenablog.jp/entry/2022/09/16/161858
    i32 idx = 0;
    std::queue<i32> sub_roots, nodes;
    std::vector<std::vector<GRAPH_EDGE_TYPE>> result;

    for (i32 i = 0; i < N; ++i) {
        if (ord[i] != 0)
            continue;
        for (auto e : tree[i]) {
            result.push_back(std::vector<GRAPH_EDGE_TYPE>{*e});
            sub_roots.push(e->v1);
        }

        while (!sub_roots.empty()) {
            i32 root = sub_roots.front();
            sub_roots.pop();

            nodes.push(root);
            while (!nodes.empty()) {
                i32 cur = nodes.front();
                nodes.pop();
                for (auto e : tree[cur]) {
                    if (low[e->v1] >= ord[cur]) {
                        result.push_back(std::vector<GRAPH_EDGE_TYPE>{*e});
                        sub_roots.push(e->v1);
                    } else {
                        result[idx].push_back(*e);
                        nodes.push(e->v1);
                    }
                }
            }
            ++idx;
        }
    }
    return result;
}

GRAPH_TEMPLATE
std::tuple<Graph<is_weighted, UNDIRECTED>, std::vector<i32>, std::vector<i32>>
GRAPH_TYPE::blockCutTree() const {
    // TODO: 現状lowlinkが2回走っているのでちゃんと実装する
    auto bicc = this->biconnectedComponent();

    // cut_id[i] == -1 なら関節点でない
    // |V|=1 のグラフの頂点は関節点でないとする
    auto cut_id = this->articulationPoints();
    i32 n_cut = 0;
    for (i32 i = 0; i < N; ++i) {
        if (cut_id[i] > 0) {
            cut_id[i] = n_cut++;
        } else {
            cut_id[i] = -1;
        }
    }

    // block_id[i] == -1 なら関節点
    std::vector<i32> block_id(N, -1);
    for (i32 i = 0; i < (i32)bicc.size(); ++i) {
        for (auto e : bicc[i]) {
            if (cut_id[e.v0] == -1) {
                block_id[e.v0] = i + n_cut;
            }
            if (cut_id[e.v1] == -1) {
                block_id[e.v1] = i + n_cut;
            }
        }
    }

    // |V|=1 のときの処理
    i32 single_id = bicc.size() + n_cut;
    for (i32 i = 0; i < N; ++i) {
        if (G[i].size() == 0) {
            block_id[i] = single_id++;
        }
    }

    i32 bct_size = single_id;
    Graph<false, false> BCT(bct_size); // 前半：関節点 後半：連結成分
    for (i32 i = 0; i < (i32)bicc.size(); ++i) {
        std::unordered_set<i32> nodes;
        for (auto e : bicc[i]) {
            nodes.insert(e.v0);
            nodes.insert(e.v1);
        }
        for (auto x : nodes) {
            if (cut_id[x] >= 0) {
                BCT.addEdge(cut_id[x], i + n_cut);
            }
        }
    }
    for (i32 i = 0; i < N; ++i) {
    }
    return {BCT, cut_id, block_id};
}

} // namespace gandalfr