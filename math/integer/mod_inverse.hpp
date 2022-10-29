#ifndef MOD_INVERSE
#define MOD_INVERSE
#include <assert.h>
#include "gandalfr/math/integer/Bezout_coefficients.hpp"

long long mod_inverse(long long x, long long mod){
    std::pair<long long, long long> p = Bezout_coefficients(x, mod);
    assert(p.first != 0 && p.second != 0);
    if(p.first < 0) p.first += mod;
    return p.first;
}

#endif