#define PROBLEM "https://atcoder.jp/contests/jsc2021/tasks/jsc2021_g"
#define IGNORE
#include <bits/stdc++.h>
#include "gandalfr/math/matrix.hpp"
#include "gandalfr/standard/mod_integer.hpp"
#include "gandalfr/graph/Manhattan_minimum_spanning_tree.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){

    //input
 
    int N;
    cin >> N;
 
    matrix<int> mat(N, N);
    cin >> mat;
 
    auto v(mat);
 
    graph<int, false> G(N);
    rep(i,0,N) rep(j,i+1,N) if(mat[i][j] == 1) {
        if(G.are_connected(i, j)){
            cout << 0 << endl;
            return 0;
        }
        G.add_edge(i, j);
    }
 
    auto cc = G.connected_components();
    int M = cc.size();
    vector<int> gr_id(N, -1);
    rep(i,0,M) for(auto x : cc[i]) gr_id[x] = i;
 
    //calculate
 
    if(M == 1){
        cout << 1 << endl;
        return 0;
    }
    
    matrix<int> shrinked(M, M);
    rep(i,0,N) rep(j,i+1,N){
        int u = gr_id[i], v = gr_id[j];
        if(mat[i][j] == -1 && u == v) continue;
        if(mat[i][j] == -1) shrinked[u][v]++, shrinked[v][u]++;
    }
 
    matrix<mod_integer<1000000007>> dt(M - 1, M - 1);
    rep(i,0,M-1) rep(j,0,M-1) dt[i][j] = -shrinked[i][j];
    rep(i,0,M-1){
        int sum = 0;
        rep(j,0,M) sum += shrinked[i][j];
        dt[i][i] = sum;
    }
    cout << dt.determinant() << endl;
 
}