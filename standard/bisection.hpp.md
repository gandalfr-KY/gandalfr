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
    \ <class T, class Func> void bisection(T &t, T &f, const Func &F) {\n    static_assert(std::is_invocable_r_v<bool,\
    \ Func, T>);\n    assert(F(t) && !F(f));\n    while (std::abs(t - f) > 1) {\n\
    \        T mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n\ntemplate\
    \ <class Func>\nvoid bisection(double &t, double &f, const Func &F, double eps\
    \ = 1e-10) {\n    static_assert(std::is_invocable_r_v<bool, Func, double>);\n\
    \    assert(F(t) && !F(f));\n    while (std::abs(t - f) > eps) {\n        double\
    \ mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n"
  code: "#include <type_traits>\n\ntemplate <class T, class Func> void bisection(T\
    \ &t, T &f, const Func &F) {\n    static_assert(std::is_invocable_r_v<bool, Func,\
    \ T>);\n    assert(F(t) && !F(f));\n    while (std::abs(t - f) > 1) {\n      \
    \  T mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n\ntemplate\
    \ <class Func>\nvoid bisection(double &t, double &f, const Func &F, double eps\
    \ = 1e-10) {\n    static_assert(std::is_invocable_r_v<bool, Func, double>);\n\
    \    assert(F(t) && !F(f));\n    while (std::abs(t - f) > eps) {\n        double\
    \ mid = (t + f) / 2;\n        (F(mid) ? t : f) = mid;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/bisection.hpp
  requiredBy: []
  timestamp: '2023-09-02 19:34:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/bisection.hpp
layout: document
redirect_from:
- /library/standard/bisection.hpp
- /library/standard/bisection.hpp.html
title: standard/bisection.hpp
---
