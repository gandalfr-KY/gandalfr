#ifndef FRACTION
#define FRACTION
#include <numeric>
#include <iostream>
#include <assert.h>
#include "gandalfr/math/integer/mod_inverse.hpp"

// verify : https://atcoder.jp/contests/abc168/submissions/39533747
// 演算結果の分子・分母がともに 64bit 整数の範囲でのみ動作を保証
class fraction{
  private:
    long long num, den;

    inline void simplify(){
        long long d = std::gcd(num, den);
        num /= (den >= 0 ? d : -d);
        den /= (den >= 0 ? d : -d);
    }

    friend fraction operator+(const fraction &a){ return a; }
    friend fraction operator-(const fraction &a){
        fraction ret;
        ret.raw_assign(-a.num, a.den);
        return ret;
    }

    friend fraction operator+(const fraction &a, const fraction &b){
        if(a.is_infinity()) {
            assert(!(b.is_infinity() && a.num * b.num == -1)); // 不定形はダメ
            return a;
        }
        else if(b.is_infinity()) {
            return b;
        }
        else {
            return {(__int128_t)a.num * b.den + (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};
        }
    }
    friend fraction operator-(const fraction &a, const fraction &b){
        if(a.is_infinity()) {
            assert(!(b.is_infinity() && a.num * b.num == 1)); // 不定形はダメ
            return a;
        }
        else if(b.is_infinity()) {
            return -b;
        }
        else {
            return {(__int128_t)a.num * b.den - (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};
        }
    }
    friend const fraction operator*(const fraction &a, const fraction &b){
        assert(a.num != 0 || b.den != 0);
        assert(a.den != 0 || b.num != 0);
        __int128_t gcd_tmp1 = std::gcd(a.num, b.den), gcd_tmp2 = std::gcd(b.num, a.den);
        fraction ret;
        ret.raw_assign((a.num / gcd_tmp1) * (b.num / gcd_tmp2),
            (a.den / gcd_tmp2) * (b.den / gcd_tmp1));
        return ret;
    }
    friend const fraction operator/(const fraction &a, const fraction &b){
        assert(a.num != 0 || b.num != 0);
        assert(a.den != 0 || b.den != 0);
        __int128_t gcd_tmp1 = std::gcd(a.num, b.num), gcd_tmp2 = std::gcd(b.den, a.den);
        fraction ret;
        ret.raw_assign((b.num >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),
            (b.num < 0 ? -1 : 1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));
        return ret;
    }

    friend bool operator==(const fraction &a, const fraction &b){ return a.num == b.num && a.den == b.den; }
    friend bool operator!=(const fraction &a, const fraction &b){ return a.num != b.num || a.den != b.den; }
    friend bool operator>(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num > b.num);
        return (__int128_t)a.num * b.den > (__int128_t)b.num * a.den;
    }
    friend bool operator>=(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num >= b.num);
        return (__int128_t)a.num * b.den >= (__int128_t)b.num * a.den;
    }
    friend bool operator<(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num < b.num);
        return (__int128_t)a.num * b.den < (__int128_t)b.num * a.den;
    }
    friend bool operator<=(const fraction &a, const fraction &b){
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num <= b.num);
        return (__int128_t)a.num * b.den <= (__int128_t)b.num * a.den;
    }

  public:
    fraction(const fraction &a){ num = a.num, den = a.den; }
    fraction(long long n) : num(n), den(1) {}
    fraction(__int128_t numerator, __int128_t denominator)
        : num(numerator), den(denominator) { simplify(); }
    fraction() : num(0), den(1) {}

    fraction &operator=(const fraction &a){
        num = a.num, den = a.den;
        return *this;
    }
    fraction &operator+=(const fraction &a){
        return *this = *this + a;
    }
    fraction &operator-=(const fraction &a){
        return *this = *this - a;
    }
    fraction &operator*=(const fraction &a){
        return *this = *this * a;
    }
    fraction &operator/=(const fraction &a){
        return *this = *this / a;
    }

    friend std::istream &operator>>(std::istream &is, fraction &a){
        std::string buf;
        is >> buf;
        a.num = a.den = 0;
        int i = (buf[0] == '-'), sz = buf.size();
        for(; i < sz && buf[i] != '/'; i++) a.num = a.num * 10 + buf[i] - '0';
        if(i == sz) a.den = 1;
        else for(i = i + 1; i < sz; i++) a.den = a.den * 10 + buf[i] - '0';
        if(buf[0] == '-') a.num *= -1;
        a.simplify();
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const fraction &a) {
        if(a.den == 0) os << (a.num >= 0 ? "inf" : "-inf");
        else if(a.den == 1) os << a.num;
        else os << a.num << '/' << a.den;
        return os;
    }

    // 約分を省略して代入する
    fraction &raw_assign(long long _num, long long _den){ 
        num = _num, den = _den;
        return *this;
    }
    long long numerator() const { return num; }
    long long denomitnator() const { return den; }
    long long floor() const { return num / den; }
    long long ceil() const { return ((__int128_t)num + den - 1) / den; }
    double real() const { return (double)num / den; }
    fraction abs() const { return (*this >= 0 ? *this : -*this); } 
    fraction inverse() const {
        fraction ret;
        ret.raw_assign((num >= 0 ? den : -den), (num >= 0 ? num : -num));
        return ret;
    }
    long long mod(long long _mod) const {
        assert(_mod > 0);
        __int128_t ret = num % _mod;
        if(ret < 0) ret += _mod;
        ret = ret * mod_inverse<__int128_t>(den, _mod) % _mod;
        return ret;
    }
    bool is_infinity() const { return (den == 0); }

    static const fraction M_INF, INF;
};
const fraction fraction::M_INF(-1, 0), fraction::INF(1, 0);


#endif
