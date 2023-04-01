#ifndef BEZOUT_COEFFICIENTS
#define BEZOUT_COEFFICIENTS
#include <utility>

template<class T>
T _extgcd(T a, T b, T &s, T &t){
    if(b == 0){
        s = 1;
        t = 0;
        return a;
    }
    else{
        T tmp = _extgcd<T>(b, a % b, t, s);
        t -= a / b * s;
        return tmp;
    }
}

template<class T>
std::pair<T, T> Bezout_coefficients(T a, T b){
    T s, t;
    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);
    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};
}

#endif