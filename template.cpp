#include <bits/stdc++.h>
#include "gandalfr/basic"
using namespace std;
const gandalfr::i32 INF = 1001001001;
const gandalfr::i64 INFLL = 1001001001001001001;
#define rep(i, j, n) for(gandalfr::i64 i = (gandalfr::i64)(j); i < (gandalfr::i64)(n); i++)
#define rrep(i, j, n) for(gandalfr::i64 i = (gandalfr::i64)(n-1); i >= (gandalfr::i64)(j); i--)
#define all(a) (a).begin(),(a).end()
#define LF cout << endl
template<typename T> void print_debug(T t) { std::cerr << t << std::endl; }
template<typename First, typename... Rest> void print_debug(First parm1, Rest... parm) {
    std::cerr << parm1 << ", ", print_debug(parm...);
}
#define debug(...) { \
    std::cerr << #__VA_ARGS__ << ": "; \
    print_debug(__VA_ARGS__); \
}
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

using namespace gandalfr;

int main(void) {


}
