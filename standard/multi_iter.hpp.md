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
  bundledCode: "#line 2 \"standard/multi_iter.hpp\"\n\n#include <vector>\n\nclass\
    \ multi_iter {\nprivate:\n    int* lim;\n    int* it;\n    int depth;\n    int\
    \ d;\n\npublic:\n    multi_iter() : lim(nullptr), it(nullptr), depth(0), d(0)\
    \ {}\n    multi_iter(const std::vector<int>& limits) : depth(limits.size()), d(0)\
    \ {\n        lim = new int[depth];\n        it = new int[depth];\n        for\
    \ (int i = 0; i < depth; ++i) {\n            lim[i] = limits[i];\n           \
    \ it[i] = 0;\n        }\n    }\n\n    ~multi_iter() {\n        delete[] lim;\n\
    \        delete[] it;\n    }\n\n    multi_iter& operator++() {\n        for (d\
    \ = 0; d < depth && ++it[d] == lim[d]; ++d)\n            it[d] = 0;\n        return\
    \ *this;\n    }\n\n    multi_iter operator++(int) {\n        multi_iter tmp(*this);\n\
    \        operator++();\n        return tmp;\n    }\n\n    void init() { std::fill(it,\
    \ it + depth, 0), d = 0; }\n\n    bool fin() const { return d == depth; }\n\n\
    \    int operator[](int idx) const { return it[idx]; }\n};\n"
  code: "#pragma once\n\n#include <vector>\n\nclass multi_iter {\nprivate:\n    int*\
    \ lim;\n    int* it;\n    int depth;\n    int d;\n\npublic:\n    multi_iter()\
    \ : lim(nullptr), it(nullptr), depth(0), d(0) {}\n    multi_iter(const std::vector<int>&\
    \ limits) : depth(limits.size()), d(0) {\n        lim = new int[depth];\n    \
    \    it = new int[depth];\n        for (int i = 0; i < depth; ++i) {\n       \
    \     lim[i] = limits[i];\n            it[i] = 0;\n        }\n    }\n\n    ~multi_iter()\
    \ {\n        delete[] lim;\n        delete[] it;\n    }\n\n    multi_iter& operator++()\
    \ {\n        for (d = 0; d < depth && ++it[d] == lim[d]; ++d)\n            it[d]\
    \ = 0;\n        return *this;\n    }\n\n    multi_iter operator++(int) {\n   \
    \     multi_iter tmp(*this);\n        operator++();\n        return tmp;\n   \
    \ }\n\n    void init() { std::fill(it, it + depth, 0), d = 0; }\n\n    bool fin()\
    \ const { return d == depth; }\n\n    int operator[](int idx) const { return it[idx];\
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/multi_iter.hpp
  requiredBy: []
  timestamp: '2023-07-20 02:56:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/multi_iter.hpp
layout: document
redirect_from:
- /library/standard/multi_iter.hpp
- /library/standard/multi_iter.hpp.html
title: standard/multi_iter.hpp
---
