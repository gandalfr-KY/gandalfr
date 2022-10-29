#include <bits/stdc++.h>
#include <atcoder/all>
#include "gandalfr/standard/chmaxmin.hpp"
#include "gandalfr/standard/gcdlcm.hpp"
#include "gandalfr/standard/power.hpp"
using namespace std;
using namespace atcoder;
using ll = long long;
const int INF = 1001001001;
const int MAXINT = std::numeric_limits<int>::max();
const int MININT = std::numeric_limits<int>::min();
const ll INFL = 1001001001001001001;
const ll MAXLL = std::numeric_limits<ll>::max();
const ll MINLL = std::numeric_limits<ll>::min();
const ll MOD  = 1000000007;
const ll _MOD = 998244353;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define rrep(i, j, n) for(ll i = (ll)(n-1); i >= (ll)(j); i--)
#define all(a) (a).begin(),(a).end()
#define fromto(a, l, r) (a).begin()+(l),(a).begin()+(r)
#define LF cout << endl

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for(int i=0; i<(int)v.size(); i++) os << v[i] << (i+1 != (int)v.size() ? " " : "");
    return os;
}
template<typename T>
istream &operator>>(istream &is, vector<T> &v){
    for(T &in : v) is >> in;
    return is;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2>& p) {
    os << p.first << " " << p.second;
    return os;
}
template<typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}
template<typename T>
ostream &operator<<(ostream &os, queue<T> v) {
    for(int i=0; i<(int)v.size(); i++) {
        os << v.front() << (i+1 != (int)v.size() ? " " : "");
        v.push(v.front());
        v.pop();
    }
    return os;
}

int main(void){

    /*ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    ofstream fout("output.txt");*/

    //input



    //calculate



}