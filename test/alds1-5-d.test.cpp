#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D"
#include <bits/stdc++.h>
#include "../standard/inversion.hpp"
#include "../other/io_supporter.hpp"
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
 
    int N;
    cin >> N;
    vector<int> A(N);
    cin >> A;

    //calculate
    
    cout << inversion(A.begin(), A.end()) << endl;
 
}