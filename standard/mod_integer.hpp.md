---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/Bezout_coefficients.hpp
    title: math/Bezout_coefficients.hpp
  - icon: ':x:'
    path: math/mod_inverse.hpp
    title: math/mod_inverse.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"standard/mod_integer.hpp\"\n\n\n#include <iostream>\n\n\
    #line 1 \"math/mod_inverse.hpp\"\n\n\n#include <assert.h>\n\n#line 1 \"math/Bezout_coefficients.hpp\"\
    \n\n\n#include <cstdlib>\n#include <utility>\n\nnamespace internal {\nlong long\
    \ extgcd(long long a, long long b, long long &s, long long &t) {\n    if (b ==\
    \ 0) {\n        s = 1;\n        t = 0;\n        return a;\n    } else {\n    \
    \    auto d = std::lldiv(a, b);\n        long long tmp = extgcd(b, d.rem, t, s);\n\
    \        t -= d.quot * s;\n        return tmp;\n    }\n}\n} // namespace internal\n\
    \nstd::pair<long long, long long> Bezout_coefficients(long long a, long long b)\
    \ {\n    long long s, t;\n    internal::extgcd((a >= 0 ? a : -a), (b >= 0 ? b\
    \ : -b), s, t);\n    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n\n#line\
    \ 6 \"math/mod_inverse.hpp\"\n\nlong long mod_inverse(long long x, int mod) {\n\
    \    assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x,\
    \ mod);\n    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n\
    }\n\n\n#line 6 \"standard/mod_integer.hpp\"\n\n// mod_integer<P> a := P\u3092\u6CD5\
    \u3068\u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class\
    \ mod_integer {\n  private:\n    // \u5024\u306F\u5FC5\u305A 0 <= val < mod \u306B\
    \u4FDD\u305F\u308C\u308B\n    long long val;\n    friend mod_integer operator+(const\
    \ mod_integer &a) { return a; }\n    friend mod_integer operator-(const mod_integer\
    \ &a) { return -a.val; }\n    friend mod_integer operator+(const mod_integer &a,\
    \ const mod_integer &b) {\n        return mod_integer(a.val + b.val);\n    }\n\
    \    friend mod_integer operator-(const mod_integer &a, const mod_integer &b)\
    \ {\n        return mod_integer(a.val - b.val);\n    }\n    friend mod_integer\
    \ operator*(const mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val\
    \ * b.val);\n    }\n    friend mod_integer operator/(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val * mod_inverse(b.val, mod));\n\
    \    }\n\n    friend bool operator==(const mod_integer &a, const mod_integer &b)\
    \ {\n        return a.val == b.val;\n    }\n    friend bool operator!=(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val != b.val;\n    }\n\n    //\
    \ \u4FBF\u5B9C\u7684\u306A\u5B9A\u7FA9\u3067\u3042\u308B\u3053\u3068\u306B\u6CE8\
    \u610F\n    friend bool operator>(const mod_integer &a, const mod_integer &b)\
    \ {\n        return a.val > b.val;\n    }\n    friend bool operator>=(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val >= b.val;\n    }\n    friend\
    \ bool operator<(const mod_integer &a, const mod_integer &b) {\n        return\
    \ a.val < b.val;\n    }\n    friend bool operator<=(const mod_integer &a, const\
    \ mod_integer &b) {\n        return a.val <= b.val;\n    }\n\n  public:\n    mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    mod_integer() : val(0) {}\n    int value() const { return\
    \ (int)val; }\n\n    const mod_integer &operator=(const mod_integer &a) {\n  \
    \      val = a.val;\n        return *this;\n    }\n    const mod_integer &operator+=(const\
    \ mod_integer &a) {\n        val += a.val;\n        if (val >= mod)\n        \
    \    val -= mod;\n        return *this;\n    }\n    const mod_integer &operator-=(const\
    \ mod_integer &a) {\n        val -= a.val;\n        if (val < 0)\n           \
    \ val += mod;\n        return *this;\n    }\n    const mod_integer &operator*=(const\
    \ mod_integer &a) {\n        (val *= a.val) %= mod;\n        return *this;\n \
    \   }\n    const mod_integer &operator/=(const mod_integer &a) {\n        (val\
    \ *= mod_inverse(a.val, mod)) %= mod;\n        return *this;\n    }\n\n    friend\
    \ std::istream &operator>>(std::istream &is, mod_integer &a) {\n        is >>\
    \ a.val;\n        a.val %= mod;\n        if (a.val < 0)\n            a.val +=\
    \ mod;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const mod_integer &a) {\n        os << a.val;\n        return os;\n   \
    \ }\n};\n\n\n"
  code: "#ifndef MOD_INTEGER\n#define MOD_INTEGER\n#include <iostream>\n\n#include\
    \ \"../math/mod_inverse.hpp\"\n\n// mod_integer<P> a := P\u3092\u6CD5\u3068\u3059\
    \u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class mod_integer\
    \ {\n  private:\n    // \u5024\u306F\u5FC5\u305A 0 <= val < mod \u306B\u4FDD\u305F\
    \u308C\u308B\n    long long val;\n    friend mod_integer operator+(const mod_integer\
    \ &a) { return a; }\n    friend mod_integer operator-(const mod_integer &a) {\
    \ return -a.val; }\n    friend mod_integer operator+(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val + b.val);\n    }\n    friend\
    \ mod_integer operator-(const mod_integer &a, const mod_integer &b) {\n      \
    \  return mod_integer(a.val - b.val);\n    }\n    friend mod_integer operator*(const\
    \ mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val *\
    \ b.val);\n    }\n    friend mod_integer operator/(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val * mod_inverse(b.val, mod));\n\
    \    }\n\n    friend bool operator==(const mod_integer &a, const mod_integer &b)\
    \ {\n        return a.val == b.val;\n    }\n    friend bool operator!=(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val != b.val;\n    }\n\n    //\
    \ \u4FBF\u5B9C\u7684\u306A\u5B9A\u7FA9\u3067\u3042\u308B\u3053\u3068\u306B\u6CE8\
    \u610F\n    friend bool operator>(const mod_integer &a, const mod_integer &b)\
    \ {\n        return a.val > b.val;\n    }\n    friend bool operator>=(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val >= b.val;\n    }\n    friend\
    \ bool operator<(const mod_integer &a, const mod_integer &b) {\n        return\
    \ a.val < b.val;\n    }\n    friend bool operator<=(const mod_integer &a, const\
    \ mod_integer &b) {\n        return a.val <= b.val;\n    }\n\n  public:\n    mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    mod_integer() : val(0) {}\n    int value() const { return\
    \ (int)val; }\n\n    const mod_integer &operator=(const mod_integer &a) {\n  \
    \      val = a.val;\n        return *this;\n    }\n    const mod_integer &operator+=(const\
    \ mod_integer &a) {\n        val += a.val;\n        if (val >= mod)\n        \
    \    val -= mod;\n        return *this;\n    }\n    const mod_integer &operator-=(const\
    \ mod_integer &a) {\n        val -= a.val;\n        if (val < 0)\n           \
    \ val += mod;\n        return *this;\n    }\n    const mod_integer &operator*=(const\
    \ mod_integer &a) {\n        (val *= a.val) %= mod;\n        return *this;\n \
    \   }\n    const mod_integer &operator/=(const mod_integer &a) {\n        (val\
    \ *= mod_inverse(a.val, mod)) %= mod;\n        return *this;\n    }\n\n    friend\
    \ std::istream &operator>>(std::istream &is, mod_integer &a) {\n        is >>\
    \ a.val;\n        a.val %= mod;\n        if (a.val < 0)\n            a.val +=\
    \ mod;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const mod_integer &a) {\n        os << a.val;\n        return os;\n   \
    \ }\n};\n\n#endif\n"
  dependsOn:
  - math/mod_inverse.hpp
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: standard/mod_integer.hpp
  requiredBy: []
  timestamp: '2023-06-19 01:40:27+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/jsc2021-g.test.cpp
documentation_of: standard/mod_integer.hpp
layout: document
redirect_from:
- /library/standard/mod_integer.hpp
- /library/standard/mod_integer.hpp.html
title: standard/mod_integer.hpp
---
