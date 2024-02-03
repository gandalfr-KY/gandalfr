#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include <bits/stdc++.h>
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

using namespace gandalfr;

int main(void){
    
    int N, M, s, t;
    cin >> N >> M >> s >> t;
    Graph<WEIGHTED, DIRECTED> G(N, M);
    rep(i,0,M) {
        int a, b, c;
        cin >> a >> b >> c;
        G.addEdge(a, b, c);
    }

    ll X = G.distances(s, -1)[t];
    if (X == -1) {
        cout << -1 << endl;
    } else {
        auto path = G.shortestPath(s, t);
        int Y = path.size();
        cout << X << " " << Y << endl;
        for (auto &e : path) {
            cout << e.v0 << " " << e.v1 << endl;
        } 
    }

}
