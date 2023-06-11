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
  bundledCode: "#line 1 \"math/mod_inverse.hpp\"\n\n\n#include <assert.h>\n#line 1\
    \ \"math/Bezout_coefficients.hpp\"\n\n\n#include <utility>\n#include <cstdlib>\n\
    \nlong long _extgcd(long long a, long long b, long long &s, long long &t){\n \
    \   if(b == 0){\n        s = 1;\n        t = 0;\n        return a;\n    }\n  \
    \  else{\n        auto d = std::lldiv(a, b);\n        long long tmp = _extgcd(b,\
    \ d.rem, t, s);\n        t -= d.quot * s;\n        return tmp;\n    }\n}\n\nstd::pair<long\
    \ long, long long> Bezout_coefficients(long long a, long long b){\n    long long\
    \ s, t;\n    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n    return\
    \ {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n\n#line 5 \"math/mod_inverse.hpp\"\
    \n\nlong long mod_inverse(long long x, int mod){\n    assert(mod > 0);\n    x\
    \ %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n    assert(a * x ==\
    \ -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n\n\n"
  code: "#ifndef MOD_INVERSE\n#define MOD_INVERSE\n#include <assert.h>\n#include \"\
    Bezout_coefficients.hpp\"\n\nlong long mod_inverse(long long x, int mod){\n  \
    \  assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n\
    \    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n\n\
    #endif"
  dependsOn:
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: math/mod_inverse.hpp
  requiredBy:
  - math/Garner.hpp
  - standard/mod_integer.hpp
  - standard/fraction.hpp
  timestamp: '2023-06-12 02:08:44+09:00'
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
