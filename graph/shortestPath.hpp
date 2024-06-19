#pragma once

#include "Graph.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
std::vector<GRAPH_EDGE_PTR> GRAPH_TYPE::dijkstraImpl(std::vector<Cost> &dist,
                                                     i32 start_node) const {
    using Pair = std::pair<Cost, i32>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
    q.push({0, start_node});
    std::vector<EdgePtr> prev_edge(N, nullptr);
    std::vector<bool> visited(N, false);
    while (!q.empty()) {
        Cost cur_dist = q.top().first;
        i32 cu = q.top().second;
        q.pop();

        if (visited[cu])
            continue;
        visited[cu] = true;

        for (auto &e : G[cu]) {
            i32 to = e->dst(cu);
            Cost alt = cur_dist + e->cost;
            if (dist[to] <= alt)
                continue;
            prev_edge[to] = e;
            dist[to] = alt;
            q.push({alt, to});
        }
    }
    return prev_edge;
}

GRAPH_TEMPLATE
std::vector<GRAPH_EDGE_PTR> GRAPH_TYPE::bfsImpl(std::vector<i32> &dist,
                                                i32 start_node) const {
    std::queue<i32> q;
    q.push(start_node);
    std::vector<EdgePtr> prev_edge(N, nullptr);
    while (!q.empty()) {
        i32 cu = q.front();
        q.pop();
        for (auto &e : G[cu]) {
            i32 to = e->dst(cu);
            if (dist[to] != CMAX)
                continue;
            prev_edge[to] = e;
            dist[to] = dist[cu] + 1;
            q.push(to);
        }
    }
    return prev_edge;
}

/**
 * @brief 最短距離を計算する
 * @param start_node 始点
 * @param invalid 到達不能な頂点に格納される値
 * @return 各ノードまでの最短距離のリスト
 */
GRAPH_TEMPLATE
std::vector<GRAPH_COST_TYPE> GRAPH_TYPE::distances(i32 start_node,
                                                   Cost invalid) const {
    std::vector<Cost> dist(N, CMAX);
    dist[start_node] = 0;

    if constexpr (is_weighted) {
        dijkstraImpl(dist, start_node);
    } else {
        bfsImpl(dist, start_node);
    }

    for (auto &x : dist)
        if (x == CMAX)
            x = invalid;
    return dist;
}

/**
 * @brief 復元付き最短経路
 * @attention 到達可能でないとき、空の配列で返る
 * @attention 負閉路があるとき正しい動作を保証しない
 */
GRAPH_TEMPLATE
std::vector<GRAPH_EDGE_TYPE> GRAPH_TYPE::shortestPath(i32 start_node,
                                                      i32 end_node) const {
    std::vector<Cost> dist(N, CMAX);
    dist[start_node] = 0;
    std::vector<EdgePtr> prev_edge(N, nullptr);

    if constexpr (is_weighted) {
        prev_edge = dijkstraImpl(dist, start_node);
    } else {
        prev_edge = bfsImpl(dist, start_node);
    }

    if (dist[end_node] == CMAX)
        return {};

    i32 cu = end_node;
    std::vector<EdgeType> route;
    while (cu != start_node) {
        auto e = prev_edge[cu];
        if (cu == e->v0) {
            route.push_back(e->rev());
        } else {
            route.push_back(*e);
        }
        cu = e->dst(cu);
    }
    return {route.rbegin(), route.rend()};
}

// O(N^3)
GRAPH_TEMPLATE
Matrix<GRAPH_COST_TYPE> GRAPH_TYPE::distancesFromAllNodes(Cost invalid) const {
    auto mt(toMatrix(CMAX));

    for (i32 k = 0; k < N; k++)         // 経由する頂点
        for (i32 i = 0; i < N; i++)     // 始点
            for (i32 j = 0; j < N; j++) // 終点
                if (mt[i][k] != CMAX && mt[k][j] != CMAX)
                    mt[i][j] = std::min(mt[i][j], mt[i][k] + mt[k][j]);

    for (i32 i = 0; i < N; ++i)
        for (i32 j = 0; j < N; ++j)
            if (mt[i][j] == CMAX)
                mt[i][j] = invalid;
    return mt;
}

} // namespace gandalfr
