#include <bits/stdc++.h>
#include "gandalfr/basic"
using namespace std;
using ll = long long;
const int INF = 1001001001;
const ll INFLL = 1001001001001001001;
const ll MOD  = 1000000007;
const ll _MOD = 998244353;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define rrep(i, j, n) for(ll i = (ll)(n-1); i >= (ll)(j); i--)
#define all(a) (a).begin(),(a).end()
#define LF cout << endl
#ifdef ENABLE_MULTI_FOR
#define mfor(it, v) for(multi_iter it(v); !it.fin(); ++it)
#endif
template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { return a < b && (a = b, true); }
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }
void Yes(bool ok){ std::cout << (ok ? "Yes" : "No") << std::endl; }

int main(void){

    int N;
    cin >> N;
    vector<int> A(N), B(N);
    cin >> A >> B;

    vector dp(N, vector<vector<ll>>(2, vector<ll>(2, INFLL)));
    dp[0][0][0] = A[0];
    dp[0][1][1] = 0;
    rep(i,1,N) {
        rep(j,0,2) rep(k,0,2) rep(prvj,0,2) {
            chmin(dp[i][j][k], dp[i-1][prvj][k] +
                (j == 0 ? A[i] : 0) + (j == prvj ? B[i] : 0));
        }
    }

    ll ans = INFLL;
    rep(j,0,2) rep(k,0,2) {
        chmin(ans, dp[N-1][j][k] + (j == k ? B[N-1] : 0));
    }
    cout << ans << endl;
    

}
