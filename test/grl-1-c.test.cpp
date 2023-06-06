#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C"
#include <bits/stdc++.h>
#include "../graph/Warshall_Floyd.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    //input
 
    int N, M;
    cin >> N >> M;
    graph<ll, true> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a>> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate
    
    auto dist = Warshall_Floyd(matrix(G, 1000000000LL));

    rep(i,0,N){
        rep(j,0,N){
            cout << (dist[i][j] == -1 ? "INF" : to_string(dist[i][j])) << (j == N - 1 ? '\n' : ' ');
        }
        cout << endl;
    }
 
}