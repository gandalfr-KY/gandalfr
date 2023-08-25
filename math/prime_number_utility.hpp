#pragma once
#include <assert.h>
#include <math.h>

#include <vector>

#include "enumeration_utility.hpp"

/**
 * @see https://drken1215.hatenablog.com/entry/2023/05/23/233000
 */
bool MillerRabin(long long N, const std::vector<long long> &A) {
    long long s = 0, d = N - 1;
    while (d % 2 == 0) {
        ++s;
        d >>= 1;
    }
    for (auto a : A) {
        if (N <= a)
            return true;
        long long t, x = power(a, d, N);
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

/**
 * @brief 素数判定や列挙をサポートするクラス
 * @brief 素数篩を固定サイズで構築、それをもとに素数列挙などを行う
 */
class Eratosthenes {
  protected:
    static inline int seive_size = (1 << 24);
    static inline std::vector<bool> sieve;
    static inline std::vector<int> primes{2, 3}, movius, min_factor;

    static void make_table() {
        sieve.assign(seive_size, true);
        sieve[0] = sieve[1] = false;
        movius.assign(seive_size, 1);
        min_factor.assign(seive_size, 1);
        for (int i = 2; i <= seive_size; ++i) {
            if (!sieve[i])
                continue;
            movius[i] = -1;
            min_factor[i] = i;
            primes.push_back(i);
            for (int j = i * 2; j < seive_size; j += i) {
                sieve[j] = false;
                movius[j] = ((j / i) % i == 0 ? 0 : -movius[j]);
                if (min_factor[j] == 1)
                    min_factor[j] = i;
            }
        }
    }

    static std::vector<std::pair<long long, int>> fast_factorize(long long n) {
        std::vector<std::pair<long long, int>> ret;
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

    static std::vector<std::pair<long long, int>> naive_factorize(long long n) {
        std::vector<std::pair<long long, int>> ret;
        for (long long p : primes) {
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
    Eratosthenes() = delete;
    ~Eratosthenes() = delete;

    static void set_init_size(int size) {
        assert(sieve.empty());
        seive_size = size;
    }

    /**
     * @brief n が素数かを判定
     * @attention if n < (1 << 24) : O(1)
     * @attention else : O(log(N))
     */
    static bool is_prime(long long n) {
        if (sieve.empty())
            make_table();
        assert(1 <= n);

        if (n > 2 && (n & 1LL) == 0) {
            return false;
        } else if (n < seive_size) {
            return sieve[n];
        } else if (n < 4759123141LL) {
            return MillerRabin(n, {2, 7, 61});
        } else {
            return MillerRabin(
                n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
        }
    }

    /**
     * @brief 素因数分解する
     * @return factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...},
     * @return factorize(1) => {}
     * @attention if n < (1 << 24) : O(log(N))
     * @attention if n < (1 << 24) : O(N^(3/2))
     */
    static std::vector<std::pair<long long, int>> factorize(long long n) {
        if (sieve.empty())
            make_table();
        assert(1 <= n);

        if (n < seive_size) {
            return fast_factorize(n);
        } else {
            return naive_factorize(n);
        }
    }

    static int Movius(int n) {
        if (movius.empty())
            make_table();
        assert(1 <= n);
        return movius.at(n);
    }

    /**
     * @brief オイラーのトーシェント関数
     */
    static long long totient(long long n) {
        long long ret = 1;
        for (auto [b, e] : factorize(n))
            ret *= power(b, e - 1) * (b - 1);
        return ret;
    }


    static int kth_prime(int k) { return primes.at(k); }
};
