#pragma once
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#include "../standard/mod_integer.hpp"

template <class T> T power(T x, long long n) {
    T ret = static_cast<T>(1);
    while (n > 0) {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

long long power(long long x, long long n) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

long long power(long long x, long long n, int MOD) {
    long long ret = 1;
    x %= MOD;
    while (n > 0) {
        if (n & 1)
            ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

long long power(long long x, long long n, long long MOD) {
    long long ret = 1;
    x %= MOD;
    while (n > 0) {
        if (n & 1)
            ret = (__int128_t)ret * x % MOD;
        x = (__int128_t)x * x % MOD;
        n >>= 1;
    }
    return ret;
}

template <class T> class factorial {
  private:
    static inline std::vector<T> fact{T(1)};

  public:
    factorial() = delete;
    ~factorial() = delete;
    static T get(int n) {
        while (n >= fact.size())
            fact.push_back(fact.back() * fact.size());
        return fact[n];
    }
};
mint (*fact)(int) = factorial<mint>::get;
_mint (*_fact)(int) = factorial<_mint>::get;

template <class T> T permutation(int n, int k) {
    assert(0 <= k && k <= n);
    return factorial<T>::get(n) / factorial<T>::get(n - k);
}
mint (*perm)(int, int) = permutation<mint>;
_mint (*_perm)(int, int) = permutation<_mint>;

template <class T> static T combnation(int n, int k) {
    assert(0 <= k && k <= n);
    return factorial<T>::get(n) /
           (factorial<T>::get(k) * factorial<T>::get(n - k));
}
mint (*comb)(int, int) = combnation<mint>;
_mint (*_comb)(int, int) = combnation<_mint>;
