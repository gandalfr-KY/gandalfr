#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M, K;
    cin >> N >> M >> K;
    Matrix<Mint998> A(N, M), B(M, K);
    cin >> A >> B;
    (A * B).print();

}
