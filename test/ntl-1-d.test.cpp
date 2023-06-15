#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D"
#include <bits/stdc++.h>
#include "../math/totient.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){
    int N;
    cin >> N;
    cout << totient(N) << endl;
}