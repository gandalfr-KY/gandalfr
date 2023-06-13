#ifndef FACTORIZE
#define FACTORIZE
#include <utility>
#include <cmath>
#include "prime_number_list.hpp"

/**
 * @brief 素因数分解する
 * @return prime_factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...}
 * @attention prime_factorize(1) => {}
 * @attention prime_factorize(0) => {{0, 1}}
 */ 
std::vector<std::pair<long long, int>> factorize(long long N){
    std::vector<std::pair<long long, int>> ret;
    prime_number_list::set_minimum_limit(ceil(sqrt(N)));
    long long p;
    for(long long p : prime_number_list::list()){
        if(N == 1 || (__int128_t)p * p > N) break;
        while(N % p == 0){
            if(ret.empty() || ret.back().first != p) ret.push_back({p, 1});
            else ret.back().second++;
            N /= p;
        }
    }
    if(N != 1) ret.push_back({N, 1});
    return ret;
}

#endif