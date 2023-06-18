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
  bundledCode: "#line 2 \"math/binomial_coefficients.hpp\"\n#include <vector>\n\n\
    template <class T> class binomial_coefficients {\n  private:\n    static std::vector<T>\
    \ fact;\n\n    static void expand(int n) {\n        while (n >= fact.size()) {\n\
    \            fact.push_back(fact.back() * fact.size());\n        }\n    }\n\n\
    \  public:\n    binomial_coefficients() = delete;\n    ~binomial_coefficients()\
    \ = delete;\n\n    static T get(int n, int k) {\n        assert(0 <= k && k <=\
    \ n);\n        if (n >= fact.size())\n            expand(n);\n        return fact[n]\
    \ / fact[k] / fact[n - k];\n    }\n};\ntemplate <class T> std::vector<T> binomial_coefficients<T>::fact\
    \ = {1};\n"
  code: "#pragma once\n#include <vector>\n\ntemplate <class T> class binomial_coefficients\
    \ {\n  private:\n    static std::vector<T> fact;\n\n    static void expand(int\
    \ n) {\n        while (n >= fact.size()) {\n            fact.push_back(fact.back()\
    \ * fact.size());\n        }\n    }\n\n  public:\n    binomial_coefficients()\
    \ = delete;\n    ~binomial_coefficients() = delete;\n\n    static T get(int n,\
    \ int k) {\n        assert(0 <= k && k <= n);\n        if (n >= fact.size())\n\
    \            expand(n);\n        return fact[n] / fact[k] / fact[n - k];\n   \
    \ }\n};\ntemplate <class T> std::vector<T> binomial_coefficients<T>::fact = {1};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/binomial_coefficients.hpp
  requiredBy: []
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/binomial_coefficients.hpp
layout: document
redirect_from:
- /library/math/binomial_coefficients.hpp
- /library/math/binomial_coefficients.hpp.html
title: math/binomial_coefficients.hpp
---
