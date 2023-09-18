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
        G.add_edge(min(a, b), max(a, b));
    }
    
    auto ans = G.lowlink().first;
    sort(all(ans), [](const edge<int> &a, const edge<int> &b) {
        if (a.v[0] == b.v[0]) {
            return a.v[1] < b.v[1];
        }
        return a.v[0] < b.v[0];
    });
    for(auto &e : ans) cout << e << endl;

}