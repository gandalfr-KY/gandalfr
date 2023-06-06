#define PROBLEM "https://atcoder.jp/contests/abc296/tasks/abc296_f"
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
    vector<int> A(N), B(N);
    cin >> A >> B;
    vector<int> _A(A), _B(B);

    //calculate

    sort(all(_A));
    sort(all(_B));
    if(_A != _B){
        Yes(false);
        return 0;
    }
    
    rep(i,0,N-1){
        if(_A[i] == _A[i+1]){
            Yes(true);
            return 0;
        }
    }
 
    Yes(inversion(A) % 2 == inversion(B) % 2);
 
}