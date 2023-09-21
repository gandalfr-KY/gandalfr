#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <bits/stdc++.h>
#include "../data_structure/union_find.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    int N, Q;
    cin >> N >> Q;
    union_find uf(N);
    rep(i,0,Q) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) uf.merge(x, y);
        else cout << uf.same(x, y) << endl;
    }

}
