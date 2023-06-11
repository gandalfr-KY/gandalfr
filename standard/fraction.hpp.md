---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/Bezout_coefficients.hpp
    title: math/Bezout_coefficients.hpp
  - icon: ':warning:'
    path: math/mod_inverse.hpp
    title: math/mod_inverse.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc168/submissions/39533747
  bundledCode: "#line 1 \"standard/fraction.hpp\"\n\n\n#include <numeric>\n#include\
    \ <iostream>\n#include <assert.h>\n#line 1 \"math/mod_inverse.hpp\"\n\n\n#line\
    \ 1 \"math/Bezout_coefficients.hpp\"\n\n\n#include <utility>\n#include <cstdlib>\n\
    \nlong long _extgcd(long long a, long long b, long long &s, long long &t){\n \
    \   if(b == 0){\n        s = 1;\n        t = 0;\n        return a;\n    }\n  \
    \  else{\n        auto d = std::lldiv(a, b);\n        long long tmp = _extgcd(b,\
    \ d.rem, t, s);\n        t -= d.quot * s;\n        return tmp;\n    }\n}\n\nstd::pair<long\
    \ long, long long> Bezout_coefficients(long long a, long long b){\n    long long\
    \ s, t;\n    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n    return\
    \ {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n\n#line 5 \"math/mod_inverse.hpp\"\
    \n\nlong long mod_inverse(long long x, int mod){\n    assert(mod > 0);\n    x\
    \ %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n    assert(a * x ==\
    \ -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n\n\n#line 7 \"standard/fraction.hpp\"\
    \n\nnamespace internal{\n\n    __int128_t __gcd(__int128_t a, __int128_t b){\n\
    \        if(a % b == 0) return b;\n        return __gcd(b, a % b); \n    }\n\n\
    \    // \u7D76\u5BFE\u5024\u306E GCD \u3092\u8FD4\u3059\u3002\u7247\u65B9\u304C\
    \ 0 \u306A\u3089\u3082\u3046\u4E00\u65B9\u306E\u7D76\u5BFE\u5024\u3002\n    __int128_t\
    \ gcd(__int128_t a, __int128_t b){\n        if(b == 0) return (a >= 0 ? a : -a);\n\
    \        return internal::__gcd((a >= 0 ? a : -a), (b >= 0 ? b : -b));\n    }\n\
    \n    inline void simplify(__int128_t &num, __int128_t &den){\n        __int128_t\
    \ d = internal::gcd(num, den);\n        num /= (den >= 0 ? d : -d);\n        den\
    \ /= (den >= 0 ? d : -d);\n    }\n};\n\n// verify : https://atcoder.jp/contests/abc168/submissions/39533747\n\
    // \u6F14\u7B97\u7D50\u679C\u306E\u5206\u5B50\u30FB\u5206\u6BCD\u304C\u3068\u3082\
    \u306B 64bit \u6574\u6570\u306E\u7BC4\u56F2\u3067\u306E\u307F\u52D5\u4F5C\u3092\
    \u4FDD\u8A3C\nclass fraction{\n  private:\n    long long num, den;\n\n    friend\
    \ fraction operator+(const fraction &a){ return a; }\n    friend fraction operator-(const\
    \ fraction &a){\n        fraction ret;\n        ret.raw_assign(-a.num, a.den);\n\
    \        return ret;\n    }\n\n    friend fraction operator+(const fraction &a,\
    \ const fraction &b){\n        assert(!(a.is_infinity() && b.is_infinity() &&\
    \ a.num * b.num == -1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\n        if(a.is_infinity())\
    \ {\n            return a;\n        }\n        else if(b.is_infinity()) {\n  \
    \          return b;\n        }\n        else {\n            return {(__int128_t)a.num\
    \ * b.den + (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};\n        }\n\
    \    }\n    friend fraction operator-(const fraction &a, const fraction &b){\n\
    \        assert(!(a.is_infinity() && b.is_infinity() && a.num * b.num == 1));\
    \ // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\n        if(a.is_infinity()) {\n   \
    \         return a;\n        }\n        else if(b.is_infinity()) {\n         \
    \   return -b;\n        }\n        else {\n            return {(__int128_t)a.num\
    \ * b.den - (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};\n        }\n\
    \    }\n    friend const fraction operator*(const fraction &a, const fraction\
    \ &b){\n        assert(a.num != 0 || b.den != 0);\n        assert(a.den != 0 ||\
    \ b.num != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.den), gcd_tmp2\
    \ = std::gcd(b.num, a.den);\n        fraction ret;\n        ret.raw_assign((a.num\
    \ / gcd_tmp1) * (b.num / gcd_tmp2),\n            (a.den / gcd_tmp2) * (b.den /\
    \ gcd_tmp1));\n        return ret;\n    }\n    friend const fraction operator/(const\
    \ fraction &a, const fraction &b){\n        assert(a.num != 0 || b.num != 0);\n\
    \        assert(a.den != 0 || b.den != 0);\n        long long gcd_tmp1 = std::gcd(a.num,\
    \ b.num), gcd_tmp2 = std::gcd(b.den, a.den);\n        fraction ret;\n        ret.raw_assign((b.num\
    \ >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),\n            (b.num\
    \ >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));\n        return ret;\n\
    \    }\n\n    friend bool operator==(const fraction &a, const fraction &b){ return\
    \ a.num == b.num && a.den == b.den; }\n    friend bool operator!=(const fraction\
    \ &a, const fraction &b){ return a.num != b.num || a.den != b.den; }\n\n    friend\
    \ int compare_to(const fraction &a, const fraction &b) {\n        if((a.num >=\
    \ 0) ^ (b.num >= 0)) return a.num > b.num ? 1 : -1;\n        __int128_t lhs =\
    \ (__int128_t)a.num * b.den;\n        __int128_t rhs = (__int128_t)b.num * a.den;\n\
    \        if (lhs == rhs) return 0;\n        return lhs > rhs ? 1 : -1;\n    }\n\
    \n    friend bool operator>(const fraction &a, const fraction &b) { return compare_to(a,\
    \ b) > 0; }\n    friend bool operator>=(const fraction &a, const fraction &b)\
    \ { return compare_to(a, b) >= 0; }\n    friend bool operator<(const fraction\
    \ &a, const fraction &b) { return compare_to(a, b) < 0; }\n    friend bool operator<=(const\
    \ fraction &a, const fraction &b) { return compare_to(a, b) <= 0; }\n\n  public:\n\
    \    fraction(long long n) : num(n), den(1) {}\n    fraction(__int128_t numerator,\
    \ __int128_t denominator){\n        internal::simplify(numerator, denominator);\n\
    \        num = numerator, den = denominator;\n    }\n    fraction() : num(0),\
    \ den(1) {}\n\n    const fraction &operator=(const fraction &a){\n        num\
    \ = a.num, den = a.den;\n        return *this;\n    }\n    const fraction &operator+=(const\
    \ fraction &a){\n        return *this = *this + a;\n    }\n    const fraction\
    \ &operator-=(const fraction &a){\n        return *this = *this - a;\n    }\n\
    \    const fraction &operator*=(const fraction &a){\n        return *this = *this\
    \ * a;\n    }\n    const fraction &operator/=(const fraction &a){\n        return\
    \ *this = *this / a;\n    }\n\n    friend std::istream &operator>>(std::istream\
    \ &is, fraction &a){\n        std::string buf;\n        is >> buf;\n        __int128_t\
    \ num_tmp = 0, den_tmp = 0;\n        int i = (buf[0] == '-'), sz = buf.size();\n\
    \        for(; i < sz && buf[i] != '/'; i++) num_tmp = num_tmp * 10 + buf[i] -\
    \ '0';\n        if(i == sz) den_tmp = 1;\n        else for(i = i + 1; i < sz;\
    \ i++) den_tmp = den_tmp * 10 + buf[i] - '0';\n        if(buf[0] == '-') num_tmp\
    \ *= -1;\n        internal::simplify(num_tmp, den_tmp);\n        a.num = num_tmp,\
    \ a.den = den_tmp;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const fraction &a) {\n        if(a.den == 0) os << (a.num >= 0 ? \"inf\"\
    \ : \"-inf\");\n        else if(a.den == 1) os << a.num;\n        else os << a.num\
    \ << '/' << a.den;\n        return os;\n    }\n\n    // \u7D04\u5206\u3092\u7701\
    \u7565\u3057\u3066\u4EE3\u5165\u3059\u308B\n    fraction &raw_assign(long long\
    \ _num, long long _den){ \n        num = _num, den = _den;\n        return *this;\n\
    \    }\n    long long numerator() const { return num; }\n    long long denomitnator()\
    \ const { return den; }\n    long long floor() const { return num / den; }\n \
    \   long long ceil() const { return ((__int128_t)num + den - 1) / den; }\n   \
    \ double real() const { return (double)num / den; }\n    fraction abs() const\
    \ { return (*this >= 0 ? *this : -*this); } \n    fraction inverse() const {\n\
    \        fraction ret;\n        ret.raw_assign((num >= 0 ? den : -den), (num >=\
    \ 0 ? num : -num));\n        return ret;\n    }\n    int mod(int _mod) const {\n\
    \        assert(_mod > 0);\n        long long ret = num % _mod;\n        if(ret\
    \ < 0) ret += _mod;\n        return (ret *= mod_inverse(den, _mod)) %= _mod;\n\
    \    }\n    bool is_infinity() const { return (den == 0); }\n\n    static const\
    \ fraction M_INF, INF;\n};\nconst fraction fraction::M_INF(-1, 0), fraction::INF(1,\
    \ 0);\n\n\n\n"
  code: "#ifndef FRACTION\n#define FRACTION\n#include <numeric>\n#include <iostream>\n\
    #include <assert.h>\n#include \"../math/mod_inverse.hpp\"\n\nnamespace internal{\n\
    \n    __int128_t __gcd(__int128_t a, __int128_t b){\n        if(a % b == 0) return\
    \ b;\n        return __gcd(b, a % b); \n    }\n\n    // \u7D76\u5BFE\u5024\u306E\
    \ GCD \u3092\u8FD4\u3059\u3002\u7247\u65B9\u304C 0 \u306A\u3089\u3082\u3046\u4E00\
    \u65B9\u306E\u7D76\u5BFE\u5024\u3002\n    __int128_t gcd(__int128_t a, __int128_t\
    \ b){\n        if(b == 0) return (a >= 0 ? a : -a);\n        return internal::__gcd((a\
    \ >= 0 ? a : -a), (b >= 0 ? b : -b));\n    }\n\n    inline void simplify(__int128_t\
    \ &num, __int128_t &den){\n        __int128_t d = internal::gcd(num, den);\n \
    \       num /= (den >= 0 ? d : -d);\n        den /= (den >= 0 ? d : -d);\n   \
    \ }\n};\n\n// verify : https://atcoder.jp/contests/abc168/submissions/39533747\n\
    // \u6F14\u7B97\u7D50\u679C\u306E\u5206\u5B50\u30FB\u5206\u6BCD\u304C\u3068\u3082\
    \u306B 64bit \u6574\u6570\u306E\u7BC4\u56F2\u3067\u306E\u307F\u52D5\u4F5C\u3092\
    \u4FDD\u8A3C\nclass fraction{\n  private:\n    long long num, den;\n\n    friend\
    \ fraction operator+(const fraction &a){ return a; }\n    friend fraction operator-(const\
    \ fraction &a){\n        fraction ret;\n        ret.raw_assign(-a.num, a.den);\n\
    \        return ret;\n    }\n\n    friend fraction operator+(const fraction &a,\
    \ const fraction &b){\n        assert(!(a.is_infinity() && b.is_infinity() &&\
    \ a.num * b.num == -1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\n        if(a.is_infinity())\
    \ {\n            return a;\n        }\n        else if(b.is_infinity()) {\n  \
    \          return b;\n        }\n        else {\n            return {(__int128_t)a.num\
    \ * b.den + (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};\n        }\n\
    \    }\n    friend fraction operator-(const fraction &a, const fraction &b){\n\
    \        assert(!(a.is_infinity() && b.is_infinity() && a.num * b.num == 1));\
    \ // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\n        if(a.is_infinity()) {\n   \
    \         return a;\n        }\n        else if(b.is_infinity()) {\n         \
    \   return -b;\n        }\n        else {\n            return {(__int128_t)a.num\
    \ * b.den - (__int128_t)b.num * a.den, (__int128_t)a.den * b.den};\n        }\n\
    \    }\n    friend const fraction operator*(const fraction &a, const fraction\
    \ &b){\n        assert(a.num != 0 || b.den != 0);\n        assert(a.den != 0 ||\
    \ b.num != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.den), gcd_tmp2\
    \ = std::gcd(b.num, a.den);\n        fraction ret;\n        ret.raw_assign((a.num\
    \ / gcd_tmp1) * (b.num / gcd_tmp2),\n            (a.den / gcd_tmp2) * (b.den /\
    \ gcd_tmp1));\n        return ret;\n    }\n    friend const fraction operator/(const\
    \ fraction &a, const fraction &b){\n        assert(a.num != 0 || b.num != 0);\n\
    \        assert(a.den != 0 || b.den != 0);\n        long long gcd_tmp1 = std::gcd(a.num,\
    \ b.num), gcd_tmp2 = std::gcd(b.den, a.den);\n        fraction ret;\n        ret.raw_assign((b.num\
    \ >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),\n            (b.num\
    \ >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));\n        return ret;\n\
    \    }\n\n    friend bool operator==(const fraction &a, const fraction &b){ return\
    \ a.num == b.num && a.den == b.den; }\n    friend bool operator!=(const fraction\
    \ &a, const fraction &b){ return a.num != b.num || a.den != b.den; }\n\n    friend\
    \ int compare_to(const fraction &a, const fraction &b) {\n        if((a.num >=\
    \ 0) ^ (b.num >= 0)) return a.num > b.num ? 1 : -1;\n        __int128_t lhs =\
    \ (__int128_t)a.num * b.den;\n        __int128_t rhs = (__int128_t)b.num * a.den;\n\
    \        if (lhs == rhs) return 0;\n        return lhs > rhs ? 1 : -1;\n    }\n\
    \n    friend bool operator>(const fraction &a, const fraction &b) { return compare_to(a,\
    \ b) > 0; }\n    friend bool operator>=(const fraction &a, const fraction &b)\
    \ { return compare_to(a, b) >= 0; }\n    friend bool operator<(const fraction\
    \ &a, const fraction &b) { return compare_to(a, b) < 0; }\n    friend bool operator<=(const\
    \ fraction &a, const fraction &b) { return compare_to(a, b) <= 0; }\n\n  public:\n\
    \    fraction(long long n) : num(n), den(1) {}\n    fraction(__int128_t numerator,\
    \ __int128_t denominator){\n        internal::simplify(numerator, denominator);\n\
    \        num = numerator, den = denominator;\n    }\n    fraction() : num(0),\
    \ den(1) {}\n\n    const fraction &operator=(const fraction &a){\n        num\
    \ = a.num, den = a.den;\n        return *this;\n    }\n    const fraction &operator+=(const\
    \ fraction &a){\n        return *this = *this + a;\n    }\n    const fraction\
    \ &operator-=(const fraction &a){\n        return *this = *this - a;\n    }\n\
    \    const fraction &operator*=(const fraction &a){\n        return *this = *this\
    \ * a;\n    }\n    const fraction &operator/=(const fraction &a){\n        return\
    \ *this = *this / a;\n    }\n\n    friend std::istream &operator>>(std::istream\
    \ &is, fraction &a){\n        std::string buf;\n        is >> buf;\n        __int128_t\
    \ num_tmp = 0, den_tmp = 0;\n        int i = (buf[0] == '-'), sz = buf.size();\n\
    \        for(; i < sz && buf[i] != '/'; i++) num_tmp = num_tmp * 10 + buf[i] -\
    \ '0';\n        if(i == sz) den_tmp = 1;\n        else for(i = i + 1; i < sz;\
    \ i++) den_tmp = den_tmp * 10 + buf[i] - '0';\n        if(buf[0] == '-') num_tmp\
    \ *= -1;\n        internal::simplify(num_tmp, den_tmp);\n        a.num = num_tmp,\
    \ a.den = den_tmp;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const fraction &a) {\n        if(a.den == 0) os << (a.num >= 0 ? \"inf\"\
    \ : \"-inf\");\n        else if(a.den == 1) os << a.num;\n        else os << a.num\
    \ << '/' << a.den;\n        return os;\n    }\n\n    // \u7D04\u5206\u3092\u7701\
    \u7565\u3057\u3066\u4EE3\u5165\u3059\u308B\n    fraction &raw_assign(long long\
    \ _num, long long _den){ \n        num = _num, den = _den;\n        return *this;\n\
    \    }\n    long long numerator() const { return num; }\n    long long denomitnator()\
    \ const { return den; }\n    long long floor() const { return num / den; }\n \
    \   long long ceil() const { return ((__int128_t)num + den - 1) / den; }\n   \
    \ double real() const { return (double)num / den; }\n    fraction abs() const\
    \ { return (*this >= 0 ? *this : -*this); } \n    fraction inverse() const {\n\
    \        fraction ret;\n        ret.raw_assign((num >= 0 ? den : -den), (num >=\
    \ 0 ? num : -num));\n        return ret;\n    }\n    int mod(int _mod) const {\n\
    \        assert(_mod > 0);\n        long long ret = num % _mod;\n        if(ret\
    \ < 0) ret += _mod;\n        return (ret *= mod_inverse(den, _mod)) %= _mod;\n\
    \    }\n    bool is_infinity() const { return (den == 0); }\n\n    static const\
    \ fraction M_INF, INF;\n};\nconst fraction fraction::M_INF(-1, 0), fraction::INF(1,\
    \ 0);\n\n\n#endif\n"
  dependsOn:
  - math/mod_inverse.hpp
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: standard/fraction.hpp
  requiredBy: []
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/fraction.hpp
layout: document
redirect_from:
- /library/standard/fraction.hpp
- /library/standard/fraction.hpp.html
title: standard/fraction.hpp
---
