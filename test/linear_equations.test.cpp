#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1308"
#include <bits/stdc++.h>
#include "gandalfr/standard/Mint.hpp"
#include "gandalfr/math/Matrix.hpp"
using namespace std;
using namespace gandalfr;

int main(void){

	vector<bool> ans;
	i32 H, W, D;

	while (cin >> W >> H >> D, H != 0) {
		vector<Mint<2>> b(H * W);
		rep(i,0,H) {
			rep(j,0,W) {
				i32 tmp;
				cin >> tmp;
				b[i * W + j] = tmp;
			}
		}
		
		Matrix<Mint<2>> A(H * W, H * W, 0); 
		rep(i,0,H) rep(j,0,W) {
			rep(ii,0,H) rep(jj,0,W) {
				i32 d = abs(i-ii) + abs(j-jj);
				if (d == 0 || d == D) {
					A[i*W+j][ii*W+jj] = true;
				}
			}
		}
		
		auto x = A.solveLinearEquation(b);
		ans.push_back(!x.empty());

	}

	for (auto b: ans) {
		cout << b << endl;
	}

}
