#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include <bits/stdc++.h>
#include "../graph/Kruscal.hpp"
using namespace std;
using ll = long long;
const int INF = 1001001001;
const int MAXINT = std::numeric_limits<int>::max();
const int MININT = std::numeric_limits<int>::min();
const ll INFLL = 1001001001001001001;
const ll MAXLL = std::numeric_limits<ll>::max();
const ll MINLL = std::numeric_limits<ll>::min();
const ll MOD  = 1000000007;
const ll _MOD = 998244353;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define rrep(i, j, n) for(ll i = (ll)(n-1); i >= (ll)(j); i--)
#define fore(i,a) for(auto &i : a)
#define all(a) (a).begin(),(a).end()
#define lr(a, l, r) (a).begin()+(l),(a).begin()+(r)
#define LF cout << endl
template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { return a < b && (a = b, true); }
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }
void Yes(bool ok){ cout << (ok ? "Yes" : "No") << endl; }

int main(void){
 
    //input
 
    int N, M;
    cin >> N >> M;
    graph<ll, false> G(N);
    rep(i,0,M){
        int a, b, c;
        cin >> a>> b >> c;
        G.add_edge(a, b, c);
    }
 
    //calculate
    
    cout << Kruscal(G).weight() << endl;
 
}