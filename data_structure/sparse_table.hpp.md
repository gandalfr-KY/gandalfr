---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/lowest_common_ancestor.hpp
    title: "\u7121\u5411\u5358\u7D14\u6728\u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\
      \u3092\u6C42\u3081\u308B\u30AF\u30E9\u30B9"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-5-c.test.cpp
    title: test/grl-5-c.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D50\u5408\u5247\u30FB\u51AA\u7B49\u6027\u3092\u6E80\u305F\u3059\
      \u6F14\u7B97\u306E\u66F4\u65B0\u7121\u3057\u533A\u9593\u30AF\u30A8\u30EA\u51E6\
      \u7406"
    links: []
  bundledCode: "#line 1 \"data_structure/sparse_table.hpp\"\n\n\n#include <functional>\n\
    #include <vector>\n\n/**\n * @brief \u7D50\u5408\u5247\u30FB\u51AA\u7B49\u6027\
    \u3092\u6E80\u305F\u3059\u6F14\u7B97\u306E\u66F4\u65B0\u7121\u3057\u533A\u9593\
    \u30AF\u30A8\u30EA\u51E6\u7406\n */\ntemplate <class T> class sparse_table {\n\
    \  private:\n    const std::function<T(T, T)> op;\n    std::vector<std::vector<T>>\
    \ table;\n    std::vector<short> log_table; // log_table[n] := 2^k < n \u3067\u3042\
    \u308B\u6700\u5927\u306E k\n\n  public:\n    sparse_table(const std::function<T(T,\
    \ T)> &f) : op(f) {}\n\n    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\
    \u671F\u5316\n    void init(const std::vector<T> &vec) {\n        table = {vec};\n\
    \        log_table.clear();\n\n        for (int i = 0; (1 << i) < table[i].size();\
    \ i++) {\n            table.push_back({});\n            for (int j = 0; j + (1\
    \ << i) < table[i].size(); j++) {\n                table[i + 1].push_back(op(table[i][j],\
    \ table[i][j + (1 << i)]));\n            }\n        }\n\n        log_table.resize(vec.size()\
    \ + 1, 0);\n        for (int i = 2; i <= vec.size(); i++) {\n            log_table[i]\
    \ = log_table[i >> 1] + 1;\n        }\n    }\n\n    /**\n     * @brief [l, r)\
    \ \u306E\u6F14\u7B97\u7D50\u679C\u3092\u5F97\u308B\n     * @attention l >= r \u306E\
    \u3068\u304D\u672A\u5B9A\u7FA9\n     */\n    T get(int l, int r) {\n        int\
    \ k = log_table[r - l];\n        return op(table[k][l], table[k][r - (1 << k)]);\n\
    \    }\n};\n\ntemplate <typename T> struct RmQ_sparse_table : public sparse_table<T>\
    \ {\n    RmQ_sparse_table()\n        : RmQ_sparse_table<T>::sparse_table(\n  \
    \            [](T a, T b) { return (a < b ? a : b); }) {}\n};\n\ntemplate <typename\
    \ T> struct RMQ_sparse_table : public sparse_table<T> {\n    RMQ_sparse_table()\n\
    \        : RMQ_sparse_table<T>::sparse_table(\n              [](T a, T b) { return\
    \ (a > b ? a : b); }) {}\n};\n\n\n"
  code: "#ifndef SPARSE_TABLE\n#define SPARSE_TABLE\n#include <functional>\n#include\
    \ <vector>\n\n/**\n * @brief \u7D50\u5408\u5247\u30FB\u51AA\u7B49\u6027\u3092\u6E80\
    \u305F\u3059\u6F14\u7B97\u306E\u66F4\u65B0\u7121\u3057\u533A\u9593\u30AF\u30A8\
    \u30EA\u51E6\u7406\n */\ntemplate <class T> class sparse_table {\n  private:\n\
    \    const std::function<T(T, T)> op;\n    std::vector<std::vector<T>> table;\n\
    \    std::vector<short> log_table; // log_table[n] := 2^k < n \u3067\u3042\u308B\
    \u6700\u5927\u306E k\n\n  public:\n    sparse_table(const std::function<T(T, T)>\
    \ &f) : op(f) {}\n\n    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\
    \u5316\n    void init(const std::vector<T> &vec) {\n        table = {vec};\n \
    \       log_table.clear();\n\n        for (int i = 0; (1 << i) < table[i].size();\
    \ i++) {\n            table.push_back({});\n            for (int j = 0; j + (1\
    \ << i) < table[i].size(); j++) {\n                table[i + 1].push_back(op(table[i][j],\
    \ table[i][j + (1 << i)]));\n            }\n        }\n\n        log_table.resize(vec.size()\
    \ + 1, 0);\n        for (int i = 2; i <= vec.size(); i++) {\n            log_table[i]\
    \ = log_table[i >> 1] + 1;\n        }\n    }\n\n    /**\n     * @brief [l, r)\
    \ \u306E\u6F14\u7B97\u7D50\u679C\u3092\u5F97\u308B\n     * @attention l >= r \u306E\
    \u3068\u304D\u672A\u5B9A\u7FA9\n     */\n    T get(int l, int r) {\n        int\
    \ k = log_table[r - l];\n        return op(table[k][l], table[k][r - (1 << k)]);\n\
    \    }\n};\n\ntemplate <typename T> struct RmQ_sparse_table : public sparse_table<T>\
    \ {\n    RmQ_sparse_table()\n        : RmQ_sparse_table<T>::sparse_table(\n  \
    \            [](T a, T b) { return (a < b ? a : b); }) {}\n};\n\ntemplate <typename\
    \ T> struct RMQ_sparse_table : public sparse_table<T> {\n    RMQ_sparse_table()\n\
    \        : RMQ_sparse_table<T>::sparse_table(\n              [](T a, T b) { return\
    \ (a > b ? a : b); }) {}\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/sparse_table.hpp
  requiredBy:
  - graph/lowest_common_ancestor.hpp
  timestamp: '2023-06-19 01:40:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/grl-5-c.test.cpp
documentation_of: data_structure/sparse_table.hpp
layout: document
redirect_from:
- /library/data_structure/sparse_table.hpp
- /library/data_structure/sparse_table.hpp.html
title: "\u7D50\u5408\u5247\u30FB\u51AA\u7B49\u6027\u3092\u6E80\u305F\u3059\u6F14\u7B97\
  \u306E\u66F4\u65B0\u7121\u3057\u533A\u9593\u30AF\u30A8\u30EA\u51E6\u7406"
---
