#ifndef MOD_INVERSE
#define MOD_INVERSE
#include <assert.h>
#include "gandalfr/math/integer/Bezout_coefficients.hpp"

template<typename T>
T mod_inverse(T x, T mod){
    assert(mod > 0);
    auto [a, b] = Bezout_coefficients(x, mod);
    assert(a * x + b * mod == 1);
    return (a >= 0 ? a : a + mod);
}

#endif