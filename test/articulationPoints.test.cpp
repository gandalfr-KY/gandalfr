#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A"

#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
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

    auto inc = G.articulationPoints();
    rep(i,0,N) {
        if (inc[i] > 0) {
            std::cout << i << std::endl;
        }
    }

}
