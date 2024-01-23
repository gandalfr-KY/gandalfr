#pragma once
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#include "Mint.hpp"
#include "formal_power_series.hpp"

namespace gandalfr {

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

template <int m> class factorial {
  private:
    static inline std::vector<atcoder::static_modint<m>> fact{1};

  public:
    factorial() = delete;
    ~factorial() = delete;
    static atcoder::static_modint<m> get(int n) {
        while (n >= (int)fact.size()) {
            fact.push_back(fact.back() * fact.size());
            return fact[n];
        }
    };
    atcoder::modint1000000007 (*fact1000000007)(int) = factorial<MOD107>::get;
    atcoder::modint998244353 (*fact998244353)(int) = factorial<998244353>::get;

    template <int m>
    static atcoder::static_modint<m> permutation(int n, int k) {
        assert(0 <= k && k <= n);
        return factorial<m>::get(n) / factorial<m>::get(n - k);
    }
    atcoder::modint1000000007 (*perm1000000007)(int, int) = permutation<MOD107>;
    atcoder::modint998244353 (*perm998244353)(int,
                                              int) = permutation<998244353>;

    template <int m> static atcoder::static_modint<m> combnation(int n, int k) {
        assert(0 <= k && k <= n);
        return factorial<m>::get(n) /
               (factorial<m>::get(k) * factorial<m>::get(n - k));
    }
    atcoder::modint1000000007 (*comb1000000007)(int, int) = combnation<MOD107>;
    atcoder::modint998244353 (*comb998244353)(int, int) = combnation<998244353>;

    template <int m>
    static FormalPowerSeries<atcoder::static_modint<m>>
    Bernoulli_number(int n) {
        assert(0 <= n);
        FormalPowerSeries<atcoder::static_modint<m>> F(n, 0);
        F[0] = 1;
        for (int i = 1; i < n; ++i) {
            F[i] = F[i - 1] / (i + 1);
        }
        F = F.inv();
        for (int i = 0; i < n; ++i) {
            F[i] *= factorial<m>::get(i);
        }
        return F;
    }
    FormalPowerSeries<atcoder::modint998244353> (*Bernoulli998244353)(int) =
        Bernoulli_number<998244353>;
}
} // namespace gandalfr
