---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/Bezout_coefficients.hpp
    title: math/Bezout_coefficients.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/Garner.hpp
    title: math/Garner.hpp
  - icon: ':warning:'
    path: math/binomial_coefficients.hpp
    title: math/binomial_coefficients.hpp
  - icon: ':warning:'
    path: standard/fraction.hpp
    title: standard/fraction.hpp
  - icon: ':x:'
    path: standard/mod_integer.hpp
    title: standard/mod_integer.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/mod_inverse.hpp\"\n#include <assert.h>\n\n#line 2 \"\
    math/Bezout_coefficients.hpp\"\n#include <cstdlib>\n#include <utility>\n\nnamespace\
    \ internal {\nlong long extgcd(long long a, long long b, long long &s, long long\
    \ &t) {\n    if (b == 0) {\n        s = 1;\n        t = 0;\n        return a;\n\
    \    } else {\n        auto d = std::lldiv(a, b);\n        long long tmp = extgcd(b,\
    \ d.rem, t, s);\n        t -= d.quot * s;\n        return tmp;\n    }\n}\n} //\
    \ namespace internal\n\nstd::pair<long long, long long> Bezout_coefficients(long\
    \ long a, long long b) {\n    long long s, t;\n    internal::extgcd((a >= 0 ?\
    \ a : -a), (b >= 0 ? b : -b), s, t);\n    return {(a >= 0 ? s : -s), (b >= 0 ?\
    \ t : -t)};\n}\n#line 5 \"math/mod_inverse.hpp\"\n\nlong long mod_inverse(long\
    \ long x, int mod) {\n    assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x,\
    \ mod);\n    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n\
    }\n"
  code: "#pragma once\n#include <assert.h>\n\n#include \"Bezout_coefficients.hpp\"\
    \n\nlong long mod_inverse(long long x, int mod) {\n    assert(mod > 0);\n    x\
    \ %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n    assert(a * x ==\
    \ -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n"
  dependsOn:
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: math/mod_inverse.hpp
  requiredBy:
  - math/binomial_coefficients.hpp
  - math/Garner.hpp
  - standard/mod_integer.hpp
  - standard/fraction.hpp
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/jsc2021-g.test.cpp
documentation_of: math/mod_inverse.hpp
layout: document
redirect_from:
- /library/math/mod_inverse.hpp
- /library/math/mod_inverse.hpp.html
title: math/mod_inverse.hpp
---
