#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <bits/stdc++.h>
#include "../graph/Kruscal.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){
 
    //input
 
    int N, M;
    cin >> N >> M;
    graph<ll, false> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a>> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate
    
    cout << Kruscal(G).weight() << endl;
 
}