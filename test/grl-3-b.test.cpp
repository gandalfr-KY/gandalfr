#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B"
#include <bits/stdc++.h>
#include "gandalfr/graph/lowlink.hpp"
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
    lowlink LL(G);
    vector<edge<int>> ans;
    for(auto id : LL.bridges()) {
        ans.push_back(G.edges()[id]);
    }
    for(auto &e : ans) if(e.from > e.to) swap(e.from, e.to);
    sort(all(ans));
    for(auto &e : ans) cout << e << endl;

}