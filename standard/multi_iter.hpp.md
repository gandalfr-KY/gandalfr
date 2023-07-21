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
  bundledCode: "#line 2 \"standard/multi_iter.hpp\"\n#define ENABLE_MULTI_FOR\n\n\
    #include <algorithm>\n#include <utility>\n#include <vector>\n\nusing multirange\
    \ = std::vector<std::pair<int, int>>;\n\nclass multi_iter {\n  private:\n    int\
    \ *lim;\n    int *bs;\n    int *it;\n    int depth, d;\n\n  public:\n    multi_iter(const\
    \ std::vector<int> &limits) : depth(limits.size()), d(0) {\n        lim = new\
    \ int[depth];\n        bs = new int[depth];\n        it = new int[depth];\n  \
    \      for (int i = 0; i < depth; ++i) {\n            lim[i] = limits[i];\n  \
    \          bs[i] = it[i] = 0;\n        }\n    }\n    multi_iter(const multirange\
    \ &rngs) : depth(rngs.size()), d(0) {\n        lim = new int[depth];\n       \
    \ bs = new int[depth];\n        it = new int[depth];\n        for (int i = 0;\
    \ i < depth; ++i) {\n            lim[i] = rngs[i].second;\n            bs[i] =\
    \ it[i] = rngs[i].first;\n        }\n    }\n\n    ~multi_iter() {\n        delete[]\
    \ lim;\n        delete[] bs;\n        delete[] it;\n    }\n\n    multi_iter &operator++()\
    \ {\n        for (d = 0; d < depth && ++it[d] == lim[d]; ++d)\n            it[d]\
    \ = bs[d];\n        return *this;\n    }\n\n    multi_iter operator++(int) {\n\
    \        multi_iter tmp(*this);\n        operator++();\n        return tmp;\n\
    \    }\n\n    void init() { std::copy(bs, bs + depth, it); }\n\n    bool fin()\
    \ const { return d == depth; }\n\n    int operator[](int idx) const { return it[idx];\
    \ }\n};\n"
  code: "#pragma once\n#define ENABLE_MULTI_FOR\n\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\nusing multirange = std::vector<std::pair<int,\
    \ int>>;\n\nclass multi_iter {\n  private:\n    int *lim;\n    int *bs;\n    int\
    \ *it;\n    int depth, d;\n\n  public:\n    multi_iter(const std::vector<int>\
    \ &limits) : depth(limits.size()), d(0) {\n        lim = new int[depth];\n   \
    \     bs = new int[depth];\n        it = new int[depth];\n        for (int i =\
    \ 0; i < depth; ++i) {\n            lim[i] = limits[i];\n            bs[i] = it[i]\
    \ = 0;\n        }\n    }\n    multi_iter(const multirange &rngs) : depth(rngs.size()),\
    \ d(0) {\n        lim = new int[depth];\n        bs = new int[depth];\n      \
    \  it = new int[depth];\n        for (int i = 0; i < depth; ++i) {\n         \
    \   lim[i] = rngs[i].second;\n            bs[i] = it[i] = rngs[i].first;\n   \
    \     }\n    }\n\n    ~multi_iter() {\n        delete[] lim;\n        delete[]\
    \ bs;\n        delete[] it;\n    }\n\n    multi_iter &operator++() {\n       \
    \ for (d = 0; d < depth && ++it[d] == lim[d]; ++d)\n            it[d] = bs[d];\n\
    \        return *this;\n    }\n\n    multi_iter operator++(int) {\n        multi_iter\
    \ tmp(*this);\n        operator++();\n        return tmp;\n    }\n\n    void init()\
    \ { std::copy(bs, bs + depth, it); }\n\n    bool fin() const { return d == depth;\
    \ }\n\n    int operator[](int idx) const { return it[idx]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/multi_iter.hpp
  requiredBy: []
  timestamp: '2023-07-21 12:50:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/multi_iter.hpp
layout: document
redirect_from:
- /library/standard/multi_iter.hpp
- /library/standard/multi_iter.hpp.html
title: standard/multi_iter.hpp
---
