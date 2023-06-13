#define PROBLEM "https://atcoder.jp/contests/abc284/tasks/abc284_f"
#define IGNORE
#include <bits/stdc++.h>
#include "../standard/rolling_hash.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()

int main(void){
 
    /*ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    ofstream fout("output.txt");*/
 
 
    //input
 
    int N;
    cin >> N;
    string s, t;
    cin >> s;
    t = s;
    reverse(all(t));
 
    //calculate
    
    rolling_hash rh(s), rh_rev(t);
    rep(i,0,N+1){
        auto hs = rh.get(0, i);
        rh.concat(hs, N + i, 2 * N);
        if(hs == rh_rev.get(N - i, 2 * N - i)){
            cout << string(s.begin(), s.begin() + i) + string(s.begin() + N + i, s.end()) << endl;
            cout << i << endl; 
            return 0;
        }
    }
    
    cout << -1 << endl;
 
}
