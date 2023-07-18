#pragma once
#include <algorithm>
#include <assert.h>

inline long long mod_inverse(long long a, int mod) {
    assert(mod > 0);
    long long b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b, std::swap(a, b);
        u -= t * v, std::swap(u, v);
    }
    u %= mod;
    if (u < 0)
        u += mod;
    return u;
}
