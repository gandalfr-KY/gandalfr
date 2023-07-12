---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 2 \"math/mod_inverse.hpp\"\n#include <assert.h>\n#include <algorithm>\n\
    \ninline long long mod_inverse(long long a, int mod) {\n    assert(mod > 0);\n\
    \    long long b = mod, u = 1, v = 0;\n    while (b) {\n        long long t =\
    \ a / b;\n        a -= t * b, std::swap(a, b);\n        u -= t * v, std::swap(u,\
    \ v);\n    }\n    u %= mod; \n    if (u < 0) u += mod;\n    return u;\n}\n"
  code: "#pragma once\n#include <assert.h>\n#include <algorithm>\n\ninline long long\
    \ mod_inverse(long long a, int mod) {\n    assert(mod > 0);\n    long long b =\
    \ mod, u = 1, v = 0;\n    while (b) {\n        long long t = a / b;\n        a\
    \ -= t * b, std::swap(a, b);\n        u -= t * v, std::swap(u, v);\n    }\n  \
    \  u %= mod; \n    if (u < 0) u += mod;\n    return u;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/mod_inverse.hpp
  requiredBy:
  - math/binomial_coefficients.hpp
  - math/Garner.hpp
  - standard/mod_integer.hpp
  - standard/fraction.hpp
  timestamp: '2023-07-12 15:11:45+09:00'
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
