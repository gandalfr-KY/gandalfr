#pragma once

#include <cassert>
#include <iostream>
#include <numeric>

#include "atcoder/modint.hpp"
#include "../types.hpp"

namespace gandalfr {

namespace internal {

// 絶対値の GCD を返す。片方が 0 ならもう一方の絶対値。
i128 gcd(i128 a, i128 b) {
    if (b == 0) {
        return (a >= 0 ? a : -a);
    }
    auto rec = [](auto self, const i128& a, const i128& b) -> i128 {
        return a % b == 0 ? b : self(self, b, a % b);
    };
    return rec(rec, a >= 0 ? a : -a, b >= 0 ? b : -b);
}

inline void simplify(i128 &num, i128 &den) {
    i128 d = internal::gcd(num, den);
    num /= (den >= 0 ? d : -d);
    den /= (den >= 0 ? d : -d);
}

} // namespace internal

/**
 * verify : https://atcoder.jp/contests/abc168/submissions/39533747
 * 演算結果の分子・分母がともに 64bit 整数の範囲でのみ動作を保証
 */
class Fraction {
  private:
    i64 num, den;

    friend Fraction operator+(const Fraction &a) { return a; }
    friend Fraction operator-(const Fraction &a) {
        Fraction ret;
        ret.raw_assign(-a.num, a.den);
        return ret;
    }

    friend Fraction operator+(const Fraction &a, const Fraction &b) {
        assert(!(a.is_infinity() && b.is_infinity() &&
                 a.num * b.num == -1)); // 不定形はダメ
        if (a.is_infinity()) {
            return a;
        } else if (b.is_infinity()) {
            return b;
        } else {
            return {(i128)a.num * b.den + (i128)b.num * a.den,
                    (i128)a.den * b.den};
        }
    }
    friend Fraction operator-(const Fraction &a, const Fraction &b) {
        assert(!(a.is_infinity() && b.is_infinity() &&
                 a.num * b.num == 1)); // 不定形はダメ
        if (a.is_infinity()) {
            return a;
        } else if (b.is_infinity()) {
            return -b;
        } else {
            return {(i128)a.num * b.den - (i128)b.num * a.den,
                    (i128)a.den * b.den};
        }
    }
    friend Fraction operator*(const Fraction &a, const Fraction &b) {
        assert(a.num != 0 || b.den != 0);
        assert(a.den != 0 || b.num != 0);
        i64 gcd_tmp1 = std::gcd(a.num, b.den),
                  gcd_tmp2 = std::gcd(b.num, a.den);
        Fraction ret;
        ret.raw_assign((a.num / gcd_tmp1) * (b.num / gcd_tmp2),
                       (a.den / gcd_tmp2) * (b.den / gcd_tmp1));
        return ret;
    }
    friend Fraction operator/(const Fraction &a, const Fraction &b) {
        assert(a.num != 0 || b.num != 0);
        assert(a.den != 0 || b.den != 0);
        i64 gcd_tmp1 = std::gcd(a.num, b.num),
                  gcd_tmp2 = std::gcd(b.den, a.den);
        Fraction ret;
        ret.raw_assign(
            (b.num >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),
            (b.num >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));
        return ret;
    }

    friend bool operator==(const Fraction &a, const Fraction &b) {
        return a.num == b.num && a.den == b.den;
    }
    friend bool operator!=(const Fraction &a, const Fraction &b) {
        return a.num != b.num || a.den != b.den;
    }

    friend i32 compare_to(const Fraction &a, const Fraction &b) {
        if ((a.num >= 0) ^ (b.num >= 0))
            return a.num > b.num ? 1 : -1;
        i128 lhs = (i128)a.num * b.den;
        i128 rhs = (i128)b.num * a.den;
        if (lhs == rhs)
            return 0;
        return lhs > rhs ? 1 : -1;
    }

    friend bool operator>(const Fraction &a, const Fraction &b) {
        return compare_to(a, b) > 0;
    }
    friend bool operator>=(const Fraction &a, const Fraction &b) {
        return compare_to(a, b) >= 0;
    }
    friend bool operator<(const Fraction &a, const Fraction &b) {
        return compare_to(a, b) < 0;
    }
    friend bool operator<=(const Fraction &a, const Fraction &b) {
        return compare_to(a, b) <= 0;
    }

  public:
    Fraction(i64 n) : num(n), den(1) {}
    Fraction(i128 numerator, i128 denominator) {
        internal::simplify(numerator, denominator);
        num = numerator, den = denominator;
    }
    Fraction() : num(0), den(1) {}

    Fraction &operator=(const Fraction &a) = default;
    Fraction &operator+=(const Fraction &a) { return *this = *this + a; }
    Fraction &operator-=(const Fraction &a) { return *this = *this - a; }
    Fraction &operator*=(const Fraction &a) { return *this = *this * a; }
    Fraction &operator/=(const Fraction &a) { return *this = *this / a; }

    friend std::istream &operator>>(std::istream &is, Fraction &a) {
        std::string buf;
        is >> buf;
        i128 num_tmp = 0, den_tmp = 0;
        i32 i = (buf[0] == '-'), sz = buf.size();
        for (; i < sz && buf[i] != '/'; i++)
            num_tmp = num_tmp * 10 + buf[i] - '0';
        if (i == sz)
            den_tmp = 1;
        else
            for (i = i + 1; i < sz; i++)
                den_tmp = den_tmp * 10 + buf[i] - '0';
        if (buf[0] == '-')
            num_tmp *= -1;
        internal::simplify(num_tmp, den_tmp);
        a.num = num_tmp, a.den = den_tmp;
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

    // 約分を省略して代入する
    Fraction &raw_assign(i64 _num, i64 _den) {
        num = _num, den = _den;
        return *this;
    }
    i64 numerator() const { return num; }
    i64 denomitnator() const { return den; }
    i64 floor() const { return num / den; }
    i64 ceil() const { return ((i128)num + den - 1) / den; }
    double real() const { return (double)num / den; }
    Fraction abs() const { return (*this >= 0 ? *this : -*this); }
    Fraction inverse() const {
        Fraction ret;
        ret.raw_assign((num >= 0 ? den : -den), (num >= 0 ? num : -num));
        return ret;
    }
    template <int m>
    i32 mod() const {
        atcoder::static_modint<m> ret(num);
        ret /= den;
        return ret.val;
    }
    bool is_infinity() const { return (den == 0); }

    static const Fraction M_INF, INF;
};
const Fraction Fraction::M_INF(-1, 0), Fraction::INF(1, 0);
}
