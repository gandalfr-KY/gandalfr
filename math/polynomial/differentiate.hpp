#ifndef DIFFERENTIATE
#define DIFFERENTIATE
#include "gandalfr/math/polynomial/polynomial.hpp"

polynomial differentiate(polynomial a){
    polynomial ret;
    for(int i=0; i<a.max_order(); i++){
        ret.set(i, a.get(i + 1) * (i + 1));
    }
    return ret;
}

#endif