#ifndef FAULHARBER
#define FAULHARBER
#include "gandalfr/math/polynomial/polynomial.hpp"
#include "gandalfr/math/fraction/Bernoulli_number.hpp"

class Faulharber{
  public:
    std::vector<polynomial> result;

  public:
    Faulharber() {}

    polynomial operator()(polynomial &a){
        if(a.max_order() + 1 >= result.size()){
            result.resize(a.max_order() + 2);
            for(int n=0; n<=a.max_order(); n++){
                for(int i=0; i<=n; i++){
                    result[n].set(n - i + 1, (fraction)nCk_bint(n + 1, i) / (n + 1) * Bernoulli(i));
                }
            }
        }

        polynomial ret = 0;
        for(int i=0; i<=a.max_order(); i++) ret += result[i] * (polynomial)a.get(i);
        return ret;
    }
};

static Faulharber sigma;

#endif