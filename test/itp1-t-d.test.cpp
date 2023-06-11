#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D"
#include <bits/stdc++.h>
#include "../math/matrix.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){
 
    //input
 
    int H, W, L;
    cin >> H >> W >> L;
    matrix<ll> A(H, W), B(W, L);
    cin >> A >> B;

    //calculate
 
    (A * B).print();
 
}