---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: standard/mod_integer.hpp
    title: standard/mod_integer.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc168/submissions/39533747
  bundledCode: "#line 2 \"standard/fraction.hpp\"\n#include <assert.h>\n\n#include\
    \ <iostream>\n#include <numeric>\n\n#line 3 \"standard/mod_integer.hpp\"\n#include\
    \ <queue>\n#include <utility>\n\ninline long long mod_inverse(long long a, int\
    \ mod) {\n    assert(mod > 0);\n    long long b = mod, u = 1, v = 0;\n    while\
    \ (b) {\n        long long t = a / b;\n        a -= t * b, std::swap(a, b);\n\
    \        u -= t * v, std::swap(u, v);\n    }\n    u %= mod;\n    if (u < 0)\n\
    \        u += mod;\n    return u;\n}\n\n// mod_integer<P> a := P\u3092\u6CD5\u3068\
    \u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class mod_integer\
    \ {\n  private:\n    long long val; // \u5024\u306F\u5FC5\u305A 0 <= val < mod\
    \ \u306B\u4FDD\u305F\u308C\u308B\n    friend mod_integer operator+(const mod_integer\
    \ &a) { return a; }\n    friend mod_integer operator-(const mod_integer &a) {\
    \ return -a.val; }\n    friend mod_integer operator+(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val + b.val);\n    }\n    friend\
    \ mod_integer operator-(const mod_integer &a, const mod_integer &b) {\n      \
    \  return mod_integer(a.val - b.val);\n    }\n    friend mod_integer operator*(const\
    \ mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val *\
    \ b.val);\n    }\n    friend mod_integer operator/(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer((a.val * mod_inverse(b.val, mod))\
    \ % mod);\n    }\n\n    friend bool operator==(const mod_integer &a, const mod_integer\
    \ &b) {\n        return a.val == b.val;\n    }\n    friend bool operator!=(const\
    \ mod_integer &a, const mod_integer &b) {\n        return a.val != b.val;\n  \
    \  }\n\n    // map \u3068\u304B\u306B\u4E57\u305B\u305F\u3044\u306E\u3067\u3001\
    \u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\n    friend bool operator<(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val < b.val;\n    }\n\n  public:\n\
    \    mod_integer(long long n) : val(n) {\n        val %= mod;\n        if (val\
    \ < 0)\n            val += mod;\n    }\n    mod_integer() : val(0) {}\n    int\
    \ value() const { return (int)val; }\n\n    mod_integer &operator=(const mod_integer\
    \ &a) = default;\n    mod_integer &operator+=(const mod_integer &a) {\n      \
    \  val += a.val;\n        if (val >= mod)\n            val -= mod;\n        return\
    \ *this;\n    }\n    mod_integer &operator-=(const mod_integer &a) {\n       \
    \ val -= a.val;\n        if (val < 0)\n            val += mod;\n        return\
    \ *this;\n    }\n    mod_integer &operator*=(const mod_integer &a) {\n       \
    \ (val *= a.val) %= mod;\n        return *this;\n    }\n    mod_integer &operator/=(const\
    \ mod_integer &a) {\n        (val *= mod_inverse(a.val, mod)) %= mod;\n      \
    \  return *this;\n    }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n        if (a.val\
    \ < 0)\n            a.val += mod;\n        return is;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const mod_integer &a) {\n        os << a.val;\n\
    \        return os;\n    }\n};\n\n// d_mod_integer<P> a := P\u3092\u6CD5\u3068\
    \u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int id> class dynamic_mod_integer\
    \ {\n  private:\n    using d_mod_integer = dynamic_mod_integer<id>;\n    static\
    \ inline int mod = 998244353;\n    long long val; // \u5024\u306F\u5FC5\u305A\
    \ 0 <= val < mod \u306B\u4FDD\u305F\u308C\u308B\n    friend d_mod_integer operator+(const\
    \ d_mod_integer &a) { return a; }\n    friend d_mod_integer operator-(const d_mod_integer\
    \ &a) { return -a.val; }\n    friend d_mod_integer operator+(const d_mod_integer\
    \ &a, const d_mod_integer &b) {\n        return d_mod_integer(a.val + b.val);\n\
    \    }\n    friend d_mod_integer operator-(const d_mod_integer &a, const d_mod_integer\
    \ &b) {\n        return d_mod_integer(a.val - b.val);\n    }\n    friend d_mod_integer\
    \ operator*(const d_mod_integer &a, const d_mod_integer &b) {\n        return\
    \ d_mod_integer(a.val * b.val);\n    }\n    friend d_mod_integer operator/(const\
    \ d_mod_integer &a, const d_mod_integer &b) {\n        return d_mod_integer((a.val\
    \ * mod_inverse(b.val, mod)) % mod);\n    }\n\n    friend bool operator==(const\
    \ d_mod_integer &a, const d_mod_integer &b) {\n        return a.val == b.val;\n\
    \    }\n    friend bool operator!=(const d_mod_integer &a, const d_mod_integer\
    \ &b) {\n        return a.val != b.val;\n    }\n\n    // map \u3068\u304B\u306B\
    \u4E57\u305B\u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\
    \n    friend bool operator<(const d_mod_integer &a, const d_mod_integer &b) {\n\
    \        return a.val < b.val;\n    }\n\n  public:\n    dynamic_mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    dynamic_mod_integer() : val(0) {}\n    int value() const\
    \ { return (int)val; }\n    static void set_mod(int _mod) {\n        assert(_mod\
    \ >= 0);\n        mod = _mod;\n    }\n\n    d_mod_integer &operator=(const d_mod_integer\
    \ &a) = default;\n    d_mod_integer &operator+=(const d_mod_integer &a) {\n  \
    \      val += a.val;\n        if (val >= mod)\n            val -= mod;\n     \
    \   return *this;\n    }\n    d_mod_integer &operator-=(const d_mod_integer &a)\
    \ {\n        val -= a.val;\n        if (val < 0)\n            val += mod;\n  \
    \      return *this;\n    }\n    d_mod_integer &operator*=(const d_mod_integer\
    \ &a) {\n        (val *= a.val) %= mod;\n        return *this;\n    }\n    d_mod_integer\
    \ &operator/=(const d_mod_integer &a) {\n        (val *= mod_inverse(a.val, mod))\
    \ %= mod;\n        return *this;\n    }\n\n    friend std::istream &operator>>(std::istream\
    \ &is, d_mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n    \
    \    if (a.val < 0)\n            a.val += mod;\n        return is;\n    }\n  \
    \  friend std::ostream &operator<<(std::ostream &os, const d_mod_integer &a) {\n\
    \        os << a.val;\n        return os;\n    }\n};\n\nusing mint = mod_integer<1000000007>;\n\
    using _mint = mod_integer<998244353>;\nusing dmint = dynamic_mod_integer<-1>;\n\
    #line 8 \"standard/fraction.hpp\"\n\nnamespace internal {\n\n__int128_t __gcd(__int128_t\
    \ a, __int128_t b) {\n    if (a % b == 0)\n        return b;\n    return __gcd(b,\
    \ a % b);\n}\n\n// \u7D76\u5BFE\u5024\u306E GCD \u3092\u8FD4\u3059\u3002\u7247\
    \u65B9\u304C 0 \u306A\u3089\u3082\u3046\u4E00\u65B9\u306E\u7D76\u5BFE\u5024\u3002\
    \n__int128_t gcd(__int128_t a, __int128_t b) {\n    if (b == 0)\n        return\
    \ (a >= 0 ? a : -a);\n    return internal::__gcd((a >= 0 ? a : -a), (b >= 0 ?\
    \ b : -b));\n}\n\ninline void simplify(__int128_t &num, __int128_t &den) {\n \
    \   __int128_t d = internal::gcd(num, den);\n    num /= (den >= 0 ? d : -d);\n\
    \    den /= (den >= 0 ? d : -d);\n}\n}; // namespace internal\n\n// verify : https://atcoder.jp/contests/abc168/submissions/39533747\n\
    // \u6F14\u7B97\u7D50\u679C\u306E\u5206\u5B50\u30FB\u5206\u6BCD\u304C\u3068\u3082\
    \u306B 64bit \u6574\u6570\u306E\u7BC4\u56F2\u3067\u306E\u307F\u52D5\u4F5C\u3092\
    \u4FDD\u8A3C\nclass fraction {\n  private:\n    long long num, den;\n\n    friend\
    \ fraction operator+(const fraction &a) { return a; }\n    friend fraction operator-(const\
    \ fraction &a) {\n        fraction ret;\n        ret.raw_assign(-a.num, a.den);\n\
    \        return ret;\n    }\n\n    friend fraction operator+(const fraction &a,\
    \ const fraction &b) {\n        assert(!(a.is_infinity() && b.is_infinity() &&\n\
    \                 a.num * b.num == -1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\
    \n        if (a.is_infinity()) {\n            return a;\n        } else if (b.is_infinity())\
    \ {\n            return b;\n        } else {\n            return {(__int128_t)a.num\
    \ * b.den + (__int128_t)b.num * a.den,\n                    (__int128_t)a.den\
    \ * b.den};\n        }\n    }\n    friend fraction operator-(const fraction &a,\
    \ const fraction &b) {\n        assert(!(a.is_infinity() && b.is_infinity() &&\n\
    \                 a.num * b.num == 1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\
    \n        if (a.is_infinity()) {\n            return a;\n        } else if (b.is_infinity())\
    \ {\n            return -b;\n        } else {\n            return {(__int128_t)a.num\
    \ * b.den - (__int128_t)b.num * a.den,\n                    (__int128_t)a.den\
    \ * b.den};\n        }\n    }\n    friend fraction operator*(const fraction &a,\
    \ const fraction &b) {\n        assert(a.num != 0 || b.den != 0);\n        assert(a.den\
    \ != 0 || b.num != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.den),\n\
    \                  gcd_tmp2 = std::gcd(b.num, a.den);\n        fraction ret;\n\
    \        ret.raw_assign((a.num / gcd_tmp1) * (b.num / gcd_tmp2),\n           \
    \            (a.den / gcd_tmp2) * (b.den / gcd_tmp1));\n        return ret;\n\
    \    }\n    friend fraction operator/(const fraction &a, const fraction &b) {\n\
    \        assert(a.num != 0 || b.num != 0);\n        assert(a.den != 0 || b.den\
    \ != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.num),\n             \
    \     gcd_tmp2 = std::gcd(b.den, a.den);\n        fraction ret;\n        ret.raw_assign(\n\
    \            (b.num >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),\n\
    \            (b.num >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));\n\
    \        return ret;\n    }\n\n    friend bool operator==(const fraction &a, const\
    \ fraction &b) {\n        return a.num == b.num && a.den == b.den;\n    }\n  \
    \  friend bool operator!=(const fraction &a, const fraction &b) {\n        return\
    \ a.num != b.num || a.den != b.den;\n    }\n\n    friend int compare_to(const\
    \ fraction &a, const fraction &b) {\n        if ((a.num >= 0) ^ (b.num >= 0))\n\
    \            return a.num > b.num ? 1 : -1;\n        __int128_t lhs = (__int128_t)a.num\
    \ * b.den;\n        __int128_t rhs = (__int128_t)b.num * a.den;\n        if (lhs\
    \ == rhs)\n            return 0;\n        return lhs > rhs ? 1 : -1;\n    }\n\n\
    \    friend bool operator>(const fraction &a, const fraction &b) {\n        return\
    \ compare_to(a, b) > 0;\n    }\n    friend bool operator>=(const fraction &a,\
    \ const fraction &b) {\n        return compare_to(a, b) >= 0;\n    }\n    friend\
    \ bool operator<(const fraction &a, const fraction &b) {\n        return compare_to(a,\
    \ b) < 0;\n    }\n    friend bool operator<=(const fraction &a, const fraction\
    \ &b) {\n        return compare_to(a, b) <= 0;\n    }\n\n  public:\n    fraction(long\
    \ long n) : num(n), den(1) {}\n    fraction(__int128_t numerator, __int128_t denominator)\
    \ {\n        internal::simplify(numerator, denominator);\n        num = numerator,\
    \ den = denominator;\n    }\n    fraction() : num(0), den(1) {}\n\n    fraction\
    \ &operator=(const fraction &a) = default;\n    fraction &operator+=(const fraction\
    \ &a) { return *this = *this + a; }\n    fraction &operator-=(const fraction &a)\
    \ { return *this = *this - a; }\n    fraction &operator*=(const fraction &a) {\
    \ return *this = *this * a; }\n    fraction &operator/=(const fraction &a) { return\
    \ *this = *this / a; }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ fraction &a) {\n        std::string buf;\n        is >> buf;\n        __int128_t\
    \ num_tmp = 0, den_tmp = 0;\n        int i = (buf[0] == '-'), sz = buf.size();\n\
    \        for (; i < sz && buf[i] != '/'; i++)\n            num_tmp = num_tmp *\
    \ 10 + buf[i] - '0';\n        if (i == sz)\n            den_tmp = 1;\n       \
    \ else\n            for (i = i + 1; i < sz; i++)\n                den_tmp = den_tmp\
    \ * 10 + buf[i] - '0';\n        if (buf[0] == '-')\n            num_tmp *= -1;\n\
    \        internal::simplify(num_tmp, den_tmp);\n        a.num = num_tmp, a.den\
    \ = den_tmp;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const fraction &a) {\n        if (a.den == 0)\n            os << (a.num\
    \ >= 0 ? \"inf\" : \"-inf\");\n        else if (a.den == 1)\n            os <<\
    \ a.num;\n        else\n            os << a.num << '/' << a.den;\n        return\
    \ os;\n    }\n\n    // \u7D04\u5206\u3092\u7701\u7565\u3057\u3066\u4EE3\u5165\u3059\
    \u308B\n    fraction &raw_assign(long long _num, long long _den) {\n        num\
    \ = _num, den = _den;\n        return *this;\n    }\n    long long numerator()\
    \ const { return num; }\n    long long denomitnator() const { return den; }\n\
    \    long long floor() const { return num / den; }\n    long long ceil() const\
    \ { return ((__int128_t)num + den - 1) / den; }\n    double real() const { return\
    \ (double)num / den; }\n    fraction abs() const { return (*this >= 0 ? *this\
    \ : -*this); }\n    fraction inverse() const {\n        fraction ret;\n      \
    \  ret.raw_assign((num >= 0 ? den : -den), (num >= 0 ? num : -num));\n       \
    \ return ret;\n    }\n    int mod(int _mod) const {\n        assert(_mod > 0);\n\
    \        long long ret = num % _mod;\n        if (ret < 0)\n            ret +=\
    \ _mod;\n        return (ret *= mod_inverse(den, _mod)) %= _mod;\n    }\n    bool\
    \ is_infinity() const { return (den == 0); }\n\n    static const fraction M_INF,\
    \ INF;\n};\nconst fraction fraction::M_INF(-1, 0), fraction::INF(1, 0);\n"
  code: "#pragma once\n#include <assert.h>\n\n#include <iostream>\n#include <numeric>\n\
    \n#include \"mod_integer.hpp\"\n\nnamespace internal {\n\n__int128_t __gcd(__int128_t\
    \ a, __int128_t b) {\n    if (a % b == 0)\n        return b;\n    return __gcd(b,\
    \ a % b);\n}\n\n// \u7D76\u5BFE\u5024\u306E GCD \u3092\u8FD4\u3059\u3002\u7247\
    \u65B9\u304C 0 \u306A\u3089\u3082\u3046\u4E00\u65B9\u306E\u7D76\u5BFE\u5024\u3002\
    \n__int128_t gcd(__int128_t a, __int128_t b) {\n    if (b == 0)\n        return\
    \ (a >= 0 ? a : -a);\n    return internal::__gcd((a >= 0 ? a : -a), (b >= 0 ?\
    \ b : -b));\n}\n\ninline void simplify(__int128_t &num, __int128_t &den) {\n \
    \   __int128_t d = internal::gcd(num, den);\n    num /= (den >= 0 ? d : -d);\n\
    \    den /= (den >= 0 ? d : -d);\n}\n}; // namespace internal\n\n// verify : https://atcoder.jp/contests/abc168/submissions/39533747\n\
    // \u6F14\u7B97\u7D50\u679C\u306E\u5206\u5B50\u30FB\u5206\u6BCD\u304C\u3068\u3082\
    \u306B 64bit \u6574\u6570\u306E\u7BC4\u56F2\u3067\u306E\u307F\u52D5\u4F5C\u3092\
    \u4FDD\u8A3C\nclass fraction {\n  private:\n    long long num, den;\n\n    friend\
    \ fraction operator+(const fraction &a) { return a; }\n    friend fraction operator-(const\
    \ fraction &a) {\n        fraction ret;\n        ret.raw_assign(-a.num, a.den);\n\
    \        return ret;\n    }\n\n    friend fraction operator+(const fraction &a,\
    \ const fraction &b) {\n        assert(!(a.is_infinity() && b.is_infinity() &&\n\
    \                 a.num * b.num == -1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\
    \n        if (a.is_infinity()) {\n            return a;\n        } else if (b.is_infinity())\
    \ {\n            return b;\n        } else {\n            return {(__int128_t)a.num\
    \ * b.den + (__int128_t)b.num * a.den,\n                    (__int128_t)a.den\
    \ * b.den};\n        }\n    }\n    friend fraction operator-(const fraction &a,\
    \ const fraction &b) {\n        assert(!(a.is_infinity() && b.is_infinity() &&\n\
    \                 a.num * b.num == 1)); // \u4E0D\u5B9A\u5F62\u306F\u30C0\u30E1\
    \n        if (a.is_infinity()) {\n            return a;\n        } else if (b.is_infinity())\
    \ {\n            return -b;\n        } else {\n            return {(__int128_t)a.num\
    \ * b.den - (__int128_t)b.num * a.den,\n                    (__int128_t)a.den\
    \ * b.den};\n        }\n    }\n    friend fraction operator*(const fraction &a,\
    \ const fraction &b) {\n        assert(a.num != 0 || b.den != 0);\n        assert(a.den\
    \ != 0 || b.num != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.den),\n\
    \                  gcd_tmp2 = std::gcd(b.num, a.den);\n        fraction ret;\n\
    \        ret.raw_assign((a.num / gcd_tmp1) * (b.num / gcd_tmp2),\n           \
    \            (a.den / gcd_tmp2) * (b.den / gcd_tmp1));\n        return ret;\n\
    \    }\n    friend fraction operator/(const fraction &a, const fraction &b) {\n\
    \        assert(a.num != 0 || b.num != 0);\n        assert(a.den != 0 || b.den\
    \ != 0);\n        long long gcd_tmp1 = std::gcd(a.num, b.num),\n             \
    \     gcd_tmp2 = std::gcd(b.den, a.den);\n        fraction ret;\n        ret.raw_assign(\n\
    \            (b.num >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2),\n\
    \            (b.num >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1));\n\
    \        return ret;\n    }\n\n    friend bool operator==(const fraction &a, const\
    \ fraction &b) {\n        return a.num == b.num && a.den == b.den;\n    }\n  \
    \  friend bool operator!=(const fraction &a, const fraction &b) {\n        return\
    \ a.num != b.num || a.den != b.den;\n    }\n\n    friend int compare_to(const\
    \ fraction &a, const fraction &b) {\n        if ((a.num >= 0) ^ (b.num >= 0))\n\
    \            return a.num > b.num ? 1 : -1;\n        __int128_t lhs = (__int128_t)a.num\
    \ * b.den;\n        __int128_t rhs = (__int128_t)b.num * a.den;\n        if (lhs\
    \ == rhs)\n            return 0;\n        return lhs > rhs ? 1 : -1;\n    }\n\n\
    \    friend bool operator>(const fraction &a, const fraction &b) {\n        return\
    \ compare_to(a, b) > 0;\n    }\n    friend bool operator>=(const fraction &a,\
    \ const fraction &b) {\n        return compare_to(a, b) >= 0;\n    }\n    friend\
    \ bool operator<(const fraction &a, const fraction &b) {\n        return compare_to(a,\
    \ b) < 0;\n    }\n    friend bool operator<=(const fraction &a, const fraction\
    \ &b) {\n        return compare_to(a, b) <= 0;\n    }\n\n  public:\n    fraction(long\
    \ long n) : num(n), den(1) {}\n    fraction(__int128_t numerator, __int128_t denominator)\
    \ {\n        internal::simplify(numerator, denominator);\n        num = numerator,\
    \ den = denominator;\n    }\n    fraction() : num(0), den(1) {}\n\n    fraction\
    \ &operator=(const fraction &a) = default;\n    fraction &operator+=(const fraction\
    \ &a) { return *this = *this + a; }\n    fraction &operator-=(const fraction &a)\
    \ { return *this = *this - a; }\n    fraction &operator*=(const fraction &a) {\
    \ return *this = *this * a; }\n    fraction &operator/=(const fraction &a) { return\
    \ *this = *this / a; }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ fraction &a) {\n        std::string buf;\n        is >> buf;\n        __int128_t\
    \ num_tmp = 0, den_tmp = 0;\n        int i = (buf[0] == '-'), sz = buf.size();\n\
    \        for (; i < sz && buf[i] != '/'; i++)\n            num_tmp = num_tmp *\
    \ 10 + buf[i] - '0';\n        if (i == sz)\n            den_tmp = 1;\n       \
    \ else\n            for (i = i + 1; i < sz; i++)\n                den_tmp = den_tmp\
    \ * 10 + buf[i] - '0';\n        if (buf[0] == '-')\n            num_tmp *= -1;\n\
    \        internal::simplify(num_tmp, den_tmp);\n        a.num = num_tmp, a.den\
    \ = den_tmp;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const fraction &a) {\n        if (a.den == 0)\n            os << (a.num\
    \ >= 0 ? \"inf\" : \"-inf\");\n        else if (a.den == 1)\n            os <<\
    \ a.num;\n        else\n            os << a.num << '/' << a.den;\n        return\
    \ os;\n    }\n\n    // \u7D04\u5206\u3092\u7701\u7565\u3057\u3066\u4EE3\u5165\u3059\
    \u308B\n    fraction &raw_assign(long long _num, long long _den) {\n        num\
    \ = _num, den = _den;\n        return *this;\n    }\n    long long numerator()\
    \ const { return num; }\n    long long denomitnator() const { return den; }\n\
    \    long long floor() const { return num / den; }\n    long long ceil() const\
    \ { return ((__int128_t)num + den - 1) / den; }\n    double real() const { return\
    \ (double)num / den; }\n    fraction abs() const { return (*this >= 0 ? *this\
    \ : -*this); }\n    fraction inverse() const {\n        fraction ret;\n      \
    \  ret.raw_assign((num >= 0 ? den : -den), (num >= 0 ? num : -num));\n       \
    \ return ret;\n    }\n    int mod(int _mod) const {\n        assert(_mod > 0);\n\
    \        long long ret = num % _mod;\n        if (ret < 0)\n            ret +=\
    \ _mod;\n        return (ret *= mod_inverse(den, _mod)) %= _mod;\n    }\n    bool\
    \ is_infinity() const { return (den == 0); }\n\n    static const fraction M_INF,\
    \ INF;\n};\nconst fraction fraction::M_INF(-1, 0), fraction::INF(1, 0);\n"
  dependsOn:
  - standard/mod_integer.hpp
  isVerificationFile: false
  path: standard/fraction.hpp
  requiredBy: []
  timestamp: '2023-08-11 23:12:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/fraction.hpp
layout: document
redirect_from:
- /library/standard/fraction.hpp
- /library/standard/fraction.hpp.html
title: standard/fraction.hpp
---
