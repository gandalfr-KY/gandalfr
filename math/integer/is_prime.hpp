#ifndef IS_PRIME
#define IS_PRIME
#include <vector>

/* is_prime[n] := |n|が素数かどうか
 * 判定表をならし時間 O(NloglogN) で構成して判定
 */
class {
  private:
    std::vector<bool> table = {false, false};

    // table のサイズをnxtに拡張 (= nxt - 1 まで判定可能にする)
    void expand(int nxt){
        int cur = table.size();
        table.resize(nxt, true);
        for(int i=2; i<cur; i++){
            if(!table[i]) continue;
            int from = (cur + i - 1) / i * i;
            for(int j=from; j<nxt; j+=i) table[j] = false;
        }
    }

  public:
    bool operator()(int n){
        if(n < 0) n *= -1;
        while(n >= table.size()) { expand(table.size() * 2); } 
        return table[n];
    }
    
} static is_prime;

#endif