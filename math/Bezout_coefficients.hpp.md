---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/Bezout_coefficients.hpp\"\n#include <tuple>\n#include\
    \ <utility>\n\nnamespace internal {\n    \nlong long extgcd(long long a, long\
    \ long b, long long &x, long long &y) {\n    x = 1, y = 0;\n    long long nx =\
    \ 0, ny = 1;\n    while(b) {\n        long long q = a / b;\n        std::tie(a,\
    \ b) = std::make_pair(b, a % b);\n        std::tie(x, nx) = std::make_pair(nx,\
    \ x - nx*q);\n        std::tie(y, ny) = std::make_pair(ny, y - ny*q);\n    }\n\
    \    return a;\n}\n} // namespace internal\n\nstd::pair<long long, long long>\
    \ Bezout_coefficients(long long a, long long b) {\n    long long s, t;\n    internal::extgcd((a\
    \ >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);\n    return {(a >= 0 ? s : -s), (b\
    \ >= 0 ? t : -t)};\n}\n"
  code: "#pragma once\n#include <tuple>\n#include <utility>\n\nnamespace internal\
    \ {\n    \nlong long extgcd(long long a, long long b, long long &x, long long\
    \ &y) {\n    x = 1, y = 0;\n    long long nx = 0, ny = 1;\n    while(b) {\n  \
    \      long long q = a / b;\n        std::tie(a, b) = std::make_pair(b, a % b);\n\
    \        std::tie(x, nx) = std::make_pair(nx, x - nx*q);\n        std::tie(y,\
    \ ny) = std::make_pair(ny, y - ny*q);\n    }\n    return a;\n}\n} // namespace\
    \ internal\n\nstd::pair<long long, long long> Bezout_coefficients(long long a,\
    \ long long b) {\n    long long s, t;\n    internal::extgcd((a >= 0 ? a : -a),\
    \ (b >= 0 ? b : -b), s, t);\n    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: math/Bezout_coefficients.hpp
  requiredBy: []
  timestamp: '2023-07-12 15:11:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/Bezout_coefficients.hpp
layout: document
redirect_from:
- /library/math/Bezout_coefficients.hpp
- /library/math/Bezout_coefficients.hpp.html
title: math/Bezout_coefficients.hpp
---
