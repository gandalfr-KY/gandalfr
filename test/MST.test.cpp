#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){

    int N, M;
    cin >> N >> M;
    Graph<WEIGHTED, UNDIRECTED> G(N);
    rep(i,0,M) {
        int a, b, c;
        cin >> a >> b >> c;
        G.addEdge(a, b, c);
    }

    cout << G.MST().weight() << endl;
      
}
