#ifndef TOTIENT
#define TOTIENT
#include "gandalfr/standard/power.hpp"
#include "gandalfr/math/integer/prime_factorize.hpp"

/* オイラー関数
 * O(√N)
 */
long long totient(long long n){
	std::vector<std::pair<long long, int>> facs = prime_factorize(n);
	long long ret = 1;
	for(std::pair<long long, int> p : facs) ret *= power(p.first, p.second - 1) * (p.first - 1);
	return ret;
}

#endif