#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N;
    cin >> N;
    Matrix<Mint998> A(N, N);
    cin >> A;
    auto I = A.inv();
    if (I.isNull()) {
        cout << -1 << endl;
    } else {
        I.print();
    }

}
