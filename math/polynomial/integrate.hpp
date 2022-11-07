#ifndef INTEGRATE
#define INTEGRATE
#include "gandalfr/math/polynomial/polynomial.hpp"

template<class T>
polynomial<T> integrate(polynomial<T> a){
    polynomial<T> ret;
    for(int i=1; i<=a.max_order()+1; i++){
        ret.set_coefficient(i, a.get_coefficient(i-1) / i);
    }
    return ret;
}

#endif