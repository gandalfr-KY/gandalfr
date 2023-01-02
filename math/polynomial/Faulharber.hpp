#ifndef FAULHARBER
#define FAULHARBER
#include "gandalfr/math/polynomial/polynomial.hpp"
#include "gandalfr/math/integer/Bernoulli_number.hpp"

template<class T>
class Faulharber {
  public:
    std::vector<polynomial<T>> result;

  public:

    // ΣP(x) (= P(1) + P(2) + ... + P(x)) を返す
    polynomial<T> get(const polynomial<T> &a){
        if(a.max_order() + 1 >= result.size()){
            result.resize(a.max_order() + 2);
            for(int n=0; n<=a.max_order(); n++){
                for(int i=0; i<=n; i++){
                    result[n].set_coefficient(n - i + 1, binomial_coefficients<T>::get(n + 1, i) / (n + 1) * Bernoulli_number<T>::get(i));
                }
            }
        }

        polynomial<T> ret = 0;
        for(int i=0; i<=a.max_order(); i++) ret += result[i] * (polynomial<T>)a.get_coefficient(i);
        return ret;
    }
};

#endif