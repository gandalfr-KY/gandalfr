---
data:
  _extendedDependsOn:
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
  bundledCode: "#line 2 \"math/Garner.hpp\"\n#include <vector>\n\n#line 2 \"math/mod_inverse.hpp\"\
    \n#include <algorithm>\n#include <assert.h>\n\ninline long long mod_inverse(long\
    \ long a, int mod) {\n    assert(mod > 0);\n    long long b = mod, u = 1, v =\
    \ 0;\n    while (b) {\n        long long t = a / b;\n        a -= t * b, std::swap(a,\
    \ b);\n        u -= t * v, std::swap(u, v);\n    }\n    u %= mod;\n    if (u <\
    \ 0)\n        u += mod;\n    return u;\n}\n#line 5 \"math/Garner.hpp\"\n\n/*\n\
    \ * O(N)\n * from : https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    \ */\nlong long Garner(std::vector<long long> a, std::vector<long long> p,\n \
    \                const int mod) {\n    for (long long &x : a)\n        x %= mod;\n\
    \    int sz = a.size();\n    std::vector<long long> kp(sz + 1, 0), rmult(sz +\
    \ 1, 1);\n    p.push_back(mod);\n    for (int i = 0; i < sz; ++i) {\n        long\
    \ long x = (a[i] - kp[i]) * mod_inverse(rmult[i], p[i]) % p[i];\n        x = (x\
    \ < 0) ? (x + p[i]) : x;\n        for (int j = i + 1; j < sz + 1; ++j) {\n   \
    \         kp[j] = (kp[j] + rmult[j] * x) % p[j];\n            rmult[j] = rmult[j]\
    \ * p[i] % p[j];\n        }\n    }\n    return kp[sz];\n}\n"
  code: "#pragma once\n#include <vector>\n\n#include \"mod_inverse.hpp\"\n\n/*\n *\
    \ O(N)\n * from : https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    \ */\nlong long Garner(std::vector<long long> a, std::vector<long long> p,\n \
    \                const int mod) {\n    for (long long &x : a)\n        x %= mod;\n\
    \    int sz = a.size();\n    std::vector<long long> kp(sz + 1, 0), rmult(sz +\
    \ 1, 1);\n    p.push_back(mod);\n    for (int i = 0; i < sz; ++i) {\n        long\
    \ long x = (a[i] - kp[i]) * mod_inverse(rmult[i], p[i]) % p[i];\n        x = (x\
    \ < 0) ? (x + p[i]) : x;\n        for (int j = i + 1; j < sz + 1; ++j) {\n   \
    \         kp[j] = (kp[j] + rmult[j] * x) % p[j];\n            rmult[j] = rmult[j]\
    \ * p[i] % p[j];\n        }\n    }\n    return kp[sz];\n}\n"
  dependsOn:
  - math/mod_inverse.hpp
  isVerificationFile: false
  path: math/Garner.hpp
  requiredBy: []
  timestamp: '2023-07-19 02:36:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/Garner.hpp
layout: document
redirect_from:
- /library/math/Garner.hpp
- /library/math/Garner.hpp.html
title: math/Garner.hpp
---
