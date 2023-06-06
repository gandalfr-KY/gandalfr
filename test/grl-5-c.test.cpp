#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C"
#include <bits/stdc++.h>
#include "../graph/lowest_common_ancestor.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){
 
    //input
 
    int N;
    cin >> N;
    graph<int, false> G(N);
    rep(i,0,N){
        int n;
        cin >> n;
        rep(j,0,n){
            int a;
            cin >> a;
            G.add_edge(i, a);
        }
    }
 
    //calculate
 
    lowest_common_ancestor LCA(G);
    std::vector<ll> ans;

    int Q;
    cin >> Q;
    rep(i,0,Q){
        int a, b;
        cin >> a >> b;
        ans.push_back(LCA.get_ancestor(a, b));
    }

    for(auto x : ans) cout << x << endl;

}
