#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Graph.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M;
    cin >> N >> M;
    Graph<WEIGHTED, UNDIRECTED> G(N);
    rep(i,0,M) {
        i32 a, b, c;
        cin >> a >> b >> c;
        G.addEdge(a, b, c);
    }

    cout << G.MST().weight() << endl;
      
}
