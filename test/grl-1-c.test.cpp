#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C"
#include <bits/stdc++.h>
#include "../graph/graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
const ll INFLL = 1001001001001001001;

int main(void){

    //input
 
    int N, M;
    cin >> N >> M;
    graph<ll, true> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a >> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate
    
    auto dist(G.distances_from_all_nodes(INT64_MIN));

    rep(i,0,N){
        if(dist(i, i) < 0){
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    rep(i,0,N){
        rep(j,0,N){
            cout << (dist(i, j) == INT64_MIN ? "INF" : to_string(dist(i, j))) << (j == N - 1 ? '\n' : ' ');
        }
    }
 
}