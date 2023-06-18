---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/Garner.hpp
    title: math/Garner.hpp
  - icon: ':x:'
    path: math/mod_inverse.hpp
    title: math/mod_inverse.hpp
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
  bundledCode: "#line 1 \"math/Bezout_coefficients.hpp\"\n\n\n#include <cstdlib>\n\
    #include <utility>\n\nnamespace internal {\nlong long extgcd(long long a, long\
    \ long b, long long &s, long long &t) {\n    if (b == 0) {\n        s = 1;\n \
    \       t = 0;\n        return a;\n    } else {\n        auto d = std::lldiv(a,\
    \ b);\n        long long tmp = extgcd(b, d.rem, t, s);\n        t -= d.quot *\
    \ s;\n        return tmp;\n    }\n}\n} // namespace internal\n\nstd::pair<long\
    \ long, long long> Bezout_coefficients(long long a, long long b) {\n    long long\
    \ s, t;\n    internal::extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n \
    \   return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n\n"
  code: "#ifndef BEZOUT_COEFFICIENTS\n#define BEZOUT_COEFFICIENTS\n#include <cstdlib>\n\
    #include <utility>\n\nnamespace internal {\nlong long extgcd(long long a, long\
    \ long b, long long &s, long long &t) {\n    if (b == 0) {\n        s = 1;\n \
    \       t = 0;\n        return a;\n    } else {\n        auto d = std::lldiv(a,\
    \ b);\n        long long tmp = extgcd(b, d.rem, t, s);\n        t -= d.quot *\
    \ s;\n        return tmp;\n    }\n}\n} // namespace internal\n\nstd::pair<long\
    \ long, long long> Bezout_coefficients(long long a, long long b) {\n    long long\
    \ s, t;\n    internal::extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n \
    \   return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n}\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/Bezout_coefficients.hpp
  requiredBy:
  - math/mod_inverse.hpp
  - math/Garner.hpp
  - standard/mod_integer.hpp
  - standard/fraction.hpp
  timestamp: '2023-06-19 01:40:27+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/jsc2021-g.test.cpp
documentation_of: math/Bezout_coefficients.hpp
layout: document
redirect_from:
- /library/math/Bezout_coefficients.hpp
- /library/math/Bezout_coefficients.hpp.html
title: math/Bezout_coefficients.hpp
---
