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
  bundledCode: "#line 1 \"math/integer/binomial_coefficients.hpp\"\n\n\n#include <vector>\n\
    \ntemplate<class T>\nclass binomial_coefficients{\n  private:\n    static std::vector<T>\
    \ fact;\n\n    static void expand(int n){\n\t\twhile(n >= fact.size()) {\n   \
    \         fact.push_back(fact.back() * fact.size());\n        }\n    }\n\n  public:\n\
    \    binomial_coefficients() = delete;\n    ~binomial_coefficients() = delete;\n\
    \n    static T get(int n, int k){\n\t\t    assert(0 <= k && k <= n);\n       \
    \ if(n >= fact.size()) expand(n);\n        return fact[n] / fact[k] / fact[n -\
    \ k];\n    }\n\n};\ntemplate<class T>\nstd::vector<T> binomial_coefficients<T>::fact\
    \ = {1};\n\n\n"
  code: "#ifndef BINOMIAL_COEFFICIENTS\n#define BINOMIAL_COEFFICIENTS\n#include <vector>\n\
    \ntemplate<class T>\nclass binomial_coefficients{\n  private:\n    static std::vector<T>\
    \ fact;\n\n    static void expand(int n){\n\t\twhile(n >= fact.size()) {\n   \
    \         fact.push_back(fact.back() * fact.size());\n        }\n    }\n\n  public:\n\
    \    binomial_coefficients() = delete;\n    ~binomial_coefficients() = delete;\n\
    \n    static T get(int n, int k){\n\t\t    assert(0 <= k && k <= n);\n       \
    \ if(n >= fact.size()) expand(n);\n        return fact[n] / fact[k] / fact[n -\
    \ k];\n    }\n\n};\ntemplate<class T>\nstd::vector<T> binomial_coefficients<T>::fact\
    \ = {1};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/integer/binomial_coefficients.hpp
  requiredBy: []
  timestamp: '2023-06-02 11:10:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/integer/binomial_coefficients.hpp
layout: document
redirect_from:
- /library/math/integer/binomial_coefficients.hpp
- /library/math/integer/binomial_coefficients.hpp.html
title: math/integer/binomial_coefficients.hpp
---
