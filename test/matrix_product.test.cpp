#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include <bits/stdc++.h>
#include "../math/matrix.hpp"
#include "../standard/mod_integer.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){

    int N, M, K;
    cin >> N >> M >> K;
    matrix<_mint> A(N, M), B(M, K);
    cin >> A >> B;
    (A * B).print();

}
