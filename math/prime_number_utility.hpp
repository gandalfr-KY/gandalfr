#pragma once
#include <math.h>

#include <vector>

/**
 * @brief 素数判定や列挙をサポートするクラス
 * @brief 素数篩を固定サイズで構築、それをもとに素数列挙などを行う
 */
class prime_number_utility {
  protected:
    static const int init_seive_size = (1 << 26), sqrt_size = (1 << 13);
    static inline std::vector<bool> sieve;
    static inline std::vector<int> primes{2, 3};

  public:
    prime_number_utility() = delete;
    ~prime_number_utility() = delete;

    /**
     * @brief n が素数かを判定
     * @attention if n < (1 << 26) : O(1)
     * @attention else : O(√n)
     */
    static bool is_prime(long long n) {
        if (sieve.empty()) { // 篩が未構築なら
            sieve.assign(init_seive_size, true);
            sieve[0] = sieve[1] = false;
            for (int i = 4; i < init_seive_size; i += 2)
                sieve[i] = false;
            for (int i = 3; i <= sqrt_size; i += 2) {
                if (!sieve[i])
                    continue;
                for (int j = i * 2; j < init_seive_size; j += i)
                    sieve[j] = false;
            }
        }
        if ((n & 1) == 0)
            return 0;
        // n が小さいとき、篩を参照
        if (n < init_seive_size)
            return sieve[n];
        // n が大きいとき、O(√n) 試し割りで計算
        long long sqrt_n = std::ceil(std::sqrt(n)) + 1;
        for (long long i = 3; i <= sqrt_n; i += 2) {
            if (!sieve[i])
                continue;
            if (n % i == 0)
                return false;
        }
        return true;
    }

    static void expand_list(int siz) {
        for (int i = primes.back() + 2; (int)primes.size() < siz; i += 2) {
            if (is_prime(i))
                primes.push_back(i);
        }
    }

    // 素数のリストを、末尾の数が lim を超えるまで拡張
    static void set_lower_limit(int lim) {
        while (primes.back() < lim)
            expand_list(primes.size() + 1);
    }

    /**
     * @brief 素因数分解する
     * @return prime_factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...}
     * @attention prime_factorize(1) => {}
     * @attention prime_factorize(0) => {{0, 1}}
     */
    static std::vector<std::pair<long long, int>> factorize(long long N) {
        std::vector<std::pair<long long, int>> ret;
        set_lower_limit(ceil(sqrt(N)));
        for (long long p : primes) {
            if (N == 1 || (__int128_t)p * p > N)
                break;
            while (N % p == 0) {
                if (ret.empty() || ret.back().first != p)
                    ret.push_back({p, 1});
                else
                    ret.back().second++;
                N /= p;
            }
        }
        if (N != 1)
            ret.push_back({N, 1});
        return ret;
    }

    static const std::vector<int> &list() { return primes; }
    static const std::vector<bool> &table() { return sieve; }
};
