#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/ManhattanMST.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){
 
    int N;
    cin >> N;
    vector<i64> X(N), Y(N);
    rep(i,0,N){
        cin >> X[i] >> Y[i];
    }
 
    ManhattanMST mmst(X, Y);
 
    cout << mmst.getMST().weight() << endl;
    for(auto &e : mmst.getMST().getAllEdges()){
        cout << e->v0 << " " << e->v1 << endl; 
    }
 
}