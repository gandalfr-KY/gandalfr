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
  bundledCode: "#line 1 \"math/divisors.hpp\"\n\n\n#include <vector>\n#include <algorithm>\n\
    \n/* \u7D04\u6570\u6607\u9806\u5217\u6319 \n * O(\u221AN) \n */\nstd::vector<long\
    \ long> divisors(long long N){\n    std::vector<long long> ret;\n    for(long\
    \ long i=1; i*i<=N; i++){\n        if(N % i == 0){\n            ret.push_back(i);\n\
    \            if(N / i != i) ret.push_back(N / i);\n        }\n    }\n    std::sort(ret.begin(),\
    \ ret.end());\n    return ret;\n}\n\n\n"
  code: "#ifndef DIVISORS\n#define DIVISORS\n#include <vector>\n#include <algorithm>\n\
    \n/* \u7D04\u6570\u6607\u9806\u5217\u6319 \n * O(\u221AN) \n */\nstd::vector<long\
    \ long> divisors(long long N){\n    std::vector<long long> ret;\n    for(long\
    \ long i=1; i*i<=N; i++){\n        if(N % i == 0){\n            ret.push_back(i);\n\
    \            if(N / i != i) ret.push_back(N / i);\n        }\n    }\n    std::sort(ret.begin(),\
    \ ret.end());\n    return ret;\n}\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/divisors.hpp
  requiredBy: []
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/divisors.hpp
layout: document
redirect_from:
- /library/math/divisors.hpp
- /library/math/divisors.hpp.html
title: math/divisors.hpp
---
