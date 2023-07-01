---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/Bezout_coefficients.hpp
    title: math/Bezout_coefficients.hpp
  - icon: ':x:'
    path: math/mod_inverse.hpp
    title: math/mod_inverse.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/binomial_coefficients.hpp
    title: math/binomial_coefficients.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"standard/mod_integer.hpp\"\n#include <iostream>\n#include\
    \ <queue>\n#include <utility>\n\n#line 2 \"math/mod_inverse.hpp\"\n#include <assert.h>\n\
    \n#line 2 \"math/Bezout_coefficients.hpp\"\n#include <cstdlib>\n#line 4 \"math/Bezout_coefficients.hpp\"\
    \n\nnamespace internal {\nlong long extgcd(long long a, long long b, long long\
    \ &s, long long &t) {\n    if (b == 0) {\n        s = 1;\n        t = 0;\n   \
    \     return a;\n    } else {\n        auto d = std::lldiv(a, b);\n        long\
    \ long tmp = extgcd(b, d.rem, t, s);\n        t -= d.quot * s;\n        return\
    \ tmp;\n    }\n}\n} // namespace internal\n\nstd::pair<long long, long long> Bezout_coefficients(long\
    \ long a, long long b) {\n    long long s, t;\n    internal::extgcd((a >= 0 ?\
    \ a : -a), (b >= 0 ? b : -b), s, t);\n    return {(a >= 0 ? s : -s), (b >= 0 ?\
    \ t : -t)};\n}\n#line 5 \"math/mod_inverse.hpp\"\n\nlong long mod_inverse(long\
    \ long x, int mod) {\n    assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x,\
    \ mod);\n    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n\
    }\n#line 7 \"standard/mod_integer.hpp\"\n\n// mod_integer<P> a := P\u3092\u6CD5\
    \u3068\u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class\
    \ mod_integer {\n  private:\n    long long val; // \u5024\u306F\u5FC5\u305A 0\
    \ <= val < mod \u306B\u4FDD\u305F\u308C\u308B\n    static inline std::deque<std::pair<int,\
    \ int>>\n        modinv_cache; // \u9006\u5143\u306E\u30AD\u30E3\u30C3\u30B7\u30E5\
    \n    static inline const int cache_size = 8;\n    friend mod_integer operator+(const\
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
    \ map \u3068\u304B\u306B\u4E57\u305B\u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\
    \u7684\u306B\u5B9A\u7FA9\n    friend bool operator<(const mod_integer &a, const\
    \ mod_integer &b) {\n        return a.val < b.val;\n    }\n\n  public:\n    mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    mod_integer() : val(0) {}\n    int value() const { return\
    \ (int)val; }\n\n    mod_integer &operator=(const mod_integer &a) = default;\n\
    \    mod_integer &operator+=(const mod_integer &a) {\n        val += a.val;\n\
    \        if (val >= mod)\n            val -= mod;\n        return *this;\n   \
    \ }\n    mod_integer &operator-=(const mod_integer &a) {\n        val -= a.val;\n\
    \        if (val < 0)\n            val += mod;\n        return *this;\n    }\n\
    \    mod_integer &operator*=(const mod_integer &a) {\n        (val *= a.val) %=\
    \ mod;\n        return *this;\n    }\n    mod_integer &operator/=(const mod_integer\
    \ &a) {\n        bool found = false;\n        for (auto &[k, v] : modinv_cache)\n\
    \            if (k == a.val) {\n                found = true;\n              \
    \  (val *= v) %= mod;\n                break;\n            }\n        if (!found)\
    \ {\n            int inv = mod_inverse(a.val, mod);\n            (val *= inv)\
    \ %= mod;\n            modinv_cache.push_back({a.val, inv});\n            if ((int)modinv_cache.size()\
    \ > cache_size)\n                modinv_cache.pop_front();\n        }\n      \
    \  return *this;\n    }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n        if (a.val\
    \ < 0)\n            a.val += mod;\n        return is;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const mod_integer &a) {\n        os << a.val;\n\
    \        return os;\n    }\n};\n\nusing mint = mod_integer<1000000007>;\nusing\
    \ _mint = mod_integer<998244353>;\n"
  code: "#pragma once\n#include <iostream>\n#include <queue>\n#include <utility>\n\
    \n#include \"../math/mod_inverse.hpp\"\n\n// mod_integer<P> a := P\u3092\u6CD5\
    \u3068\u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class\
    \ mod_integer {\n  private:\n    long long val; // \u5024\u306F\u5FC5\u305A 0\
    \ <= val < mod \u306B\u4FDD\u305F\u308C\u308B\n    static inline std::deque<std::pair<int,\
    \ int>>\n        modinv_cache; // \u9006\u5143\u306E\u30AD\u30E3\u30C3\u30B7\u30E5\
    \n    static inline const int cache_size = 8;\n    friend mod_integer operator+(const\
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
    \ map \u3068\u304B\u306B\u4E57\u305B\u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\
    \u7684\u306B\u5B9A\u7FA9\n    friend bool operator<(const mod_integer &a, const\
    \ mod_integer &b) {\n        return a.val < b.val;\n    }\n\n  public:\n    mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    mod_integer() : val(0) {}\n    int value() const { return\
    \ (int)val; }\n\n    mod_integer &operator=(const mod_integer &a) = default;\n\
    \    mod_integer &operator+=(const mod_integer &a) {\n        val += a.val;\n\
    \        if (val >= mod)\n            val -= mod;\n        return *this;\n   \
    \ }\n    mod_integer &operator-=(const mod_integer &a) {\n        val -= a.val;\n\
    \        if (val < 0)\n            val += mod;\n        return *this;\n    }\n\
    \    mod_integer &operator*=(const mod_integer &a) {\n        (val *= a.val) %=\
    \ mod;\n        return *this;\n    }\n    mod_integer &operator/=(const mod_integer\
    \ &a) {\n        bool found = false;\n        for (auto &[k, v] : modinv_cache)\n\
    \            if (k == a.val) {\n                found = true;\n              \
    \  (val *= v) %= mod;\n                break;\n            }\n        if (!found)\
    \ {\n            int inv = mod_inverse(a.val, mod);\n            (val *= inv)\
    \ %= mod;\n            modinv_cache.push_back({a.val, inv});\n            if ((int)modinv_cache.size()\
    \ > cache_size)\n                modinv_cache.pop_front();\n        }\n      \
    \  return *this;\n    }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n        if (a.val\
    \ < 0)\n            a.val += mod;\n        return is;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const mod_integer &a) {\n        os << a.val;\n\
    \        return os;\n    }\n};\n\nusing mint = mod_integer<1000000007>;\nusing\
    \ _mint = mod_integer<998244353>;\n"
  dependsOn:
  - math/mod_inverse.hpp
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: standard/mod_integer.hpp
  requiredBy:
  - math/binomial_coefficients.hpp
  timestamp: '2023-07-01 19:17:15+09:00'
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
