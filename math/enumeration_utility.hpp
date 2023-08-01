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

template <class T> class factorial {
  private:
    static inline std::vector<T> fact{1};

  public:
    factorial() = delete;
    ~factorial() = delete;
    static T get(int n) {
        while (n >= fact.size())
            fact.push_back(fact.back() * fact.size());
        return fact[n];
    }
};

template <class T> struct permutation {
    permutation() = delete;
    ~permutation() = delete;
    static T get(int n, int k) {
        assert(0 <= k && k <= n);
        return factorial<T>::get(n) / factorial<T>::get(n - k);
    }
};

template <class T> struct combination {
    combination() = delete;
    ~combination() = delete;
    static T get(int n, int k) {
        assert(0 <= k && k <= n);
        return factorial<T>::get(n) /
               (factorial<T>::get(k) * factorial<T>::get(n - k));
    }
};

using fact = factorial<mint>;
using _fact = factorial<_mint>;
using perm = permutation<mint>;
using _perm = permutation<_mint>;
using comb = combination<mint>;
using _comb = combination<_mint>;
