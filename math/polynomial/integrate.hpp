#ifndef INTEGRATE
#define INTEGRATE
#include "gandalfr/math/polynomial/polynomial.hpp"

polynomial integrate(polynomial a){
    polynomial ret;
    for(int i=1; i<=a.max_order()+1; i++){
        ret.set(i, a.get(i-1) / i);
    }
    return ret;
}

#endif