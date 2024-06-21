#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B"

#include <bits/stdc++.h>
#include "gandalfr/graph/lowlink.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M;
    cin >> N >> M;
    Graph<UNWEIGHTED, UNDIRECTED> G(N);
    rep(i,0,M) {
        i32 a, b;
        cin >> a >> b;
        G.addEdge(a, b);
    }

    auto tmp = G.bridges();
    for (auto &e : tmp) if (e.v0 > e.v1) std::swap(e.v0, e.v1);
    sort(all(tmp), [](Edge<false> a, Edge<false> b) {
        if (a.v0 == b.v0) return a.v1 < b.v1;
        return a.v0 < b.v0;
    });
    for (auto e : tmp) {
        cout << e << endl;
    } 

}
