#ifndef MOD_INVERSE
#define MOD_INVERSE
#include <assert.h>
#include "gandalfr/math/integer/Bezout_coefficients.hpp"

template<class T>
T mod_inverse(T x, T mod){
    T s, t;
    assert(mod > 0);
    assert(_extgcd((x >= 0 ? x : -x), mod, s, t) == 1);
    if(x < 0) s = -s;
    if(s < 0) s += mod;
    return s;
}

#endif