#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include <bits/stdc++.h>
#include "../math/matrix.hpp"
#include "../standard/mod_integer.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){

    int N;
    cin >> N;
    matrix<_mint> A(N, N);
    cin >> A;
    auto INV = A.inverse();
    if (INV.size_H() == 0) {
        cout << -1 << endl;
    } else {
        INV.print();
    }

}
