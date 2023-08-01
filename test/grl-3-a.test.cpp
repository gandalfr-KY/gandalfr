#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A"
#define IGNORE
#include <bits/stdc++.h>
#include "../graph/lowlink.hpp"
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
    auto ans(LL.articulation_points());
    sort(all(ans));
    for(auto x : ans) cout << x << endl;

}