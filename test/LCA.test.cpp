#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/LCA.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){
 
    int N;
    cin >> N;
    Graph<UNWEIGHTED, UNDIRECTED> G(N, N - 1);
    rep(i,0,N){
        int a;
        cin >> a;
        rep(j,0,a){
            int b;
            cin >> b;
            G.addEdge(i, b);
        }
    }

    LCA lca(G, 0);
    int q;
    cin >> q;
    while(q--){
        int a, b;
        cin >> a >> b;
        cout << lca.getAncestor(a, b) << endl;
    }

}