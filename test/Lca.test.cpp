#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Lca.hpp"
using namespace std;
using namespace gandalfr;

int main(void){
 
    i32 N;
    cin >> N;
    Graph<UNWEIGHTED, UNDIRECTED> G(N, N - 1);
    rep(i,0,N){
        i32 a;
        cin >> a;
        rep(j,0,a){
            i32 b;
            cin >> b;
            G.addEdge(i, b);
        }
    }

    Lca lca(G, 0);
    i32 q;
    cin >> q;
    while(q--){
        i32 a, b;
        cin >> a >> b;
        cout << lca.getAncestor(a, b) << endl;
    }

}