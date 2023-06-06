#ifndef MANHATTAN_MST
#define MANHATTAN_MST
#include "gandalfr/graph/graph.hpp"

// from : https://hitonanode.github.io/cplib-cpp/graph/manhattan_mst.hpp
template<typename WEIGHT>
class Manhattan_minimum_spanning_tree {
  private:
    graph<WEIGHT, false> mst;

  public:

    Manhattan_minimum_spanning_tree(const std::vector<WEIGHT> &xs, const std::vector<WEIGHT> &ys) : mst(xs.size()) {
        int N = xs.size();
        std::vector<edge<WEIGHT>> E;
        std::vector<int> idx(N);
        std::iota(idx.begin(), idx.end(), 0);
        for (int s = 0; s < 2; s++) {
            for (int t = 0; t < 2; t++) {
                std::sort(idx.begin(), idx.end(), [&](int i, int j){ return xs[i] + ys[i] < xs[j] + ys[j]; });
                std::map<WEIGHT, int> sweep;
                for (int i : idx) {
                    for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it)) {
                        int j = it->second;
                        if (xs[i] - xs[j] < ys[i] - ys[j]) break;
                        E.emplace_back(edge<WEIGHT>{i, j, std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]), -1});
                    }
                    sweep[-ys[i]] = i;
                }
                std::swap(xs, ys);
            }
            for(auto &x : xs) x = -x;
        }

        int cnt_id = 0;
        sort(E.begin(), E.end());
        for(auto &e : E) if(!mst.is_connected(e.from, e.to)) {
            e.id = cnt_id;
            mst.add_edge(e);
            cnt_id++;
        }
    }

    const graph<WEIGHT, false> &graph(){ return mst; }

};

#endif