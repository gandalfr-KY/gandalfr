#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"
#include <bits/stdc++.h>
#include "../graph/shortest_path.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    //input
 
    int N, M, K;
    cin >> N >> M >> K;
    graph<ll, true> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a>> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate
    
    auto dist = shortest_path(G, K);
    for(auto x : dist){
        if(x == -1) cout << "INF" << endl;
        else cout << x << endl;
    }
 
}