#ifndef IS_PRIME
#define IS_PRIME
#include <vector>

/* is_prime::judge(n) := |n|が素数かどうか
 * 判定表をならし時間 O(NloglogN) で構成して判定
 */

class is_prime{
  protected:
    static std::vector<bool> sieve;

  private:
    // sieve のサイズをnxtに拡張 (= nxt - 1 まで判定可能にする)
    static void expand(int nxt){
        int cur = sieve.size();
        sieve.resize(nxt, true);

        for(int i=2; i<=(cur>>1); i++){
            if(!sieve[i]) continue;
            int from = (cur + i - 1) / i * i;
            for(int j=from; j<nxt; j+=i) sieve[j] = false;
        }
    }

  public:
    is_prime() = delete;
    ~is_prime() = delete;

    static bool judge(int n){
        if(n < 0) n *= -1;
        while(n >= sieve.size()) { expand(sieve.size() * 2); } 
        return sieve[n];
    }

    static const std::vector<bool> &table(){ return sieve; }
};
std::vector<bool> is_prime::sieve = {false, false};


#endif