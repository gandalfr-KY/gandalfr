#pragma once
#include <map>
#include <numeric>

#include "graph.hpp"

/**
 * @see https://hitonanode.github.io/cplib-cpp/graph/manhattan_mst.hpp
 * @brief マンハッタン距離で最小重み全域木を構成する。
 * @param xs 各ノードの x 座標
 * @param ys 各ノードの y 座標
 */
template <typename Weight> class Manhattan_minimum_spanning_tree {
  private:
    graph<Weight, false> mst;

  public:
    Manhattan_minimum_spanning_tree(std::vector<Weight> &xs,
                                    std::vector<Weight> &ys)
        : mst(xs.size()) {
        int N = xs.size();
        std::vector<edge<Weight>> E;
        std::vector<int> idx(N);
        std::iota(idx.begin(), idx.end(), 0);
        for (int s = 0; s < 2; s++) {
            for (int t = 0; t < 2; t++) {
                std::sort(idx.begin(), idx.end(), [&](int i, int j) {
                    return xs[i] + ys[i] < xs[j] + ys[j];
                });
                std::map<Weight, int> sweep;
                for (int i : idx) {
                    for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end();
                         it = sweep.erase(it)) {
                        int j = it->second;
                        if (xs[i] - xs[j] < ys[i] - ys[j])
                            break;
                        E.emplace_back(edge<Weight>{i, j,
                                                    std::abs(xs[i] - xs[j]) +
                                                        std::abs(ys[i] - ys[j]),
                                                    -1});
                    }
                    sweep[-ys[i]] = i;
                }
                std::swap(xs, ys);
            }
            for (auto &x : xs)
                x = -x;
        }

        int cnt_id = 0;
        sort(E.begin(), E.end());
        for (auto &e : E)
            if (!mst.are_connected(e.from, e.to)) {
                e.id = cnt_id;
                mst.add_edge(e);
                cnt_id++;
            }
    }

    const graph<Weight, false> &get_tree() { return mst; }
};
