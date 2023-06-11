#ifndef TOTIENT
#define TOTIENT
#include "../standard/power.hpp"
#include "factorize.hpp"

/* オイラー関数
 * O(√N)
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267874
 */
long long totient(long long n){
	std::vector<std::pair<long long, int>> facs = factorize(n);
	long long ret = 1;
	for(std::pair<long long, int> p : facs) ret *= power(p.first, p.second - 1) * (p.first - 1);
	return ret;
}

#endif