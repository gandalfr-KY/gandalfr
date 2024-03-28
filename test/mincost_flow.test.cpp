#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/FlowGraph.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M, F;
    cin >> N >> M >> F;
    FlowGraph G(N, M);
    rep(i,0,M) {
        i32 a, b, c, d;
        cin >> a >> b >> c >> d;
        G.addEdge(a, b, c, d);
    }
    cout << G.primalDual(0, N - 1, F) << endl;

}
