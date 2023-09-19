#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"
#include <bits/stdc++.h>
#include "../graph/flow_graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    int N, M;
    cin >> N >> M;
    flow_graph<int, ll> G(N, M);
    rep(i,0,M) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add_edge(a, b, c);
    }

    cout << G.Dinic(0, N - 1) << endl;

}