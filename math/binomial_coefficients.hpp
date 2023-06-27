#pragma once
#include <vector>
#include <map>

#include "../standard/mod_integer.hpp"

template <class T> class binomial_coefficients {
  private:
    static inline std::vector<T> fact;

    static void expand(int n) {
        while (n >= fact.size()) {
            fact.push_back(fact.back() * fact.size());
        }
    }

  public:
    binomial_coefficients() = delete;
    ~binomial_coefficients() = delete;

    static T get(int n, int k) {
        assert(0 <= k && k <= n);
        if (n >= fact.size())
            expand(n);
        return fact[n] / fact[k] / fact[n - k];
    }
};

using binom = binomial_coefficients<mint>;
using _binom = binomial_coefficients<_mint>;