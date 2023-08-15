---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/enumeration_utility.hpp
    title: math/enumeration_utility.hpp
  - icon: ':heavy_check_mark:'
    path: math/totient.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\
      \u6570"
  - icon: ':warning:'
    path: standard/fraction.hpp
    title: standard/fraction.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ntl-1-d.test.cpp
    title: test/ntl-1-d.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"standard/mod_integer.hpp\"\n#include <iostream>\n#include\
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
    \ &a,\n                                   const d_mod_integer &b) {\n        return\
    \ d_mod_integer(a.val + b.val);\n    }\n    friend d_mod_integer operator-(const\
    \ d_mod_integer &a,\n                                   const d_mod_integer &b)\
    \ {\n        return d_mod_integer(a.val - b.val);\n    }\n    friend d_mod_integer\
    \ operator*(const d_mod_integer &a,\n                                   const\
    \ d_mod_integer &b) {\n        return d_mod_integer(a.val * b.val);\n    }\n \
    \   friend d_mod_integer operator/(const d_mod_integer &a,\n                 \
    \                  const d_mod_integer &b) {\n        return d_mod_integer((a.val\
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
    using _mint = mod_integer<998244353>;\nusing dmint = dynamic_mod_integer<-1>;\n"
  code: "#pragma once\n#include <iostream>\n#include <queue>\n#include <utility>\n\
    \ninline long long mod_inverse(long long a, int mod) {\n    assert(mod > 0);\n\
    \    long long b = mod, u = 1, v = 0;\n    while (b) {\n        long long t =\
    \ a / b;\n        a -= t * b, std::swap(a, b);\n        u -= t * v, std::swap(u,\
    \ v);\n    }\n    u %= mod;\n    if (u < 0)\n        u += mod;\n    return u;\n\
    }\n\n// mod_integer<P> a := P\u3092\u6CD5\u3068\u3059\u308B\u3068\u304D\u306E\u6574\
    \u6570\u578B;\ntemplate <int mod> class mod_integer {\n  private:\n    long long\
    \ val; // \u5024\u306F\u5FC5\u305A 0 <= val < mod \u306B\u4FDD\u305F\u308C\u308B\
    \n    friend mod_integer operator+(const mod_integer &a) { return a; }\n    friend\
    \ mod_integer operator-(const mod_integer &a) { return -a.val; }\n    friend mod_integer\
    \ operator+(const mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val\
    \ + b.val);\n    }\n    friend mod_integer operator-(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val - b.val);\n    }\n    friend\
    \ mod_integer operator*(const mod_integer &a, const mod_integer &b) {\n      \
    \  return mod_integer(a.val * b.val);\n    }\n    friend mod_integer operator/(const\
    \ mod_integer &a, const mod_integer &b) {\n        return mod_integer((a.val *\
    \ mod_inverse(b.val, mod)) % mod);\n    }\n\n    friend bool operator==(const\
    \ mod_integer &a, const mod_integer &b) {\n        return a.val == b.val;\n  \
    \  }\n    friend bool operator!=(const mod_integer &a, const mod_integer &b) {\n\
    \        return a.val != b.val;\n    }\n\n    // map \u3068\u304B\u306B\u4E57\u305B\
    \u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\n    friend\
    \ bool operator<(const mod_integer &a, const mod_integer &b) {\n        return\
    \ a.val < b.val;\n    }\n\n  public:\n    mod_integer(long long n) : val(n) {\n\
    \        val %= mod;\n        if (val < 0)\n            val += mod;\n    }\n \
    \   mod_integer() : val(0) {}\n    int value() const { return (int)val; }\n\n\
    \    mod_integer &operator=(const mod_integer &a) = default;\n    mod_integer\
    \ &operator+=(const mod_integer &a) {\n        val += a.val;\n        if (val\
    \ >= mod)\n            val -= mod;\n        return *this;\n    }\n    mod_integer\
    \ &operator-=(const mod_integer &a) {\n        val -= a.val;\n        if (val\
    \ < 0)\n            val += mod;\n        return *this;\n    }\n    mod_integer\
    \ &operator*=(const mod_integer &a) {\n        (val *= a.val) %= mod;\n      \
    \  return *this;\n    }\n    mod_integer &operator/=(const mod_integer &a) {\n\
    \        (val *= mod_inverse(a.val, mod)) %= mod;\n        return *this;\n   \
    \ }\n\n    friend std::istream &operator>>(std::istream &is, mod_integer &a) {\n\
    \        is >> a.val;\n        a.val %= mod;\n        if (a.val < 0)\n       \
    \     a.val += mod;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const mod_integer &a) {\n        os << a.val;\n        return os;\n   \
    \ }\n};\n\n// d_mod_integer<P> a := P\u3092\u6CD5\u3068\u3059\u308B\u3068\u304D\
    \u306E\u6574\u6570\u578B;\ntemplate <int id> class dynamic_mod_integer {\n  private:\n\
    \    using d_mod_integer = dynamic_mod_integer<id>;\n    static inline int mod\
    \ = 998244353;\n    long long val; // \u5024\u306F\u5FC5\u305A 0 <= val < mod\
    \ \u306B\u4FDD\u305F\u308C\u308B\n    friend d_mod_integer operator+(const d_mod_integer\
    \ &a) { return a; }\n    friend d_mod_integer operator-(const d_mod_integer &a)\
    \ { return -a.val; }\n    friend d_mod_integer operator+(const d_mod_integer &a,\n\
    \                                   const d_mod_integer &b) {\n        return\
    \ d_mod_integer(a.val + b.val);\n    }\n    friend d_mod_integer operator-(const\
    \ d_mod_integer &a,\n                                   const d_mod_integer &b)\
    \ {\n        return d_mod_integer(a.val - b.val);\n    }\n    friend d_mod_integer\
    \ operator*(const d_mod_integer &a,\n                                   const\
    \ d_mod_integer &b) {\n        return d_mod_integer(a.val * b.val);\n    }\n \
    \   friend d_mod_integer operator/(const d_mod_integer &a,\n                 \
    \                  const d_mod_integer &b) {\n        return d_mod_integer((a.val\
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
    using _mint = mod_integer<998244353>;\nusing dmint = dynamic_mod_integer<-1>;\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/mod_integer.hpp
  requiredBy:
  - math/enumeration_utility.hpp
  - math/totient.hpp
  - standard/fraction.hpp
  timestamp: '2023-08-15 19:52:01+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/ntl-1-d.test.cpp
  - test/jsc2021-g.test.cpp
documentation_of: standard/mod_integer.hpp
layout: document
redirect_from:
- /library/standard/mod_integer.hpp
- /library/standard/mod_integer.hpp.html
title: standard/mod_integer.hpp
---
