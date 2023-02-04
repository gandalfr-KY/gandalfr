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

#endif