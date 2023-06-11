#ifndef MOD_INVERSE
#define MOD_INVERSE
#include <assert.h>
#include "Bezout_coefficients.hpp"

long long mod_inverse(long long x, int mod){
    assert(mod > 0);
    x %= mod;
    auto [a, b] = Bezout_coefficients(x, mod);
    assert(a * x == -b * mod + 1);
    return (a >= 0 ? a : a + mod);
}

#endif