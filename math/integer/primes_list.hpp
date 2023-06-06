#ifndef PRIMES_LIST
#define PRIMES_LIST
#include <assert.h>
#include "prime_number_utility.hpp"

// 昇順の素数リスト
class primes_list{
  protected:
    static std::vector<int> primes;

  private:
    static void expand(int nex){
        int i = (primes.empty() ? 2 : primes.back() + 1);
        while((int)primes.size() < nex){
            if(prime_number_utility::is_prime(i)) primes.push_back(i);
            i++;
        }
    }

  public:
    primes_list() = delete;
    ~primes_list() = delete;

	static void resize(int siz){
		if((int)primes.size() > siz){
			while(primes.size() - siz > 0){
				primes.pop_back();
			}
		}
		else{
			expand(siz);
		}
	}

	// primes.back() が lim を超えるまで拡張
	static void set_lower_limit(int lim){
		while(primes.empty() || primes.back() < lim){
			expand(primes.size() + 1);
		}
	}

    static const std::vector<int> &list(){ return primes; }
};
std::vector<int> primes_list::primes;

#endif