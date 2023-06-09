#define PROMLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D"
#include <bits/stdc++.h>
#include "gandalfr/standard/longest_increasing_subsequence.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()
int main(void){
 
    //input
 
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i,0,N) cin >> A[i];

    //calculate
 
    cout << longest_increasing_subsequence(all(A), true) << endl;
 
}