#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B"
#include <bits/stdc++.h>
#include "../graph/graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){

    int N, M;
    cin >> N >> M;
    graph<int, false> G(N);
    rep(i,0,M){
        int a, b;
        cin >> a >> b;
        G.add_edge(a, b);
    }
    
    auto ans = G.lowlink().first;
    for(auto &e : ans) if(e.from > e.to) swap(e.from, e.to);
    sort(all(ans));
    for(auto &e : ans) cout << e << endl;

}