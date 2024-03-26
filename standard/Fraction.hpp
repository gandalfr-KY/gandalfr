#pragma once

#include <cassert>
#include <compare>
#include <exception>
#include <iostream>
#include <numeric>

#include "Mint.hpp"
#include "gandalfr/types.hpp"

namespace gandalfr {

namespace internal {

inline i128 abs128(i128 x) { return x >= 0 ? x : -x; }

inline i128 gcd128_impl(const i128 &a, const i128 &b) {
    i128 m = a % b;
    return m == 0 ? b : gcd128_impl(b, m);
};

// GCD の正値を返す。片方が 0 ならもう一方の絶対値。
inline i128 gcd128(i128 a, i128 b) {
    return abs128(b == 0 ? a : gcd128_impl(a, b));
}

inline void simplify128(i128 &num, i128 &den) {
    i128 d = gcd128(num, den);
    if (den < 0)
        d = -d;
    num /= d, den /= d;
}

inline bool isSameSign(i64 a, i64 b) { return (a ^ b) >= 0; }

} // namespace internal

class IndeterminateOperationException : public std::exception {
  private:
    std::string message;

  public:
    IndeterminateOperationException() = default;
    IndeterminateOperationException(const std::string &msg) : message(msg) {}

    virtual const char *what() const noexcept override {
        return message.c_str();
    }

    virtual ~IndeterminateOperationException() noexcept {}
};

/**
 * verify : https://atcoder.jp/contests/abc168/submissions/39533747
 * 演算結果の分子・分母がともに 64bit 整数の範囲でのみ動作を保証
 */
class Fraction {
  private:
    i64 num, den;

  public:
    static const Fraction M_INF, INF;

    Fraction(i64 n) : num(n), den(1) {}
    Fraction(i128 numerator, i128 denominator) {
        internal::simplify128(numerator, denominator);
        num = numerator, den = denominator;
    }
    Fraction() : num(0), den(1) {}

    Fraction operator+() const { return *this; }
    Fraction operator-() const {
        Fraction ret;
        ret.rawAssign(-num, den);
        return ret;
    }

    Fraction &operator+=(const Fraction &a) {
        if (isInf() && a.isInf() && !internal::isSameSign(num, a.num)) {
            throw IndeterminateOperationException();
        }
        return *this = Fraction((i128)num * a.den + (i128)a.num * den,
                                (i128)den * a.den);
    }
    Fraction &operator-=(const Fraction &a) {
        if (isInf() && a.isInf() && internal::isSameSign(num, a.num)) {
            throw IndeterminateOperationException();
        }
        return *this = Fraction((i128)num * a.den - (i128)a.num * den,
                                (i128)den * a.den);
    }
    Fraction &operator*=(const Fraction &a) {
        if ((num == 0 && a.den == 0) || (den == 0 && a.num == 0)) {
            throw IndeterminateOperationException();
        }
        i64 gcd_tmp1 = std::gcd(num, a.den), gcd_tmp2 = std::gcd(den, a.num);
        num /= gcd_tmp1, num *= a.num / gcd_tmp2;
        den /= gcd_tmp2, den *= a.den / gcd_tmp1;
        return *this;
    }
    Fraction &operator/=(const Fraction &a) { return *this *= a.inverse(); }

    friend Fraction operator+(const Fraction &a, const Fraction &b) {
        return Fraction(a) += b;
    }
    friend Fraction operator-(const Fraction &a, const Fraction &b) {
        return Fraction(a) -= b;
    }
    friend Fraction operator*(const Fraction &a, const Fraction &b) {
        return Fraction(a) *= b;
    }
    friend Fraction operator/(const Fraction &a, const Fraction &b) {
        return Fraction(a) /= b;
    }

    friend std::strong_ordering operator<=>(const Fraction &a,
                                            const Fraction &b) {
        if (!internal::isSameSign(a.num, b.num))
            return a.num >= 0 ? std::strong_ordering::greater
                              : std::strong_ordering::less;
        if (a == b)
            return std::strong_ordering::equal;
        return (i128)a.num * b.den > (i128)b.num * a.den
                   ? std::strong_ordering::greater
                   : std::strong_ordering::less;
    }

    friend bool operator==(const Fraction &a, const Fraction &b) = default;

    friend std::istream &operator>>(std::istream &is, Fraction &a) {
        std::string buf;
        is >> buf;
        size_t slash_pos = buf.find('/');
        if (slash_pos == std::string::npos) {
            a.num = std::stoll(buf);
            a.den = 1;
        } else {
            a.num = std::stoll(buf.substr(0, slash_pos));
            a.den = std::stoll(buf.substr(slash_pos + 1, buf.size()));
            i64 d = std::gcd(a.num, a.den);
            a.num /= d, a.den /= d;
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Fraction &a) {
        if (a.den == 0)
            os << (a.num >= 0 ? "inf" : "-inf");
        else if (a.den == 1)
            os << a.num;
        else
            os << a.num << '/' << a.den;
        return os;
    }

    void rawAssign(i64 _num, i64 _den) { num = _num, den = _den; }
    i64 numer() const { return num; }
    i64 denom() const { return den; }
    Fraction inverse() const {
        Fraction ret;
        if (num >= 0) {
            ret.rawAssign(den, num);
        } else {
            ret.rawAssign(-den, -num);
        }
        return ret;
    }
    template <int m> i32 mod() const {
        Mint<m> ret(num);
        ret /= den;
        return ret.val;
    }

    bool isInf() const { return den == 0; }
    double toDouble() const { return (double)num / den; }
    friend Fraction abs(const Fraction &x) { return (x.num >= 0 ? x : -x); }
    friend i64 floor(const Fraction &x) { return x.num / x.den; }
    friend i64 ceil(const Fraction &x) {
        return ((i128)x.num + x.den - 1) / x.den;
    }
};
const Fraction Fraction::M_INF(-1, 0), Fraction::INF(1, 0);

} // namespace gandalfr
