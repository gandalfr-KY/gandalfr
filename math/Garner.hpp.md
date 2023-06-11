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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://kopricky.github.io/code/Computation_Advanced/garner.html
  bundledCode: "#line 1 \"math/Garner.hpp\"\n\n\n#include <vector>\n#line 1 \"math/mod_inverse.hpp\"\
    \n\n\n#include <assert.h>\n#line 1 \"math/Bezout_coefficients.hpp\"\n\n\n#include\
    \ <utility>\n#include <cstdlib>\n\nlong long _extgcd(long long a, long long b,\
    \ long long &s, long long &t){\n    if(b == 0){\n        s = 1;\n        t = 0;\n\
    \        return a;\n    }\n    else{\n        auto d = std::lldiv(a, b);\n   \
    \     long long tmp = _extgcd(b, d.rem, t, s);\n        t -= d.quot * s;\n   \
    \     return tmp;\n    }\n}\n\nstd::pair<long long, long long> Bezout_coefficients(long\
    \ long a, long long b){\n    long long s, t;\n    _extgcd((a >= 0 ? a : -a), (b\
    \ >= 0 ? b : -b), s, t);\n    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};\n\
    }\n\n\n#line 5 \"math/mod_inverse.hpp\"\n\nlong long mod_inverse(long long x,\
    \ int mod){\n    assert(mod > 0);\n    x %= mod;\n    auto [a, b] = Bezout_coefficients(x,\
    \ mod);\n    assert(a * x == -b * mod + 1);\n    return (a >= 0 ? a : a + mod);\n\
    }\n\n\n#line 5 \"math/Garner.hpp\"\n\n/*\n * O(N)\n * from : https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    \ */\nlong long Garner(std::vector<long long> a, std::vector<long long> p, const\
    \ int mod){\n    for(long long &x : a) x %= mod;\n    int sz = a.size();\n   \
    \ std::vector<long long> kp(sz + 1, 0), rmult(sz + 1, 1);\n    p.push_back(mod);\n\
    \    for(int i = 0; i < sz; ++i){\n        long long x = (a[i] - kp[i]) * mod_inverse(rmult[i],\
    \ p[i]) % p[i];\n        x = (x < 0) ? (x + p[i]) : x;\n        for(int j = i\
    \ + 1; j < sz + 1; ++j){\n            kp[j] = (kp[j] + rmult[j] * x) % p[j];\n\
    \            rmult[j] = rmult[j] * p[i] % p[j];\n        }\n    }\n    return\
    \ kp[sz];\n}\n\n\n"
  code: "#ifndef GARNER\n#define GARNER\n#include <vector>\n#include \"mod_inverse.hpp\"\
    \n\n/*\n * O(N)\n * from : https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    \ */\nlong long Garner(std::vector<long long> a, std::vector<long long> p, const\
    \ int mod){\n    for(long long &x : a) x %= mod;\n    int sz = a.size();\n   \
    \ std::vector<long long> kp(sz + 1, 0), rmult(sz + 1, 1);\n    p.push_back(mod);\n\
    \    for(int i = 0; i < sz; ++i){\n        long long x = (a[i] - kp[i]) * mod_inverse(rmult[i],\
    \ p[i]) % p[i];\n        x = (x < 0) ? (x + p[i]) : x;\n        for(int j = i\
    \ + 1; j < sz + 1; ++j){\n            kp[j] = (kp[j] + rmult[j] * x) % p[j];\n\
    \            rmult[j] = rmult[j] * p[i] % p[j];\n        }\n    }\n    return\
    \ kp[sz];\n}\n\n#endif"
  dependsOn:
  - math/mod_inverse.hpp
  - math/Bezout_coefficients.hpp
  isVerificationFile: false
  path: math/Garner.hpp
  requiredBy: []
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/Garner.hpp
layout: document
redirect_from:
- /library/math/Garner.hpp
- /library/math/Garner.hpp.html
title: math/Garner.hpp
---
