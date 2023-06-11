#ifndef FACTORIZE
#define FACTORIZE
#include <utility>
#include <cmath>
#include "primes_list.hpp"

/* 素因数分解
 * prime_factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...}
 * prime_factorize(1) => {}
 * prime_factorize(0) => {{0, 1}}
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267865
 */ 
std::vector<std::pair<long long, int>> factorize(long long N){
    std::vector<std::pair<long long, int>> ret;
    primes_list::set_lower_limit(ceil(sqrt(N)));
    long long p;
    for(int i=0; p = primes_list::list()[i], p * p <= N; i++){
        while(N % p == 0){
            if(ret.empty() || ret.back().first != p) ret.push_back({p, 1});
            else ret.back().second++;
            N /= p;
        }
        if(N == 1) break;
    }
    if(N != 1) ret.push_back({N, 1});
    return ret;
}

#endif