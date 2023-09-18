#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"
#include <bits/stdc++.h>
#include "../graph/Manhattan_minimum_spanning_tree.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    //input
 
    int N;
    cin >> N;
    vector<ll> X(N), Y(N);
    rep(i,0,N){
        cin >> X[i] >> Y[i];
    }
 
    //calculate
 
    Manhattan_minimum_spanning_tree mst(X, Y);
 
    cout << mst.get_tree().weight() << endl;
    for(auto &e : mst.get_tree().edges()){
        cout << e->v[0] << " " << e->v[1] << endl; 
    }

}