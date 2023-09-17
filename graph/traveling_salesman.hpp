#pragma once
#include "../math/matrix.hpp"
#include "graph.hpp"

/*
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7650432#1
 */
template <class Weight, bool is_directed>
Weight traveling_salesman(const graph<Weight, is_directed> &G) {
    matrix<Weight> adj(G, -1);
    const Weight MAX = std::numeric_limits<Weight>::max() / 2;
    int N = G.count_nodes();

    std::vector<std::vector<Weight>> dp((1 << N), std::vector<Weight>(N, MAX));
    dp[0][0] = 0;

    for (long long cuS = 0; cuS < (1 << N); cuS++) {
        for (int cu = 0; cu < N; cu++) {
            for (int ne = 0; ne < N; ne++) {
                if (cuS & (1 << ne) || adj[cu][ne] == -1)
                    continue;
                long long neS = cuS ^ (1 << ne);
                dp[neS][ne] = std::min(dp[neS][ne], dp[cuS][cu] + adj[cu][ne]);
            }
        }
    }

    Weight ret = dp[(1 << N) - 1][0];
    if (ret == MAX)
        ret = -1;
    return ret;
}
