#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include <bits/stdc++.h>
#include "../graph/graph.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    int N, M, s, t;
    cin >> N >> M >> s >> t;
    graph<ll, true> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a >> b >> c;
        G.add_edge(a,b,c);
    }

    auto E(G.shortest_path(s, t));
    if (s != t && E.empty()) {
        cout << -1 << endl;
        return 0;
    }
    ll ans = 0;
    for (auto e : E) ans += e.cost;
    cout << ans << " " << E.size() << endl;
    for (auto e : E) cout << e.from << " " << e.to << endl;

}
