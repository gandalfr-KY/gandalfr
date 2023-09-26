#pragma once
#include <algorithm>
#include <vector>

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"

// https://web.archive.org/web/20220813112322/https://opt-cp.com/fps-implementation/#toc2
template<class T> struct FormalPowerSeries : public std::vector<T> {
    using std::vector<T>::vector;
    using std::vector<T>::operator=;
    using F = FormalPowerSeries;

    F operator-() const {
        F res(*this);
        for (auto &e : res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for (auto &e : *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (*this).size(), m = g.size();
        for(int i = 0; i < std::min(n, m); ++i) (*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (*this).size(), m = g.size();
        for(int i = 0; i < std::min(n, m); ++i) (*this)[i] -= g[i];
        return *this;
    }
    F &operator<<=(const int d) {
        int n = (*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
        return *this;
    }
    F &operator>>=(const int d) {
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + std::min(n, d));
        (*this).resize(n);
        return *this;
    }
    F inv(int d = -1) const {
        int n = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        if (d == -1) d = n;
        assert(d > 0);
        F res{(*this)[0].inv()};
        while (res.size() < d) {
        int m = size(res);
        F f(begin(*this), begin(*this) + std::min(n, 2*m));
        F r(res);
        f.resize(2*m), atcoder::internal::butterfly(f);
        r.resize(2*m), atcoder::internal::butterfly(r);
        for(int i = 0; i < 2 * m; ++i) f[i] *= r[i];
        atcoder::internal::butterfly_inv(f);
        f.erase(f.begin(), f.begin() + m);
        f.resize(2*m), atcoder::internal::butterfly(f);
        for(int i = 0; i < 2 * m; ++i) f[i] *= r[i];
        atcoder::internal::butterfly_inv(f);
        T iz = T(2*m).inv(); iz *= -iz;
        for(int i = 0; i < m; ++i) f[i] *= iz;
        res.insert(res.end(), f.begin(), f.begin() + m);
        }
        return {res.begin(), res.begin() + d};
    }

    // fast: FMT-friendly modulus only
    F &operator*=(const F &g) {
        int n = (*this).size();
        *this = convolution(*this, g);
        (*this).resize(n);
        return *this;
    }
    F &operator/=(const F &g) {
        int n = (*this).size();
        *this = convolution(*this, g.inv(n));
        (*this).resize(n);
        return *this;
    }

    // naive
    F &naive_mult(const F &g) {
        int n = (*this).size(), m = g.size();
        for(int i = n - 1; i >= 0; --i) {
        (*this)[i] *= g[0];
        for(int j = 1; j < std::min(i+1, m); ++j) (*this)[i] += (*this)[i-j] * g[j];
        }
        return *this;
    }
    F &naive_div(const F &g) {
        assert(g[0] != T(0));
        T ig0 = g[0].inv();
        int n = (*this).size(), m = g.size();
        for(int i = 0; i < n; ++i) {
        for(int j = 1; j < std::min(i+1, m); ++j) (*this)[i] -= (*this)[i-j] * g[j];
        (*this)[i] *= ig0;
        }
        return *this;
    }

    // sparse
    F &sparse_mult(const std::vector<std::pair<int, T>> &g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if (d == 0) g.erase(g.begin());
        else c = 0;
        for(int i = n - 1; i >= 0; --i) {
        (*this)[i] *= c;
        for (auto &[j, b] : g) {
            if (j > i) break;
            (*this)[i] += (*this)[i-j] * b;
        }
        }
        return *this;
    }
    F &sparse_div(const std::vector<std::pair<int, T>> &g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(d == 0 && c != T(0));
        T ic = c.inv();
        g.erase(g.begin());
        for(int i = 0; i < n; ++i) {
        for (auto &[j, b] : g) {
            if (j > i) break;
            (*this)[i] -= (*this)[i-j] * b;
        }
        (*this)[i] *= ic;
        }
        return *this;
    }

    F &operator^=(long long n) {
        if (n == 0) {
            std::fill(this->begin(), this->end(), T(0));
            (*this)[0] = 1;
            return *this;
        }
        F f(*this);
        --n;
        while (n > 0) {
            if (n & 1)
                *this *= f;
            f = f * f;
            n >>= 1;
        }
        return *this;
    }

    // multiply and divide (1 + cz^d)
    void multiply(const int d, const T c) { 
        int n = (*this).size();
        if (c == T(1)) for(int i = n - d - 1; i >= 0; --i) (*this)[i+d] += (*this)[i];
        else if (c == T(-1)) for(int i = n - d - 1; i >= 0; --i) (*this)[i+d] -= (*this)[i];
        else for(int i = n - d - 1; i >= 0; --i) (*this)[i+d] += (*this)[i] * c;
    }
    void divide(const int d, const T c) {
        int n = (*this).size();
        if (c == T(1)) for(int i = 0; i < n - d; ++i) (*this)[i+d] -= (*this)[i];
        else if (c == T(-1)) for(int i = 0; i < n - d; ++i) (*this)[i+d] += (*this)[i];
        else for(int i = 0; i < n - d; ++i) (*this)[i+d] -= (*this)[i] * c;
    }

    T eval(const T &a) const {
        T x(1), res(0);
        for (auto e : *this) res += e * x, x *= a;
        return res;
    }

    friend F operator*(const T &g, const F &f) { return F(f) *= g; }
    friend F operator/(const T &g, const F &f) { return F(f) /= g; }
    friend F operator+(const F &f1, const F &f2) { return F(f1) += f2; }
    friend F operator-(const F &f1, const F &f2) { return F(f1) -= f2; }
    friend F operator<<(const F &f, const int d) { return F(f) <<= d; }
    friend F operator>>(const F &f, const int d) { return F(f) >>= d; }
    friend F operator*(const F &f1, const F &f2) { return F(f1) *= f2; }
    friend F operator/(const F &f1, const F &f2) { return F(f1) /= f2; }
    friend F operator*(const F &f, const std::vector<std::pair<int, T>> &g) { return F(f) *= g; }
    friend F operator/(const F &f, const std::vector<std::pair<int, T>> &g) { return F(f) /= g; }
    friend F operator^(const F &f, long long g) { return F(f) ^= g; }

};
