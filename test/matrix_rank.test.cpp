#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 N, M;
    cin >> N >> M;
    Matrix<Mint998> A(N, M);
    cin >> A;
    cout << A.rank() << endl;

}
