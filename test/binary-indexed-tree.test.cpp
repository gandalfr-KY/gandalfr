#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"
#include <bits/stdc++.h>
#include "../data_structure/binary_indexed_tree.hpp"
using namespace std;
using ll = long long;
#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)
#define all(a) (a).begin(),(a).end()
void Yes(bool ok){ cout << (ok ? "Yes" : "No") << endl; }

int main(void){
 
    /*ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    ofstream fout("output.txt");*/
 
 
    //input
 
    int N, Q;
    cin >> N >> Q;
    binary_indexed_tree<ll> bit(N);

    //calculate

    rep(i,0,Q){
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 0) bit.add(b - 1, c);
        else cout << bit.get(c) - bit.get(b - 1) << endl;
    }
 
}