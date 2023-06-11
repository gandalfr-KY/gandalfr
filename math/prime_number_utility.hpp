#ifndef PRIME_NUMBER_UTILITY
#define PRIME_NUMBER_UTILITY
#include <vector>
#include <math.h>

/* is_prime::judge(n) := |n|が素数かどうか
 * 判定表をならし時間 O(NloglogN) で構成して判定
 */
class prime_number_utility{
  protected:
    static bool has_table_made;
    static std::vector<bool> sieve;
    static const int sieve_size = (1 << 18);

  public:
    prime_number_utility() = delete;
    ~prime_number_utility() = delete;

    static bool is_prime(long long n){
        if(!has_table_made){
            sieve.assign(sieve_size, true);
            sieve[0] = sieve[1] = false;
            sieve[2] = true;
            for(int i = 4; i < sieve_size; i += 2) sieve[i] = false;
            int sqrt_size = ceil(std::sqrt(sieve_size)) + 1;
            for(int i = 3; i <= sqrt_size; i += 2){
                if(!sieve[i]) continue;
                for(int j = i * 2; j < sieve_size; j += i) sieve[j] = false;
            }
            has_table_made = true;
        }
        if(n < 0) n *= -1;
        if(n < sieve_size) return sieve[n];
        
        long long sqrt_n = ceil(std::sqrt(n)) + 1;
        if(n % 2 == 0) return false;
        for(long long i = 3; i <= sqrt_n; i += 2){
            if(!sieve[i]) continue;
            if(n % i == 0) return false;
        }
        return true;
    }

    static const std::vector<bool> &table(){ return sieve; }
};
std::vector<bool> prime_number_utility::sieve;
bool prime_number_utility::has_table_made = false;


#endif