---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: standard/inversion.hpp
    title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\
      \u3067\u6307\u5B9A\u3057\u3001\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/alds1-5-d.test.cpp
    title: test/alds1-5-d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dsl-2-b.test.cpp
    title: test/dsl-2-b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97"
    links: []
  bundledCode: "#line 1 \"data_structure/binary_indexed_tree.hpp\"\n\n\n#include <vector>\n\
    \n/**\n * @brief \u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97\
    \n * @attention 0-indexed\n*/\ntemplate<class T>\nstruct binary_indexed_tree{\n\
    \  private:\n    int N;\n    std::vector<T> bit;\n\n  public:\n    binary_indexed_tree(int\
    \ siz) : N(siz), bit(N, 0) {}\n\n    /** \n     * @return a \u306E\u4F4D\u7F6E\
    \u306B w \u3092\u52A0\u7B97\n     */\n    void add(int a, T w){\n        for(int\
    \ x = a + 1; x <= N; x += x & -x) bit[x - 1] += w;\n    }\n\n    /** \n     *\
    \ @return [0, a) \u306E\u7DCF\u548C\n     */\n    T get(int a){\n        T ret\
    \ = 0;\n        for(int x = a; x > 0; x -= x & -x) ret += bit[x - 1];\n      \
    \  return ret;\n    }\n};\n\n\n"
  code: "#ifndef BINARY_INDEXED_TREE\n#define BINARY_INDEXED_TREE\n#include <vector>\n\
    \n/**\n * @brief \u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97\
    \n * @attention 0-indexed\n*/\ntemplate<class T>\nstruct binary_indexed_tree{\n\
    \  private:\n    int N;\n    std::vector<T> bit;\n\n  public:\n    binary_indexed_tree(int\
    \ siz) : N(siz), bit(N, 0) {}\n\n    /** \n     * @return a \u306E\u4F4D\u7F6E\
    \u306B w \u3092\u52A0\u7B97\n     */\n    void add(int a, T w){\n        for(int\
    \ x = a + 1; x <= N; x += x & -x) bit[x - 1] += w;\n    }\n\n    /** \n     *\
    \ @return [0, a) \u306E\u7DCF\u548C\n     */\n    T get(int a){\n        T ret\
    \ = 0;\n        for(int x = a; x > 0; x -= x & -x) ret += bit[x - 1];\n      \
    \  return ret;\n    }\n};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/binary_indexed_tree.hpp
  requiredBy:
  - standard/inversion.hpp
  timestamp: '2023-06-07 01:31:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/alds1-5-d.test.cpp
  - test/dsl-2-b.test.cpp
documentation_of: data_structure/binary_indexed_tree.hpp
layout: document
redirect_from:
- /library/data_structure/binary_indexed_tree.hpp
- /library/data_structure/binary_indexed_tree.hpp.html
title: "\u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97"
---
