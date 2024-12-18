#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

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

    vector<set<i32>> bcs;
    for (auto v : G.biconnectedComponent()) {
        assert(!v.empty());
        std::set<i32> st;
        for (auto e : v) st.insert(e.v0), st.insert(e.v1);
        if (!st.empty()) bcs.push_back(st);
    }
    for (i32 i = 0; i < N; ++i) if (G[i].size() == 0) {
        bcs.push_back({});
        bcs.back().insert(i);
    }

    std::cout << bcs.size() << std::endl;
    for (auto v : bcs) {
        std::cout << v.size() << " " << v << std::endl;
    }


}
