#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"
#include <bits/stdc++.h>
#include "../standard/rolling_hash.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

int main(void){

    //ifstream in("in");
    //cin.rdbuf(in.rdbuf());
    //ofstream fout("out");

    // input

	string s, t;
	cin >> s >> t;
	rolling_hash rh(s), _rh(t);
    auto t_hash = _rh.get(0, t.size());

	// calculate

	vector<int> ans;
    rep(i,0,(int)s.size() - (int)t.size() + 1){
        if(rh.get(i, i + t.size()) == t_hash) cout << i << endl;
    }
    
}
