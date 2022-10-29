#ifndef MATRIX_POWER
#define MATRIX_POWER
#include "gandalfr/math/matrix/matrix.hpp"

template<class T>
matrix<T> matrix_power(matrix<T> x, long long n) {
    assert(x.size_H() == x.size_W());
    int H = x.size_H();
    matrix<T> ret(H, H);
    for(int i=0; i<H; i++) ret[i][i] = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

matrix<long long> matrix_power(matrix<long long> x, long long n, long long MOD) {
    assert(x.size_H() == x.size_W());
    int H = x.size_H();
    matrix<long long> ret(H, H);
    for(int i=0; i<H; i++) ret[i][i] = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

#endif