#pragma once
#include <array>
#include <vector>

#include "../standard/Mint.hpp"
#include "../types.hpp"
#include "atcoder/math.hpp"

namespace gandalfr {

template <i32 m> struct CombinatoricsUtility {
  private:
    static inline std::vector<Mint<m>> fact{1, 1}, invmod{0, 1}, invfact{1, 1};
    template <i32 b> static inline std::vector<Mint<m>> pows{1};

    static std::tuple<Mint<m>, Mint<m>, Mint<m>> get(i32 n) {
        while (n >= (i32)fact.size()) {
            i32 s = fact.size();
            auto [dv, md] = std::div(m, s);
            fact.push_back(fact[s - 1] * s);
            invmod.push_back(-invmod[md] * dv);
            invfact.push_back(invfact[s - 1] * invmod[s]);
        }
        return std::make_tuple(fact[n], invmod[n], invfact[n]);
    }

  public:
    CombinatoricsUtility() = delete;
    ~CombinatoricsUtility() = delete;

    static Mint<m> factorial(i32 n) { return std::get<0>(get(n)); }

    static Mint<m> invMod(i32 n) { return std::get<1>(get(n)); }

    static Mint<m> invFactorial(i32 n) { return std::get<2>(get(n)); }

    static Mint<m> permutation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return factorial(n) * invFactorial(n - k);
    }

    static Mint<m> combnation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return factorial(n) * invFactorial(k) * invFactorial(n - k);
    }

    // n 種から重複を許して k 個選ぶ
    static Mint<m> homogeneous(i32 n, i32 k) {
        return combnation(n + k - 1, k);
    }

    template <i32 b> static Mint<m> powMod(i32 n) {
        while (n >= (i32)pows<b>.size()) {
            pows<b>.push_back(pows<b>.back() * b);
        }
        return pows<b>[n];
    }
};

Mint107 (*fact107)(i32) = CombinatoricsUtility<MOD107>::factorial;
Mint998 (*fact998)(i32) = CombinatoricsUtility<MOD998>::factorial;
Mint107 (*invFact107)(i32) = CombinatoricsUtility<MOD107>::invFactorial;
Mint998 (*invFact998)(i32) = CombinatoricsUtility<MOD998>::invFactorial;
Mint107 (*perm107)(i32, i32) = CombinatoricsUtility<MOD107>::permutation;
Mint998 (*perm998)(i32, i32) = CombinatoricsUtility<MOD998>::permutation;
Mint107 (*comb107)(i32, i32) = CombinatoricsUtility<MOD107>::combnation;
Mint998 (*comb998)(i32, i32) = CombinatoricsUtility<MOD998>::combnation;
Mint107 (*homo107)(i32, i32) = CombinatoricsUtility<MOD107>::homogeneous;
Mint998 (*homo998)(i32, i32) = CombinatoricsUtility<MOD998>::homogeneous;
Mint107 (*inv107)(i32) = CombinatoricsUtility<MOD107>::invMod;
Mint998 (*inv998)(i32) = CombinatoricsUtility<MOD998>::invMod;
template <i32 b>
Mint998 (*powMod998)(i32) = CombinatoricsUtility<MOD998>::powMod<b>;
template <i32 b>
Mint107 (*powMod107)(i32) = CombinatoricsUtility<MOD107>::powMod<b>;
template <i32 m> Mint<m> (*fact)(i32) = CombinatoricsUtility<m>::factorial;
template <i32 m>
Mint<m> (*invFact)(i32) = CombinatoricsUtility<m>::invFactorial;
template <i32 m>
Mint<m> (*perm)(i32, i32) = CombinatoricsUtility<m>::permutation;
template <i32 m>
Mint<m> (*comb)(i32, i32) = CombinatoricsUtility<m>::combnation;
template <i32 m>
Mint<m> (*homo)(i32, i32) = CombinatoricsUtility<m>::homogeneous;
template <i32 m> Mint<m> (*inv)(i32) = CombinatoricsUtility<m>::invMod;
template <i32 m, i32 b>
Mint<m> (*powMod)(i32) = CombinatoricsUtility<m>::template powMod<b>;
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

struct Factor {
    i64 factor;
    i32 exponent;
};

namespace internal {

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
} // namespace internal

// 素数篩を固定サイズで構築する。篩のサイズが (2^23) でおよそ 0.5sかかる
class Seive {
  private:
    static inline std::vector<i32> primes{2}, min_factor{0, 1};

    static std::vector<Factor> osak(i64 n) {
        std::vector<Factor> ret{{0, 0}};
        while (n > 1) {
            if (ret.back().factor != min_factor[n]) {
                ret.emplace_back(Factor{min_factor[n], 1});
            } else {
                ret.back().exponent++;
            }
            n /= min_factor[n];
        }
        return {ret.begin() + 1, ret.end()};
    }

    static std::vector<Factor> naiveFactorize(i64 n) {
        std::vector<Factor> ret{{0, 0}};
        for (i64 p : primes) {
            if (n == 1 || p * p > n)
                break;
            while (n % p == 0) {
                if (ret.back().factor != p)
                    ret.emplace_back(Factor{p, 1});
                else
                    ret.back().exponent++;
                n /= p;
            }
        }
        if (n != 1)
            ret.push_back({n, 1});
        return {ret.begin() + 1, ret.end()};
    }

    static void divisors_impl(u32 f_idx, i64 n, std::vector<i64> &ds,
                              const std::vector<Factor> &fs) {
        if (f_idx == fs.size()) {
            ds.push_back(n);
            return;
        }
        for (i32 i = 0; i <= fs[f_idx].exponent; ++i) {
            divisors_impl(f_idx + 1, n, ds, fs);
            n *= fs[f_idx].factor;
        }
    }

  public:
    Seive() = delete;
    ~Seive() = delete;

    static i32 size() { return min_factor.size(); }

    // 必ず最初に呼ぶ　
    static void makeTable(i32 sieve_size = 1 << 23) {
        min_factor.assign(sieve_size, 1);
        primes.push_back(2);
        for (i32 i = 2; i < sieve_size; i += 2)
            min_factor[i] = 2;
        for (i32 i = 3; i < sieve_size; i += 2) {
            if (min_factor[i] != 1)
                continue;
            min_factor[i] = i;
            primes.push_back(i);
            for (i32 j = i * 2; j < sieve_size; j += i) {
                if (min_factor[j] == 1)
                    min_factor[j] = i;
            }
        }
    }

    /**
     * @brief n が素数かを判定
     */
    static bool isPrime(i64 n) {
        assert(n < (i64)size());
        if (n < 2 || (n & 1) == 0) {
            return false;
        } else if (n < size()) {
            return min_factor[n] == n;
        } else if (n < 4759123141) {
            return internal::MillerRabin(n, {2, 7, 61});
        } else {
            return internal::MillerRabin(
                n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
        }
    }

    /**
     * @brief 素因数分解する
     * @return factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...},
     * @return factorize(1) => {}
     */
    static std::vector<Factor> factorize(i64 n) {
        assert((i64)primes.back() * primes.back() >= n);
        if (n < size())
            return osak(n);
        else
            return naiveFactorize(n);
    }

    static std::vector<i64> divisors(i64 n) {
        std::vector<i64> ds;
        divisors_impl(0, 1, ds, factorize(n));
        std::sort(ds.begin(), ds.end());
        return ds;
    }

    // 1..n で n と co-prime な数の個数
    static i64 totient(i64 n) {
        i64 ret = 1;
        for (auto [b, e] : factorize(n))
            ret *= power(b, e - 1) * (b - 1);
        return ret;
    }

    static i32 nthPrime(i32 n) { return primes.at(n); }
};

} // namespace gandalfr
