#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){

    ll N, K;
    cin >> N >> K;
    Matrix<Mint998> A(N, N);
    cin >> A;
    A.power(K).print();

}
