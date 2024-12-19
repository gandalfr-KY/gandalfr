#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/lowlink.hpp"
using namespace std;
using namespace gandalfr;

int main(void) {

    i32 N, M;
    cin >> N >> M;
    Graph<false, false> G(N);
    rep(i,0,M) {
        i32 a, b;
        cin >> a >> b;
        G.addEdge(a, b);
    }

    auto ans = G.twoEdgeConnectedComponent();
    std::cout << ans.size() << std::endl;
    for (auto v : ans) {
        cout << v.size() << " " << v << std::endl;
    }


}
