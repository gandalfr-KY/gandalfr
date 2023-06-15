---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/totient.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\
      \u6570"
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"standard/power.hpp\"\n\n\n#include <assert.h>\n\ntemplate<class\
    \ T>\nT power(T x, long long n) {\n    T ret = T(1);\n    while (n > 0) {\n  \
    \      if (n & 1) ret = ret * x;\n        x = x * x;\n        n >>= 1;\n    }\n\
    \    return ret;\n}\n\nlong long power(long long x, long long n) {\n    long long\
    \ ret = 1;\n    while (n > 0) {\n        if (n & 1) ret = ret * x;\n        x\
    \ = x * x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong long power(long\
    \ long x, long long n, int MOD) {\n    long long ret = 1;\n    x %= MOD;\n   \
    \ while (n > 0) {\n        if (n & 1) ret = ret * x % MOD;\n        x = x * x\
    \ % MOD;\n        n >>= 1;\n    }\n    return ret;\n}\n\n\n"
  code: "#ifndef POWER\n#define POWER\n#include <assert.h>\n\ntemplate<class T>\n\
    T power(T x, long long n) {\n    T ret = T(1);\n    while (n > 0) {\n        if\
    \ (n & 1) ret = ret * x;\n        x = x * x;\n        n >>= 1;\n    }\n    return\
    \ ret;\n}\n\nlong long power(long long x, long long n) {\n    long long ret =\
    \ 1;\n    while (n > 0) {\n        if (n & 1) ret = ret * x;\n        x = x *\
    \ x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong long power(long long\
    \ x, long long n, int MOD) {\n    long long ret = 1;\n    x %= MOD;\n    while\
    \ (n > 0) {\n        if (n & 1) ret = ret * x % MOD;\n        x = x * x % MOD;\n\
    \        n >>= 1;\n    }\n    return ret;\n}\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: standard/power.hpp
  requiredBy:
  - math/totient.hpp
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/power.hpp
layout: document
redirect_from:
- /library/standard/power.hpp
- /library/standard/power.hpp.html
title: standard/power.hpp
---
