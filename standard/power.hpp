#ifndef POWER
#define POWER
#include <assert.h>
#include "gandalfr/math/matrix/matrix.hpp"

template<class T>
T power(T x, long long n) {
    T ret = T(1);
    while (n > 0) {
        if (n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

long long power(long long x, long long n) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

long long power(long long x, long long n, long long MOD) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

template<class T>
matrix<T> power(matrix<T> x, long long n) {
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

matrix<long long> power(matrix<long long> x, long long n, long long MOD) {
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