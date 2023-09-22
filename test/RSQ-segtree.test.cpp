#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <bits/stdc++.h>
#include "../data_structure/segment_tree.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)


int main(void){
    
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i,0,N) cin >> A[i];

    segment_tree<monoid::Plus<ll>> seg(A);
    rep(i,0,Q) {
        ll q, a, b;
        cin >> q >> a >> b;
        if (q == 0) seg[a] = seg[a] + b;
        else cout << seg(a, b) << endl;
    }

}
