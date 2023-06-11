#ifndef BINOMIAL_COEFFICIENTS
#define BINOMIAL_COEFFICIENTS
#include <vector>

template<class T>
class binomial_coefficients{
  private:
    static std::vector<T> fact;

    static void expand(int n){
		while(n >= fact.size()) {
            fact.push_back(fact.back() * fact.size());
        }
    }

  public:
    binomial_coefficients() = delete;
    ~binomial_coefficients() = delete;

    static T get(int n, int k){
		    assert(0 <= k && k <= n);
        if(n >= fact.size()) expand(n);
        return fact[n] / fact[k] / fact[n - k];
    }

};
template<class T>
std::vector<T> binomial_coefficients<T>::fact = {1};

#endif