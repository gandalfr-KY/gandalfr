#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/data_structure/PersistentUnionFind.hpp"

using namespace std;
using namespace gandalfr;

int main() {
    
    i32 N, Q;
    cin >> N >> Q;
    PersistentUnionFind puf(N);
    vector<i32> ans;

    rep(i,0,Q) {
        i32 t, k, u, v;
        cin >> t >> k >> u >> v;
        if (t == 0) {
            puf.unite(k + 1, u, v);
        } else {
            ans.push_back(puf.isSame(k + 1, u, v));
            puf.unite(puf.version() - 1, 0, 0);
        }
    }
    cout << ans << endl;

}
