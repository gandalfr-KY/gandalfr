#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A"
#include <bits/stdc++.h>
#include "../graph/diameter.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    //input
 
    int N;
    cin >> N;
    graph<ll, false> G(N);
    rep(i,0,N-1){
        int a, b, c;
        cin >> a>> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate

    cout << diameter(G) << endl;
 
}