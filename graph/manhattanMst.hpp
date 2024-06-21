#pragma once
#include <map>
#include <numeric>

#include "../data_structure/UnionFind.hpp"
#include "Graph.hpp"

namespace gandalfr {

/**
 * @see
 * https://github.com/hitonanode/cplib-cpp/blob/master/graph/manhattan_mst.hpp
 * @brief マンハッタン距離で最小重み全域木を構成する。
 * @param xs 各ノードの x 座標
 * @param ys 各ノードの y 座標
 */
Graph<true, false> manhattanMst(std::vector<i64> &xs, std::vector<i64> &ys) {
    i32 N = xs.size();
    std::vector<i32> idx(N);
    std::iota(idx.begin(), idx.end(), 0);
    std::vector<Edge<true>> E;
    for (i32 s = 0; s < 2; s++) {
        for (i32 t = 0; t < 2; t++) {
            std::sort(idx.begin(), idx.end(), [&](i32 i, i32 j) {
                return xs[i] + ys[i] < xs[j] + ys[j];
            });
            std::map<i64, i32> sweep;
            for (i32 i : idx) {
                for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end();
                     it = sweep.erase(it)) {
                    i32 j = it->second;
                    if (xs[i] - xs[j] < ys[i] - ys[j])
                        break;
                    E.emplace_back(
                        i, j, std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]),
                        -1);
                }
                sweep[-ys[i]] = i;
            }
            std::swap(xs, ys);
        }
        for (auto &x : xs) {
            x = -x;
        }
    }

    Graph<true, false> mst;
    mst.resize(xs.size());
    mst.reserve(xs.size() - 1);
    std::sort(E.begin(), E.end(), [](const Edge<true> &a, const Edge<true> &b) {
        return a.cost < b.cost;
    });
    UnionFind uf(N);
    for (auto &e : E) {
        if (!uf.isSame(e.v0, e.v1)) {
            uf.unite(e.v0, e.v1);
            mst.addEdge(e);
        }
    }
    return mst;
}
} // namespace gandalfr
