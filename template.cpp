#include <bits/stdc++.h>
#include "gandalfr/basic"
using namespace std;
using ll = long long;
const int INF = 1001001001;
const ll INFLL = 1001001001001001001;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define rrep(i, j, n) for(ll i = (ll)(n-1); i >= (ll)(j); i--)
#define all(a) (a).begin(),(a).end()
#define LF cout << endl
#define debug(a) std::cerr << #a << ": " << a << std::endl
template<typename T> inline bool chmax(T &a, const T& b) { return a < b && (a = b, true); }
template<typename T> inline bool chmin(T &a, const T& b) { return a > b && (a = b, true); }
template<typename Key, typename Value> inline bool map_chmax(std::map<Key, Value>& mp, const Key& a, const Value& b) {
    auto it = mp.find(a);
    return it == mp.end() ? (mp[a] = b, true) : chmax(it->second, b);
}
template<typename Key, typename Value> inline bool map_chmin(std::map<Key, Value>& mp, const Key& a, const Value& b) {
    auto it = mp.find(a);
    return it == mp.end() ? (mp[a] = b, true) : chmin(it->second, b);
}
void Yes(bool ok){ std::cout << (ok ? "Yes" : "No") << std::endl; }

int main(void){



}
