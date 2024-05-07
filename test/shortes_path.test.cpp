#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Graph.hpp"
using namespace std;
using ll = long long;

using namespace gandalfr;

int main(void){
    
    i32 N, M, s, t;
    cin >> N >> M >> s >> t;
    Graph<WEIGHTED, DIRECTED> G(N, M);
    rep(i,0,M) {
        i32 a, b, c;
        cin >> a >> b >> c;
        G.addEdge(a, b, c);
    }

    ll X = G.distances(s, -1)[t];
    if (X == -1) {
        cout << -1 << endl;
    } else {
        auto path = G.shortestPath(s, t);
        i32 Y = path.size();
        cout << X << " " << Y << endl;
        for (auto& e : path) {
            cout << e.v0 << " " << e.v1 << endl;
        }
    }

}
