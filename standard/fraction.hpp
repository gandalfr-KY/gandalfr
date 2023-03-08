#ifndef FRACTION
#define FRACTION
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "gandalfr/standard/power.hpp"
#include "gandalfr/standard/gcdlcm.hpp"
#include "gandalfr/math/integer/mod_inverse.hpp"

#include "gandalfr/standard/io_supporter.hpp"

class fraction{
  private:
    __int128_t num, den;

    void simplify(){
        __int128_t gcd_tmp = _gcd((num >= 0 ? num : -num), (den >= 0 ? den : -den));
        num /= gcd_tmp;
        den /= gcd_tmp;
        if(den < 0){
            num *= -1;
            den *= -1;
        }
    }

    friend const fraction operator+(const fraction &a){ return a; }
    friend const fraction operator-(const fraction &a){ return {-a.num, a.den, false}; }

    friend const fraction operator+(const fraction &a, const fraction &b){
        __int128_t lcm_tmp = _lcm((a.den >= 0 ? a.den : -a.den), (b.den >= 0 ? b.den : -b.den));
        return {lcm_tmp / a.den * a.num + lcm_tmp / b.den * b.num, lcm_tmp};
    }

    friend const fraction operator-(const fraction &a, const fraction &b){
        __int128_t lcm_tmp = _lcm((a.den >= 0 ? a.den : -a.den), (b.den >= 0 ? b.den : -b.den));
        return {lcm_tmp / a.den * a.num - lcm_tmp / b.den * b.num, lcm_tmp};
    }

    friend const fraction operator*(const fraction &a, const fraction &b){
        __int128_t gcd_tmp1 = _gcd((a.num >= 0 ? a.num : -a.num), (b.den >= 0 ? b.den : -b.den)),
            gcd_tmp2 = _gcd((b.num >= 0 ? b.num : -b.num), (a.den >= 0 ? a.den : -a.den));
        return {(a.num / gcd_tmp1) * (b.num / gcd_tmp2), (a.den / gcd_tmp2) * (b.den / gcd_tmp1), false};
    }

    friend const fraction operator/(const fraction &a, const fraction &b){
        assert(b.num != 0);
        __int128_t gcd_tmp1 = _gcd((a.num >= 0 ? a.num : -a.num), (b.num >= 0 ? b.num : -b.num)),
            gcd_tmp2 = _gcd((b.den >= 0 ? b.den : -b.den), (a.den >= 0 ? a.den : -a.den));
        return {(a.num / gcd_tmp1) * (b.den / gcd_tmp2), (a.den / gcd_tmp2) * (b.num / gcd_tmp1), false};
    }

    friend bool operator==(const fraction &a, const fraction &b){
        return a.num == b.num && a.den == b.den;
    }

    friend bool operator!=(const fraction &a, const fraction &b){
        return a.num != b.num || a.den != b.den;
    }   

    // 64bit整数の範囲でのみ正しく判定可能
    friend bool operator>(const fraction &a, const fraction &b) { return a.num * b.den >  b.num * a.den; }
    friend bool operator>=(const fraction &a, const fraction &b){ return a.num * b.den >= b.num * a.den; }
    friend bool operator<(const fraction &a, const fraction &b) { return a.num * b.den <  b.num * a.den; }
    friend bool operator<=(const fraction &a, const fraction &b){ return a.num * b.den <= b.num * a.den; }

  public:
    fraction(__int128_t n) : num(n), den(1) {}
    // false を添えると約分されない
    fraction(__int128_t numerator, __int128_t denominator, bool with_simplify = true) : num(numerator), den(denominator) {
        assert(den != 0);
        if(with_simplify) simplify();
    }
    fraction(const std::string &s) : num(0), den(0) {
        int i = (s[0] == '-');
        for(; i < s.size() && s[i] != '/'; i++) num = num * 10 + s[i] - '0'; 
        for(i = i + 1; i < s.size(); i++) den = den * 10 + s[i] - '0';
        if(s[0] == '-') num *= -1;
        if(den == 0) den = 1;
        simplify();
    }
    fraction(const char s[]) : fraction(std::string(s)) {}
    fraction() : num(0), den(1) {}

    __int128_t numerator() const { return num; }
    __int128_t denomitnator() const { return den; }
    double real() const { return (double)num / den; }
    const fraction abs() const { return {(num >= 0 ? num : -num), den, false}; } 
    const fraction inverse() const { return {(num >= 0 ? den : -den), (num >= 0 ? num : -num), false}; }
    const __int128_t mod_value(__int128_t mod) const {
        assert(mod > 0);
        __int128_t ret = num % mod;
        if(ret < 0) ret += mod;
        ret = ret * mod_inverse(den, mod) % mod;
        return ret;
    }

    fraction &operator=(const fraction &a){
        num = a.num;
        den = a.den;
        return *this;
    }

    void operator+=(const fraction &a){
        __int128_t lcm_tmp = _lcm((den >= 0 ? den : -den), (a.den >= 0 ? a.den : -a.den));
        num = lcm_tmp / den * num + lcm_tmp / a.den * a.num;
        den = lcm_tmp;
        simplify();
    }

    void operator-=(const fraction &a){
        __int128_t lcm_tmp = _lcm((den >= 0 ? den : -den), (a.den >= 0 ? a.den : -a.den));
        num = lcm_tmp / den * num - lcm_tmp / a.den * a.num;
        den = lcm_tmp;
        simplify();
    }

    void operator*=(const fraction &a){
        __int128_t gcd_tmp1 = _gcd((num >= 0 ? num : -num), (a.den >= 0 ? a.den : -a.den)),
             gcd_tmp2 = _gcd((a.num >= 0 ? a.num : -a.num), (den >= 0 ? den : -den));
        num = (num / gcd_tmp1) * (a.num / gcd_tmp2);
        den = (den / gcd_tmp2) * (a.den / gcd_tmp1);
    }

    void operator/=(const fraction &a){
        assert(a.num != 0);
        __int128_t gcd_tmp1 = _gcd((num >= 0 ? num : -num), (a.num >= 0 ? a.num : -a.num)),
            gcd_tmp2 = _gcd((a.den >= 0 ? a.den : -a.den), (den >= 0 ? den : -den));
        num = (num / gcd_tmp1) * (a.den / gcd_tmp2);
        den = (den / gcd_tmp2) * (a.num / gcd_tmp1);
    }

    friend std::istream &operator>>(std::istream &is, fraction &a){
        std::string tmp;
        is >> tmp;
        a.num = a.den = 0;
        int i = (tmp[0] == '-');
        for(; i < tmp.size() && tmp[i] != '/'; i++) a.num = a.num * 10 + tmp[i] - '0'; 
        for(i = i + 1; i < tmp.size(); i++) a.den = a.den * 10 + tmp[i] - '0';
        if(tmp[0] == '-') a.num *= -1;
        if(a.den == 0) a.den = 1;
        a.simplify();
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const fraction &a) {
        os << a.num;
        if(a.den != 1) os << '/' << a.den;
        return os;
    }
};

#endif