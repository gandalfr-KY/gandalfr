---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/integer/Bezout_coefficients.hpp
    title: math/integer/Bezout_coefficients.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/integer/Garner.hpp
    title: math/integer/Garner.hpp
  - icon: ':warning:'
    path: standard/fraction.hpp
    title: standard/fraction.hpp
  - icon: ':warning:'
    path: standard/mod_integer.hpp
    title: standard/mod_integer.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/integer/mod_inverse.hpp\"\n\n\n#include <assert.h>\n\
    #line 1 \"math/integer/Bezout_coefficients.hpp\"\n\n\n#include <utility>\n\nlong\
    \ long _extgcd(long long a, long long b, long long &s, long long &t){\n    if(b\
    \ == 0){\n        s = 1;\n        t = 0;\n        return a;\n    }\n    else{\n\
    \        auto d = std::lldiv(a, b);\n        long long tmp = _extgcd(b, d.rem,\
    \ t, s);\n        t -= d.quot * s;\n        return tmp;\n    }\n}\n\nstd::pair<long\
    \ long, long long> Bezout_coefficients(long long a, long long b){\n    long long\
    \ s, t;\n    _extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n    return\
    \ {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n\n#line 5 \"math/integer/mod_inverse.hpp\"\
    \n\nlong long mod_inverse(long long x, int mod){\n    assert(mod > 0);\n    x\
    \ %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n    assert(a * x ==\
    \ -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n\n\n"
  code: "#ifndef MOD_INVERSE\n#define MOD_INVERSE\n#include <assert.h>\n#include \"\
    Bezout_coefficients.hpp\"\n\nlong long mod_inverse(long long x, int mod){\n  \
    \  assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x, mod);\n\
    \    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n}\n\n\
    #endif"
  dependsOn:
  - math/integer/Bezout_coefficients.hpp
  isVerificationFile: false
  path: math/integer/mod_inverse.hpp
  requiredBy:
  - math/integer/Garner.hpp
  - standard/mod_integer.hpp
  - standard/fraction.hpp
  timestamp: '2023-06-07 15:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/integer/mod_inverse.hpp
layout: document
redirect_from:
- /library/math/integer/mod_inverse.hpp
- /library/math/integer/mod_inverse.hpp.html
title: math/integer/mod_inverse.hpp
---
