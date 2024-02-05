#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/FlowGraph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){

    int N, M, F;
    cin >> N >> M >> F;
    FlowGraph G(N, M);
    rep(i,0,M) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        G.addEdge(a, b, c, d);
    }
    cout << G.primalDual(0, N - 1, F) << endl;

}
