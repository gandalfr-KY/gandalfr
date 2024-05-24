#define IGNORE
#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include <bits/stdc++.h>
#include "gandalfr/standard/BSGS.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

    i32 w;
    cin >> w;
    while(w--) {
        i64 N, S, K;
        cin >> N >> S >> K;

        BSGS<i64> bsgs(S, 0LL, N);
        auto f = [&](i64 x) {
            return (x + K) % N;
        };
        auto g = [&](i64 x) {
            return (x + bsgs.getStepWidth() * K) % N;
        };
        bsgs.setFunction(f, g);
        cout << bsgs.findMinimum() << endl;
    }

}
