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
  bundledCode: "#line 1 \"standard/bisection.hpp\"\n#include <type_traits>\n\ntemplate\
    \ <class T, class Func>\nvoid bisection(T &t, T &f, const Func &F) {\n    static_assert(std::is_invocable_r_v<bool,\
    \ Func, T>);\n    assert(F(t) && !F(f));\n    while (std::abs(t - f) > 1) {\n\
    \        T mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n"
  code: "#include <type_traits>\n\ntemplate <class T, class Func>\nvoid bisection(T\
    \ &t, T &f, const Func &F) {\n    static_assert(std::is_invocable_r_v<bool, Func,\
    \ T>);\n    assert(F(t) && !F(f));\n    while (std::abs(t - f) > 1) {\n      \
    \  T mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/bisection.hpp
  requiredBy: []
  timestamp: '2023-08-22 00:48:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/bisection.hpp
layout: document
redirect_from:
- /library/standard/bisection.hpp
- /library/standard/bisection.hpp.html
title: standard/bisection.hpp
---
