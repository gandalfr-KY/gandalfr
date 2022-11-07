#ifndef BERNOULLI_NUMBER
#define BERNOULLI_NUMBER
#include "gandalfr/standard/power.hpp"
#include "gandalfr/math/integer/binomial_coefficients.hpp"
#include "gandalfr/math/integer/mod_inverse.hpp"

/* Bernoulli_number<value_type> B;
 * B(n) := ベルヌーイ数の第n項
 */
template<class T>
class Bernoulli_number : protected binomial_coefficients<T>{
  private:
    std::vector<T> B = {1, (T)1 / 2};

    // テ－ブルを長さ n + 1 まで拡張 ( = B[n] にアクセスできるようにする)
    void expand(int n){
        B.reserve(n + 1);
        for(int m=B.size(); m<=n; m++){
            if(m % 2 == 1) B.emplace_back(0);
            else{
                T res = 0;
                for(int i=0; i<=n; i++){
                    T tmp = 0;
                    for(int j=i; j<=n; j++) tmp += binomial_coefficients<T>::get(j, i) / (j + 1);
                    if(i % 2 == 0) res += tmp * power<T>(i, n);
                    else           res -= tmp * power<T>(i, n);
                }
                B.emplace_back(res);
            }   
        }
    }

  protected:
    T get(int n){
        if(n >= B.size()) expand(n);
        return B[n];
    }

  public:
    T operator()(int n){
        assert(n >= 0);
        return get(n);
    }
    
};

#endif