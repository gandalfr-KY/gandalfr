#ifndef FRACTION
#define FRACTION
#include "gandalfr/standard/gcdlcm.hpp"
#include "gandalfr/math/integer/mod_inverse.hpp"

// verify : https://atcoder.jp/contests/abc168/submissions/39533747
// 分子・分母がともに 64bit 整数の範囲でのみ動作を保証
class fraction{
  private:
    __int128_t num, den;

    void simplify(){
        __int128_t d = _gcd(num, den);
        num /= (den >= 0 ? d : -d);
        den /= (den >= 0 ? d : -d);
    }

    friend const fraction operator+(const fraction &a){ return a; }
    friend const fraction operator-(const fraction &a){ return {-a.num, a.den, false}; }

    friend const fraction operator+(const fraction &a, const fraction &b){
        __int128_t lcm_tmp = _lcm(a.den, b.den);
        return {lcm_tmp / a.den * a.num + lcm_tmp / b.den * b.num, lcm_tmp};
    }
    friend const fraction operator-(const fraction &a, const fraction &b){
        __int128_t lcm_tmp = _lcm(a.den, b.den);
        return {lcm_tmp / a.den * a.num - lcm_tmp / b.den * b.num, lcm_tmp};
    }
    friend const fraction operator*(const fraction &a, const fraction &b){
        __int128_t gcd_tmp1 = _gcd(a.num, b.den), gcd_tmp2 = _gcd(b.num, a.den);
        return {(a.num / gcd_tmp1) * (b.num / gcd_tmp2), (a.den / gcd_tmp2) * (b.den / gcd_tmp1), false};
    }
    friend const fraction operator/(const fraction &a, const fraction &b){
        //assert(b.num != 0);
        __int128_t gcd_tmp1 = _gcd(a.num, b.num), gcd_tmp2 = _gcd(b.den, a.den);
        return {(a.num / gcd_tmp1) * (b.den / gcd_tmp2), (a.den / gcd_tmp2) * (b.num / gcd_tmp1), false};
    }

    friend bool operator==(const fraction &a, const fraction &b){ return a.num == b.num && a.den == b.den; }
    friend bool operator!=(const fraction &a, const fraction &b){ return a.num != b.num || a.den != b.den; }
    friend bool operator>(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num > b.num);
        return a.num * b.den > b.num * a.den;
    }
    friend bool operator>=(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num >= b.num);
        return a.num * b.den >= b.num * a.den;
    }
    friend bool operator<(const fraction &a, const fraction &b) {
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num < b.num);
        return a.num * b.den < b.num * a.den;
    }
    friend bool operator<=(const fraction &a, const fraction &b){
        if((a.num >= 0) ^ (b.num >= 0)) return (a.num <= b.num);
        return a.num * b.den <= b.num * a.den;
    }

  public:
    fraction(const fraction &a){ num = a.num, den = a.den; }
    fraction(__int128_t n) : num(n), den(1) {}
    // false を添えると約分されない
    fraction(__int128_t numerator, __int128_t denominator, bool with_simplify = true) : num(numerator), den(denominator) { if(with_simplify) simplify(); }
    fraction() : num(0), den(1) {}

    fraction &operator=(const fraction &a){
        num = a.num;
        den = a.den;
        return *this;
    }
    fraction &operator+=(const fraction &a){
        __int128_t lcm_tmp = _lcm(den, a.den);
        num = lcm_tmp / den * num + lcm_tmp / a.den * a.num;
        den = lcm_tmp;
        simplify();
        return *this;
    }
    fraction &operator-=(const fraction &a){
        __int128_t lcm_tmp = _lcm(den, a.den);
        num = lcm_tmp / den * num - lcm_tmp / a.den * a.num;
        den = lcm_tmp;
        simplify();
        return *this;
    }
    fraction &operator*=(const fraction &a){
        __int128_t gcd_tmp1 = _gcd(num, a.den), gcd_tmp2 = _gcd(a.num, den);
        num = (num / gcd_tmp1) * (a.num / gcd_tmp2);
        den = (den / gcd_tmp2) * (a.den / gcd_tmp1);
        return *this;
    }
    fraction &operator/=(const fraction &a){
        __int128_t gcd_tmp1 = _gcd(num, a.num), gcd_tmp2 = _gcd(a.den, den);
        num = (num / gcd_tmp1) * (a.den / gcd_tmp2);
        den = (den / gcd_tmp2) * (a.num / gcd_tmp1);
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, fraction &a){
        std::string buf;
        is >> buf;
        a.num = a.den = 0;
        int i = (buf[0] == '-');
        for(; i < buf.size() && buf[i] != '/'; i++) a.num = a.num * 10 + buf[i] - '0';
        if(i == buf.size()) a.den = 1;
        else for(i = i + 1; i < buf.size(); i++) a.den = a.den * 10 + buf[i] - '0';
        if(buf[0] == '-') a.num *= -1;
        a.simplify();
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const fraction &a) {
        if(a.den == 0) os << (a.num >= 0 ? "inf" : "-inf");
        else if(a.den == 1) os << (long long)a.num;
        else os << (long long)a.num << '/' << (long long)a.den;
        return os;
    }

    long long numerator() const { return num; }
    long long denomitnator() const { return den; }
    long long floor() const { return num / den; }
    long long ceil() const { return (num + den - 1) / den; }
    double real() const { return (double)num / den; }
    fraction abs() const { return {(num >= 0 ? num : -num), den, false}; } 
    fraction inverse() const { return {(num >= 0 ? den : -den), (num >= 0 ? num : -num), false}; }
    long long mod(long long _mod) const {
        assert(_mod > 0);
        __int128_t ret = num % _mod;
        if(ret < 0) ret += _mod;
        ret = ret * mod_inverse<__int128_t>(den, _mod) % _mod;
        return ret;
    }

    static const fraction M_INF, INF;
};
const fraction fraction::M_INF(-1, 0), fraction::INF(1, 0);


#endif