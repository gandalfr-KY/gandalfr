#ifndef BERNOULLI_NUMBER
#define BERNOULLI_NUMBER
#include "gandalfr/standard/power.hpp"
#include "gandalfr/math/integer/binomial_coefficients.hpp"
#include "gandalfr/math/integer/mod_inverse.hpp"

template<int mod>
class Bernoulli_number{
  public:
    Bernoulli_number(){}

    const long long &operator()(int n){
        if(n >= Bernoulli.size()){
            Bernoulli.reserve(n + 1);
            for(int m=Bernoulli.size(); m<=n; m++){
                if(m % 2 == 1) Bernoulli.emplace_back(0);
                else{
                    long long res = 0;
                    for(int i=0; i<=n; i++){
                        long long tmp = 0;
                        for(int j=i; j<=n; j++) tmp = (tmp + nCk(j, i) * mod_inverse(j + 1, mod)) % mod;
                        if(i % 2 == 0) res += tmp * power(i, n, mod);
                        else           res -= tmp * power(i, n, mod);
                        res %= mod;
                        if(res < 0) res += mod;
                    }
                    Bernoulli.emplace_back(res);
                }   
            }
        }
        return Bernoulli[n];
    }

  private:
    std::vector<long long> Bernoulli = {1, mod_inverse(2, mod)};
    binomial_coefficients<mod> nCk;
    
};

#endif