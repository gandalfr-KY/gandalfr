#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){

    int N, M, K;
    cin >> N >> M >> K;
    Matrix<Mint998> A(N, M), B(M, K);
    cin >> A >> B;
    (A * B).print();

}
