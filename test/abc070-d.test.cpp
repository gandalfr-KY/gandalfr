#define PROBLEM "https://atcoder.jp/contests/abc070_d"
#include <bits/stdc++.h>
#include "../graph/lowest_common_ancestor.hpp"
#include "../graph/shortest_path.hpp"
#include "../other/io_supporter.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){
 
    //input
 
    int N;
    cin >> N;
    graph<ll, false> G(N);
    rep(i,0,N - 1){
        int a,b,c;
        cin>>a>>b>>c;
        G.add_edge(a-1,b-1,c);
    }
 
    int Q, K;
    cin >> Q >> K;
    K--;
    vector<int> x(Q), y(Q);
    rep(i,0,Q){
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
    }
 
    //calculate
 
    lowest_common_ancestor LCA(G);
    auto dist = shortest_path(G, 0);

    std::vector<ll> ans;
 
    rep(i,0,Q){
        ll lca1 = LCA.get_ancestor(K, x[i]);
        ll dist1 = dist[K] + dist[x[i]] - 2 * dist[lca1];
        ll lca2 = LCA.get_ancestor(K, y[i]);
        ll dist2 = dist[K] + dist[y[i]] - 2 * dist[lca2];
        ans.push_back(dist1 + dist2);
    }
 
    cout << ans << endl;
 
 
 
}