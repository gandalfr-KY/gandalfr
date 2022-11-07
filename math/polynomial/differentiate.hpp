#ifndef DIFFERENTIATE
#define DIFFERENTIATE
#include "gandalfr/math/polynomial/polynomial.hpp"

template<class T>
polynomial<T> differentiate(polynomial<T> a){
    polynomial<T> ret;
    for(int i=0; i<a.max_order(); i++){
        ret.set_coefficient(i, a.get_coefficient(i + 1) * (i + 1));
    }
    return ret;
}

#endif