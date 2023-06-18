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
  bundledCode: "#line 1 \"data_structure/prefix_sums.hpp\"\n\n\n#include <functional>\n\
    #include <vector>\n\n// [l, r) \u3067\u533A\u9593\u548C\u3092\u5F97\u308B\ntemplate\
    \ <class T> class prefix_sums {\n  private:\n    int n;\n    std::vector<T> acm;\n\
    \    const std::function<T(T, T)> f;\n    const std::function<T(T, T)> f_inv;\n\
    \    T e;\n\n  public:\n    prefix_sums(\n        const std::vector<T> &v,\n \
    \       const std::function<T(T, T)> &_f = [](T a, T b) { return a + b; },\n \
    \       const std::function<T(T, T)> &_f_inv = [](T a, T b) { return a - b; },\n\
    \        const T &_e = 0)\n        : n(v.size()), f(_f), f_inv(_f_inv), e(_e)\
    \ {\n        acm.reserve(n + 1);\n        acm.push_back(e);\n        for (const\
    \ T &x : v) {\n            acm.push_back(f(acm.back(), x));\n        }\n    }\n\
    \n    T get(int l, int r) {\n        assert(0 <= l && l <= r && r <= n);\n   \
    \     if (l == r)\n            return e;\n        return f_inv(acm[r], acm[l]);\n\
    \    }\n\n    const std::vector<T> &result() { return acm; }\n};\n\ntemplate <class\
    \ T> class prefix_sums_2d {\n  public:\n    int h, w;\n    std::vector<std::vector<T>>\
    \ acm;\n    const std::function<T(T, T)> f;\n    const std::function<T(T, T)>\
    \ f_inv;\n    T e;\n\n  public:\n    prefix_sums_2d(\n        const std::vector<std::vector<T>>\
    \ &v,\n        const std::function<T(T, T)> &_f = [](T a, T b) { return a + b;\
    \ },\n        const std::function<T(T, T)> &_f_inv = [](T a, T b) { return a -\
    \ b; },\n        const T &_e = 0)\n        : h(v.size()), w(v[0].size()), f(_f),\
    \ f_inv(_f_inv), e(_e),\n          acm(h + 1, std::vector<T>(w + 1, _e)) {\n \
    \       for (int i = 1; i <= h; i++) {\n            for (int j = 1; j <= w; j++)\
    \ {\n                acm[i][j] = f(acm[i][j - 1], v[i - 1][j - 1]);\n        \
    \    }\n            for (int j = 1; j <= w; j++) {\n                acm[i][j]\
    \ = f(acm[i][j], acm[i - 1][j]);\n            }\n        }\n    }\n\n    T get(int\
    \ h_begin, int h_end, int w_begin, int w_end) {\n        assert(0 <= h_begin &&\
    \ h_begin <= h_end && h_end <= h);\n        assert(0 <= w_begin && w_begin <=\
    \ w_end && w_end <= w);\n        if (h_begin == h_end || w_begin == w_end)\n \
    \           return e;\n        // acm[h_end][w_end] - acm[h_end][w_begin] - acm[h_begin][w_end]\
    \ +\n        // acm[h_begin][w_begin] \u307F\u305F\u3044\u306A\u611F\u3058\n \
    \       return f(f_inv(f_inv(acm[h_end][w_end], acm[h_end][w_begin]),\n      \
    \                 acm[h_begin][w_end]),\n                 acm[h_begin][w_begin]);\n\
    \    }\n\n    const std::vector<std::vector<T>> &result() { return acm; }\n};\n\
    \n\n"
  code: "#ifndef PREFIX_SUMS\n#define PREFIX_SUMS\n#include <functional>\n#include\
    \ <vector>\n\n// [l, r) \u3067\u533A\u9593\u548C\u3092\u5F97\u308B\ntemplate <class\
    \ T> class prefix_sums {\n  private:\n    int n;\n    std::vector<T> acm;\n  \
    \  const std::function<T(T, T)> f;\n    const std::function<T(T, T)> f_inv;\n\
    \    T e;\n\n  public:\n    prefix_sums(\n        const std::vector<T> &v,\n \
    \       const std::function<T(T, T)> &_f = [](T a, T b) { return a + b; },\n \
    \       const std::function<T(T, T)> &_f_inv = [](T a, T b) { return a - b; },\n\
    \        const T &_e = 0)\n        : n(v.size()), f(_f), f_inv(_f_inv), e(_e)\
    \ {\n        acm.reserve(n + 1);\n        acm.push_back(e);\n        for (const\
    \ T &x : v) {\n            acm.push_back(f(acm.back(), x));\n        }\n    }\n\
    \n    T get(int l, int r) {\n        assert(0 <= l && l <= r && r <= n);\n   \
    \     if (l == r)\n            return e;\n        return f_inv(acm[r], acm[l]);\n\
    \    }\n\n    const std::vector<T> &result() { return acm; }\n};\n\ntemplate <class\
    \ T> class prefix_sums_2d {\n  public:\n    int h, w;\n    std::vector<std::vector<T>>\
    \ acm;\n    const std::function<T(T, T)> f;\n    const std::function<T(T, T)>\
    \ f_inv;\n    T e;\n\n  public:\n    prefix_sums_2d(\n        const std::vector<std::vector<T>>\
    \ &v,\n        const std::function<T(T, T)> &_f = [](T a, T b) { return a + b;\
    \ },\n        const std::function<T(T, T)> &_f_inv = [](T a, T b) { return a -\
    \ b; },\n        const T &_e = 0)\n        : h(v.size()), w(v[0].size()), f(_f),\
    \ f_inv(_f_inv), e(_e),\n          acm(h + 1, std::vector<T>(w + 1, _e)) {\n \
    \       for (int i = 1; i <= h; i++) {\n            for (int j = 1; j <= w; j++)\
    \ {\n                acm[i][j] = f(acm[i][j - 1], v[i - 1][j - 1]);\n        \
    \    }\n            for (int j = 1; j <= w; j++) {\n                acm[i][j]\
    \ = f(acm[i][j], acm[i - 1][j]);\n            }\n        }\n    }\n\n    T get(int\
    \ h_begin, int h_end, int w_begin, int w_end) {\n        assert(0 <= h_begin &&\
    \ h_begin <= h_end && h_end <= h);\n        assert(0 <= w_begin && w_begin <=\
    \ w_end && w_end <= w);\n        if (h_begin == h_end || w_begin == w_end)\n \
    \           return e;\n        // acm[h_end][w_end] - acm[h_end][w_begin] - acm[h_begin][w_end]\
    \ +\n        // acm[h_begin][w_begin] \u307F\u305F\u3044\u306A\u611F\u3058\n \
    \       return f(f_inv(f_inv(acm[h_end][w_end], acm[h_end][w_begin]),\n      \
    \                 acm[h_begin][w_end]),\n                 acm[h_begin][w_begin]);\n\
    \    }\n\n    const std::vector<std::vector<T>> &result() { return acm; }\n};\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/prefix_sums.hpp
  requiredBy: []
  timestamp: '2023-06-19 01:40:27+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/prefix_sums.hpp
layout: document
redirect_from:
- /library/data_structure/prefix_sums.hpp
- /library/data_structure/prefix_sums.hpp.html
title: data_structure/prefix_sums.hpp
---
