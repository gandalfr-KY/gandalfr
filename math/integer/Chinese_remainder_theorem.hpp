#ifndef CHINESE_REMAINDER_THEOREM
#define CHINESE_REMAINDER_THEOREM
#include <vector>
#include "gandalfr/math/integer/mod_inverse.hpp"

// gcd(all(m)) must be 1
long long Chinese_remainder_theorem(std::vector<long long> x, std::vector<long long> m){
    int n = x.size();
    long long mlt = 1;
    for(int i = 0; i < n; i++) mlt *= m[i];
    
    long long ret = 0;
    for(int i = 0; i < n; i++){
        ret = (ret + x[i] * (mlt / m[i]) * mod_inverse(mlt / m[i], m[i])) % mlt;
    }
    return ret;
}

/*
 * O(N)
 * from : https://kopricky.github.io/code/Computation_Advanced/garner.html
 */
long long garner(std::vector<long long> a, std::vector<long long> p, const int mod){
    for(long long &x : a) x %= mod;
    int sz = a.size();
    std::vector<long long> kp(sz + 1, 0), rmult(sz + 1, 1);
    p.push_back(mod);
    for(int i = 0; i < sz; ++i){
        long long x = (a[i] - kp[i]) * mod_inverse(rmult[i], p[i]) % p[i];
        x = (x < 0) ? (x + p[i]) : x;
        for(int j = i + 1; j < sz + 1; ++j){
            kp[j] = (kp[j] + rmult[j] * x) % p[j];
            rmult[j] = rmult[j] * p[i] % p[j];
        }
    }
    return kp[sz];
}

#endif