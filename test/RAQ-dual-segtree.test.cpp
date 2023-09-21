#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"
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
    dual_segment_tree<monoid_action::Plus<int>> seg(N);

    rep(i,0,Q) {
        int q;
        cin >> q;
        if (q == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            seg.act(s - 1, t, x);
        } else {
            int t;
            cin >> t;
            cout << seg.get(t - 1) << endl;
        }
    }

}