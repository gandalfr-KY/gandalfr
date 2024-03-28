#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i64 N, K;
    cin >> N >> K;
    Matrix<Mint998> A(N, N);
    cin >> A;
    A.power(K).print();

}
