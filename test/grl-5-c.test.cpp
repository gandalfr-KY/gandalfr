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
        int a;
        cin >> a;
        rep(j,0,a){
            int b;
            cin >> b;
            G.add_edge(i, b);
        }
    }

    //calculate

    lowest_common_ancestor LCA(G);
    int q;
    cin >> q;
    while(q--){
        int a, b;
        cin >> a >> b;
        cout << LCA.get_ancestor(a, b) << endl;
    }

}