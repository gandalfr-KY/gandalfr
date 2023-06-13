#ifndef PRIME_NUMBER_UTILITY
#define PRIME_NUMBER_UTILITY
#include <vector>
#include <math.h>

/* is_prime::judge(n) := |n|が素数かどうか
 * 判定表をならし時間 O(NloglogN) で構成して判定
 */
class prime_number_utility{
  protected:
    static const int init_seive_size = (1 << 24), sqrt_size = (1 << 12);
    static inline std::vector<bool> sieve;

  public:
    prime_number_utility() = delete;
    ~prime_number_utility() = delete;

    static bool is_prime(long long n) {
        if(sieve.empty()){ // 篩が未構築なら
            sieve.assign(init_seive_size, true);
            sieve[0] = sieve[1] = false;
            for(int i = 4; i < init_seive_size; i += 2) sieve[i] = false;
            for(int i = 3; i <= sqrt_size; i += 2) {
                if(!sieve[i]) continue;
                for(int j = i * 2; j < init_seive_size; j += i) sieve[j] = false;
            }
        }

        // n が小さいとき、篩を参照
        if(n < init_seive_size) return sieve[n];
        if((n & 1) == 0) return 0;
        // n が大きいとき、O(√n) 試し割りで計算
        long long sqrt_n = std::ceil(std::sqrt(n)) + 1;
        for(long long i = 3; i <= sqrt_n; i += 2) {
            if(!sieve[i]) continue;
            if(n % i == 0) return false;
        }
        return true;
    }

    static const std::vector<bool> &table(){ return sieve; }
};


#endif