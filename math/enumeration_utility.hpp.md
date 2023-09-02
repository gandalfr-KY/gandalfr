---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: standard/mod_integer.hpp
    title: standard/mod_integer.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/Eratosthenes.hpp
    title: "\u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\u30FC\u30C8\
      \u3059\u308B\u30AF\u30E9\u30B9"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/ntl-1-a.test.cpp
    title: test/ntl-1-a.test.cpp
  - icon: ':x:'
    path: test/ntl-1-d.test.cpp
    title: test/ntl-1-d.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/enumeration_utility.hpp\"\n#include <algorithm>\n#include\
    \ <map>\n#include <utility>\n#include <vector>\n\n#line 2 \"standard/mod_integer.hpp\"\
    \n#include <iostream>\n#include <queue>\n#line 5 \"standard/mod_integer.hpp\"\n\
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
    using _mint = mod_integer<998244353>;\nusing dmint = dynamic_mod_integer<-1>;\n\
    #line 8 \"math/enumeration_utility.hpp\"\n\ntemplate <class T> T power(T x, long\
    \ long n) {\n    T ret = static_cast<T>(1);\n    while (n > 0) {\n        if (n\
    \ & 1)\n            ret = ret * x;\n        x = x * x;\n        n >>= 1;\n   \
    \ }\n    return ret;\n}\n\nlong long power(long long x, long long n) {\n    long\
    \ long ret = 1;\n    while (n > 0) {\n        if (n & 1)\n            ret = ret\
    \ * x;\n        x = x * x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong\
    \ long power(long long x, long long n, int MOD) {\n    long long ret = 1;\n  \
    \  x %= MOD;\n    while (n > 0) {\n        if (n & 1)\n            ret = ret *\
    \ x % MOD;\n        x = x * x % MOD;\n        n >>= 1;\n    }\n    return ret;\n\
    }\n\nlong long power(long long x, long long n, long long MOD) {\n    long long\
    \ ret = 1;\n    x %= MOD;\n    while (n > 0) {\n        if (n & 1)\n         \
    \   ret = (__int128_t)ret * x % MOD;\n        x = (__int128_t)x * x % MOD;\n \
    \       n >>= 1;\n    }\n    return ret;\n}\n\ntemplate <class T> class factorial\
    \ {\n  private:\n    static inline std::vector<T> fact{T(1)};\n\n  public:\n \
    \   factorial() = delete;\n    ~factorial() = delete;\n    static T get(int n)\
    \ {\n        while (n >= (int)fact.size())\n            fact.push_back(fact.back()\
    \ * fact.size());\n        return fact[n];\n    }\n};\nmint (*fact)(int) = factorial<mint>::get;\n\
    _mint (*_fact)(int) = factorial<_mint>::get;\n\ntemplate <class T> T permutation(int\
    \ n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ / factorial<T>::get(n - k);\n}\nmint (*perm)(int, int) = permutation<mint>;\n\
    _mint (*_perm)(int, int) = permutation<_mint>;\n\ntemplate <class T> static T\
    \ combnation(int n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ /\n           (factorial<T>::get(k) * factorial<T>::get(n - k));\n}\nmint (*comb)(int,\
    \ int) = combnation<mint>;\n_mint (*_comb)(int, int) = combnation<_mint>;\n"
  code: "#pragma once\n#include <algorithm>\n#include <map>\n#include <utility>\n\
    #include <vector>\n\n#include \"../standard/mod_integer.hpp\"\n\ntemplate <class\
    \ T> T power(T x, long long n) {\n    T ret = static_cast<T>(1);\n    while (n\
    \ > 0) {\n        if (n & 1)\n            ret = ret * x;\n        x = x * x;\n\
    \        n >>= 1;\n    }\n    return ret;\n}\n\nlong long power(long long x, long\
    \ long n) {\n    long long ret = 1;\n    while (n > 0) {\n        if (n & 1)\n\
    \            ret = ret * x;\n        x = x * x;\n        n >>= 1;\n    }\n   \
    \ return ret;\n}\n\nlong long power(long long x, long long n, int MOD) {\n   \
    \ long long ret = 1;\n    x %= MOD;\n    while (n > 0) {\n        if (n & 1)\n\
    \            ret = ret * x % MOD;\n        x = x * x % MOD;\n        n >>= 1;\n\
    \    }\n    return ret;\n}\n\nlong long power(long long x, long long n, long long\
    \ MOD) {\n    long long ret = 1;\n    x %= MOD;\n    while (n > 0) {\n       \
    \ if (n & 1)\n            ret = (__int128_t)ret * x % MOD;\n        x = (__int128_t)x\
    \ * x % MOD;\n        n >>= 1;\n    }\n    return ret;\n}\n\ntemplate <class T>\
    \ class factorial {\n  private:\n    static inline std::vector<T> fact{T(1)};\n\
    \n  public:\n    factorial() = delete;\n    ~factorial() = delete;\n    static\
    \ T get(int n) {\n        while (n >= (int)fact.size())\n            fact.push_back(fact.back()\
    \ * fact.size());\n        return fact[n];\n    }\n};\nmint (*fact)(int) = factorial<mint>::get;\n\
    _mint (*_fact)(int) = factorial<_mint>::get;\n\ntemplate <class T> T permutation(int\
    \ n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ / factorial<T>::get(n - k);\n}\nmint (*perm)(int, int) = permutation<mint>;\n\
    _mint (*_perm)(int, int) = permutation<_mint>;\n\ntemplate <class T> static T\
    \ combnation(int n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ /\n           (factorial<T>::get(k) * factorial<T>::get(n - k));\n}\nmint (*comb)(int,\
    \ int) = combnation<mint>;\n_mint (*_comb)(int, int) = combnation<_mint>;\n"
  dependsOn:
  - standard/mod_integer.hpp
  isVerificationFile: false
  path: math/enumeration_utility.hpp
  requiredBy:
  - math/Eratosthenes.hpp
  timestamp: '2023-08-26 20:18:13+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/ntl-1-d.test.cpp
  - test/ntl-1-a.test.cpp
documentation_of: math/enumeration_utility.hpp
layout: document
redirect_from:
- /library/math/enumeration_utility.hpp
- /library/math/enumeration_utility.hpp.html
title: math/enumeration_utility.hpp
---
