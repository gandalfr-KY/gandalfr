#ifndef BEZOUT_COEFFICIENTS
#define BEZOUT_COEFFICIENTS
#include <utility>
#include "gandalfr/standard/gcdlcm.hpp"

template<class T>
std::pair<T, T> Bezout_coefficients(T a, T b){
    T s, t;
    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);
    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};
}

#endif