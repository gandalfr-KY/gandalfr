#ifndef BEZOUT_COEFFICIENTS
#define BEZOUT_COEFFICIENTS
#include <utility>
#include <cstdlib>

long long _extgcd(long long a, long long b, long long &s, long long &t){
    if(b == 0){
        s = 1;
        t = 0;
        return a;
    }
    else{
        auto d = std::lldiv(a, b);
        long long tmp = _extgcd(b, d.rem, t, s);
        t -= d.quot * s;
        return tmp;
    }
}

std::pair<long long, long long> Bezout_coefficients(long long a, long long b){
    long long s, t;
    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);
    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};
}

#endif