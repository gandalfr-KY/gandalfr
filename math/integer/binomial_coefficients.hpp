#ifndef BINOMIAL_COEFFICIENTS
#define BINOMIAL_COEFFICIENTS
#include <vector>

template<class T>
class binomial_coefficients{
  public:
    std::vector<T> fact = {1,1};

    // テーブルを n+1 行まで拡張 ( = pascal[n][k] にアクセスできるようにする)
    void expand(int n){
		while(n >= fact.size()) fact.push_back(fact.back() * fact.size());
    }

  protected:
    T get(int n, int k){
        if(n >= fact.size()) expand(n);
        return fact[n] / fact[k] / fact[n - k];
    }

  public:
    T operator()(int n, int k){
        assert(0 <= k && k <= n);
		return get(n, k);
    }
};

#endif