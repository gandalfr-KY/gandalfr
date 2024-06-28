#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/data_structure/Segtree.hpp"
#include "gandalfr/graph/Hld.hpp"
using namespace std;
using namespace gandalfr;

using S = i64;
S op(S a, S b) {return a+b;}
S e() {return 0;}

int main(void){

    i32 N, Q;
    cin >> N >> Q;
    vector<i32> A(N);
    cin >> A;
    Graph<UNDIRECTED, UNWEIGHTED> G(N, N - 1);
    rep(i,0,N-1) {
        i32 a, b;
        cin >> a >> b;
        G.addEdge(a, b);
    }

    Hld hld(G, 0);

    vector<i64> init(N);
    rep(i,0,N) {
        i32 u = hld.node(i).first;
        init[u] = A[i];
    }
    Segtree<S,op,e> seg(init);
    vector<i64> answers;
    rep(i,0,Q) {
        i32 q;
        cin >> q;
        if (q == 0) {
            i64 p, x;
            cin >> p >> x;
            p = hld.node(p).first;
            seg.set(p, seg[p] + x);
        } else {
            i32 u, v;
            cin >> u >> v;
            i64 ans = 0;
            for (auto [l, r] : hld.path(u, v)) {
                ans += seg.prod(l, r);
            }
            answers.push_back(ans);
        }
    }
    cout << answers << endl;

}
