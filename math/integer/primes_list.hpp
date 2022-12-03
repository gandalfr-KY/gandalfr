#ifndef PRIMES_LIST
#define PRIMES_LIST
#include <assert.h>
#include "gandalfr/math/integer/is_prime.hpp"

/* primes_list[n] := n番目の素数(n:0-indexed)
 * リストは必要に応じて自動的に拡張される
 */
class {
  private:
    std::vector<int> nums = {2};

    void expand(int nex){
        int i = nums.back() + 1;
        while(nums.size() < nex){
            if(is_prime(i)) nums.push_back(i);
            i++;
        }
    }

  public:
    int operator[](int n){
        assert(n >= 0);
        while(n >= nums.size()) { expand(nums.size() * 2); } 
        return nums[n];
    }

} static primes_list;

#endif