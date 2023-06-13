#ifndef PRIME_NUMBER_LIST
#define PRIME_NUMBER_LIST
#include <assert.h>
#include "prime_number_utility.hpp"

// 昇順の素数リスト
class prime_number_list{
protected:
    static inline std::vector<int> primes{2, 3};

public:
    prime_number_list() = delete;
    ~prime_number_list() = delete;

    static void reserve(int siz){
        for(int i = primes.back() + 2; (int)primes.size() < siz; i += 2){
            if(prime_number_utility::is_prime(i)) primes.push_back(i);
        }
    }

	// primes.back() が lim を超えるまで拡張
	static void set_minimum_limit(int lim){
		while(primes.back() < lim) reserve(primes.size() + 1);
	}

    static const std::vector<int> &list(){ return primes; }
};

#endif