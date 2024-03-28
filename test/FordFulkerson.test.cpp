#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"
#include <bits/stdc++.h>
#include "gandalfr/graph/FlowGraph.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M;
    cin >> N >> M;
    FlowGraph G(N, M);
    rep(i,0,M) {
        i32 a, b, c;
        cin >> a >> b >> c;
        G.addEdge(a, b, c);
    }

    std::cout << G.fordFulkerson(0, N - 1) << std::endl;

}
