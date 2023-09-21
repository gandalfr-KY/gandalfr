#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D"
#include <bits/stdc++.h>
#include "../data_structure/dual_segment_tree.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()
void Yes(bool ok){ cout << (ok ? "Yes" : "No") << endl; }

int main(void){
 
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> A(N, {0, INT32_MAX});
    dual_segment_tree<monoid_action::Chmax<pair<int, int>>> seg(A);

    rep(i,0,Q) {
        int q;
        cin >> q;
        if (q == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            seg.act(s, t + 1, {i + 1, x});
        } else {
            int t;
            cin >> t;
            cout << seg.get(t).second << endl;
        }
    }

}
