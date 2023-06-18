#pragma once
#include <vector>

#include "mod_inverse.hpp"

/*
 * O(N)
 * from : https://kopricky.github.io/code/Computation_Advanced/garner.html
 */
long long Garner(std::vector<long long> a, std::vector<long long> p,
                 const int mod) {
    for (long long &x : a)
        x %= mod;
    int sz = a.size();
    std::vector<long long> kp(sz + 1, 0), rmult(sz + 1, 1);
    p.push_back(mod);
    for (int i = 0; i < sz; ++i) {
        long long x = (a[i] - kp[i]) * mod_inverse(rmult[i], p[i]) % p[i];
        x = (x < 0) ? (x + p[i]) : x;
        for (int j = i + 1; j < sz + 1; ++j) {
            kp[j] = (kp[j] + rmult[j] * x) % p[j];
            rmult[j] = rmult[j] * p[i] % p[j];
        }
    }
    return kp[sz];
}
