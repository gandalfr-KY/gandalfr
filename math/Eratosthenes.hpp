#pragma once
#include <assert.h>
#include <math.h>

#include <vector>

#include "atcoder/math.hpp"
#include "utility.hpp"

namespace gandalfr {

namespace impl {

/**
 * @see https://drken1215.hatenablog.com/entry/2023/05/23/233000
 */
bool MillerRabin(i64 N, const std::vector<i64> &A) {
    i64 s = 0, d = N - 1;
    while (d % 2 == 0) {
        ++s;
        d >>= 1;
    }
    for (auto a : A) {
        if (N <= a)
            return true;
        i64 t, x = atcoder::pow_mod(a, d, N);
        if (x != 1) {
            for (t = 0; t < s; ++t) {
                if (x == N - 1)
                    break;
                x = (__int128_t)x * x % N;
            }
            if (t == s)
                return false;
        }
    }
    return true;
}
}


// 素数篩を固定サイズで構築する。篩のサイズが (2^23) でおよそ 0.5sかかる
// set_seive_size を最初に呼ぶとサイズを変更できる
class Seive {
  protected:
    static inline i32 seive_size = (1 << 23);
    static inline std::vector<bool> sieve;
    static inline std::vector<i32> primes{2, 3}, movius, min_factor;

    static void makeTable() {
        sieve.assign(seive_size, true);
        sieve[0] = sieve[1] = false;
        movius.assign(seive_size, 1);
        min_factor.assign(seive_size, 1);
        for (i32 i = 2; i <= seive_size; ++i) {
            if (!sieve[i])
                continue;
            movius[i] = -1;
            min_factor[i] = i;
            primes.push_back(i);
            for (i32 j = i * 2; j < seive_size; j += i) {
                sieve[j] = false;
                movius[j] = ((j / i) % i == 0 ? 0 : -movius[j]);
                if (min_factor[j] == 1)
                    min_factor[j] = i;
            }
        }
    }

    static std::vector<std::pair<i64, i32>> fastFactorize(i64 n) {
        std::vector<std::pair<i64, i32>> ret;
        while (n > 1) {
            if (ret.empty() || ret.back().first != min_factor[n]) {
                ret.push_back({min_factor[n], 1});
            } else {
                ret.back().second++;
            }
            n /= min_factor[n];
        }
        return ret;
    }

    static std::vector<std::pair<i64, i32>> naiveFactorize(i64 n) {
        std::vector<std::pair<i64, i32>> ret;
        for (i64 p : primes) {
            if (n == 1 || p * p > n)
                break;
            while (n % p == 0) {
                if (ret.empty() || ret.back().first != p)
                    ret.push_back({p, 1});
                else
                    ret.back().second++;
                n /= p;
            }
        }
        if (n != 1)
            ret.push_back({n, 1});
        return ret;
    }

  public:
    Seive() = delete;
    ~Seive() = delete;

    static void setInitSize(i32 size) {
        assert(sieve.empty());
        seive_size = size;
    }

    /**
     * @brief n が素数かを判定
     */
    static bool isPrime(i64 n) {
        if (sieve.empty())
            makeTable();
        assert(1 <= n);

        if (n > 2 && (n & 1LL) == 0) {
            return false;
        } else if (n < seive_size) {
            return sieve[n];
        } else if (n < 4759123141LL) {
            return impl::MillerRabin(n, {2, 7, 61});
        } else {
            return impl::MillerRabin(
                n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
        }
    }

    /**
     * @brief 素因数分解する
     * @return factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...},
     * @return factorize(1) => {}
     */
    static std::vector<std::pair<i64, i32>> factorize(i64 n) {
        if (sieve.empty())
            makeTable();
        assert(1 <= n);

        if (n < seive_size) {
            return fastFactorize(n);
        } else {
            return naiveFactorize(n);
        }
    }

    static i32 movius(i32 n) {
        if (movius.empty())
            makeTable();
        assert(1 <= n);
        return movius.at(n);
    }

    /**
     * @brief 約数列挙
     * @attention if n < sieve_size : O(N^(1/loglogN))
     */
    template <bool sort = true>
    static std::vector<i64> divisors(i64 n) {
        std::vector<i64> ds;
        auto facs(factorize(n));
        auto rec = [&](auto self, i64 d, i32 cu) -> void {
            if (cu == (i32)facs.size()) {
                ds.push_back(d);
                return;
            }
            for (i32 e = 0; e <= facs[cu].second; ++e) {
                self(self, d, cu + 1);
                d *= facs[cu].first;
            }
        };
        rec(rec, 1LL, 0);
        if constexpr (sort)
            std::sort(ds.begin(), ds.end());
        return ds;
        ;
    }

    /**
     * @brief オイラーのトーシェント関数
     */
    static i64 totient(i64 n) {
        i64 ret = 1;
        for (auto [b, e] : factorize(n))
            ret *= power(b, e - 1) * (b - 1);
        return ret;
    }

    static i32 nthPrime(i32 n) { return primes.at(n); }
};
} // namespace gandalfr
