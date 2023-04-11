#ifndef TRAVELING_SALESMAN
#define TRAVELING_SALESMAN
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

/*
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7650432#1
 */
template<class WEIGHT, bool is_directed>
WEIGHT traveling_salesman(const internal::_base_graph<WEIGHT, is_directed> &G){
    matrix<WEIGHT> adj(G, -1);
    const WEIGHT MAX = std::numeric_limits<WEIGHT>::max() / 2;
    int N = G.nodes();

    std::vector<std::vector<WEIGHT>> dp((1 << N), std::vector<WEIGHT>(N, MAX));
    dp[0][0] = 0;

    for(long long cuS = 0; cuS < (1 << N); cuS++){
        for(int cu = 0; cu < N; cu++){
            for(int ne = 0; ne < N; ne++){
                if(cuS & (1 << ne) || adj[cu][ne] == -1) continue;
                long long neS = cuS ^ (1 << ne);
                dp[neS][ne] = std::min(dp[neS][ne], dp[cuS][cu] + adj[cu][ne]);
            }
        }
    }

    WEIGHT ret = dp[(1 << N) - 1][0];
    if(ret == MAX) ret = -1;
    return ret;
}

#endif