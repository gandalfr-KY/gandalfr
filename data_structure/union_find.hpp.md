---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
  - icon: ':question:'
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
  - icon: ':warning:'
    path: graph/is_isomorphic.hpp
    title: graph/is_isomorphic.hpp
  - icon: ':heavy_check_mark:'
    path: graph/lowest_common_ancestor.hpp
    title: "\u7121\u5411\u5358\u7D14\u6728\u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\
      \u3092\u6C42\u3081\u308B\u30AF\u30E9\u30B9"
  - icon: ':warning:'
    path: graph/traveling_salesman.hpp
    title: graph/traveling_salesman.hpp
  - icon: ':warning:'
    path: other/random.hpp
    title: other/random.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-1-a.test.cpp
    title: test/grl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-1-c.test.cpp
    title: test/grl-1-c.test.cpp
  - icon: ':x:'
    path: test/grl-2-a.test.cpp
    title: test/grl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-b.test.cpp
    title: test/grl-3-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-5-c.test.cpp
    title: test/grl-5-c.test.cpp
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/manhattan-mst.test.cpp
    title: test/manhattan-mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/shortest_path.test.cpp
    title: test/shortest_path.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "\u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059"
    links: []
  bundledCode: "#line 2 \"data_structure/union_find.hpp\"\n#include <assert.h>\n\n\
    #include <algorithm>\n#include <vector>\n\nclass union_find {\n  private:\n  \
    \  int N;\n    mutable std::vector<int> par;\n    std::vector<int> nxt;\n    int\
    \ group_num; // \u96C6\u5408\u306E\u6570\n\n  public:\n    union_find() : N(0),\
    \ group_num(0) {}\n    union_find(int n) : N(n), par(n, -1), nxt(n), group_num(n)\
    \ {\n        std::iota(nxt.begin(), nxt.end(), 0);\n    }\n\n    /**\n     * @brief\
    \ \u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059\n     * @attention \u5C0F\
    \u3055\u304F\u306F\u3067\u304D\u306A\u3044\n     */\n    void expand(int n) {\n\
    \        if (n <= N)\n            return;\n        par.resize(n, -1);\n      \
    \  nxt.resize(n);\n        for (int i = N; i < n; ++i)\n            nxt[i] = i;\n\
    \        group_num += n - N;\n        N = n;\n    }\n\n    int leader(int x) const\
    \ {\n        return (par[x] < 0 ? x : par[x] = leader(par[x]));\n    }\n\n   \
    \ bool same(int x, int y) const { return leader(x) == leader(y); }\n\n    bool\
    \ merge(int x, int y) {\n        if ((x = leader(x)) == (y = leader(y)))\n   \
    \         return false;\n        if (-par[x] > -par[y])\n            std::swap(x,\
    \ y);\n\n        par[x] += par[y];\n        par[y] = x;\n        std::swap(nxt[x],\
    \ nxt[y]);\n        group_num--;\n        return true;\n    }\n\n    /**\n   \
    \  * @brief x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\u30D7\u306E\u30B5\u30A4\
    \u30BA\u3092\u8FD4\u3059\n     */\n    int size(int x) const { return -par[leader(x)];\
    \ }\n\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u30CE\u30FC\u30C9\u306E\
    \u6570\n     */\n    int size() const { return N; }\n\n    std::vector<int> contained_group(int\
    \ x) const {\n        std::vector<int> ret{x};\n        for (int cu = nxt[x];\
    \ cu != ret[0]; cu = nxt[cu])\n            ret.push_back(cu);\n        return\
    \ ret;\n    }\n\n    int count_groups() const { return group_num; }\n\n    std::vector<std::vector<int>>\
    \ all_groups() const {\n        std::vector<std::vector<int>> result;\n      \
    \  result.reserve(group_num);\n        std::vector<bool> used(N, false);\n   \
    \     for (int i = 0; i < N; ++i) {\n            if (!used[i]) {\n           \
    \     result.emplace_back(contained_group(i));\n                for (int x : result.back())\
    \ {\n                    used[x] = true;\n                }\n            }\n \
    \       }\n        return result;\n    }\n};\n"
  code: "#pragma once\n#include <assert.h>\n\n#include <algorithm>\n#include <vector>\n\
    \nclass union_find {\n  private:\n    int N;\n    mutable std::vector<int> par;\n\
    \    std::vector<int> nxt;\n    int group_num; // \u96C6\u5408\u306E\u6570\n\n\
    \  public:\n    union_find() : N(0), group_num(0) {}\n    union_find(int n) :\
    \ N(n), par(n, -1), nxt(n), group_num(n) {\n        std::iota(nxt.begin(), nxt.end(),\
    \ 0);\n    }\n\n    /**\n     * @brief \u9802\u70B9\u3092 n \u500B\u306B\u5897\
    \u3084\u3059\n     * @attention \u5C0F\u3055\u304F\u306F\u3067\u304D\u306A\u3044\
    \n     */\n    void expand(int n) {\n        if (n <= N)\n            return;\n\
    \        par.resize(n, -1);\n        nxt.resize(n);\n        for (int i = N; i\
    \ < n; ++i)\n            nxt[i] = i;\n        group_num += n - N;\n        N =\
    \ n;\n    }\n\n    int leader(int x) const {\n        return (par[x] < 0 ? x :\
    \ par[x] = leader(par[x]));\n    }\n\n    bool same(int x, int y) const { return\
    \ leader(x) == leader(y); }\n\n    bool merge(int x, int y) {\n        if ((x\
    \ = leader(x)) == (y = leader(y)))\n            return false;\n        if (-par[x]\
    \ > -par[y])\n            std::swap(x, y);\n\n        par[x] += par[y];\n    \
    \    par[y] = x;\n        std::swap(nxt[x], nxt[y]);\n        group_num--;\n \
    \       return true;\n    }\n\n    /**\n     * @brief x \u306E\u5C5E\u3059\u308B\
    \u30B0\u30EB\u30FC\u30D7\u306E\u30B5\u30A4\u30BA\u3092\u8FD4\u3059\n     */\n\
    \    int size(int x) const { return -par[leader(x)]; }\n\n    /**\n     * @brief\
    \ \u3059\u3079\u3066\u306E\u30CE\u30FC\u30C9\u306E\u6570\n     */\n    int size()\
    \ const { return N; }\n\n    std::vector<int> contained_group(int x) const {\n\
    \        std::vector<int> ret{x};\n        for (int cu = nxt[x]; cu != ret[0];\
    \ cu = nxt[cu])\n            ret.push_back(cu);\n        return ret;\n    }\n\n\
    \    int count_groups() const { return group_num; }\n\n    std::vector<std::vector<int>>\
    \ all_groups() const {\n        std::vector<std::vector<int>> result;\n      \
    \  result.reserve(group_num);\n        std::vector<bool> used(N, false);\n   \
    \     for (int i = 0; i < N; ++i) {\n            if (!used[i]) {\n           \
    \     result.emplace_back(contained_group(i));\n                for (int x : result.back())\
    \ {\n                    used[x] = true;\n                }\n            }\n \
    \       }\n        return result;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/union_find.hpp
  requiredBy:
  - other/random.hpp
  - graph/graph.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/doubling.hpp
  - graph/traveling_salesman.hpp
  - graph/lowest_common_ancestor.hpp
  - graph/is_isomorphic.hpp
  timestamp: '2023-07-20 02:56:32+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/manhattan-mst.test.cpp
  - test/grl-5-c.test.cpp
  - test/grl-1-a.test.cpp
  - test/grl-2-a.test.cpp
  - test/grl-3-a.test.cpp
  - test/grl-3-b.test.cpp
  - test/shortest_path.test.cpp
  - test/grl-1-c.test.cpp
  - test/jsc2021-g.test.cpp
  - test/grl-5-a.test.cpp
documentation_of: data_structure/union_find.hpp
layout: document
redirect_from:
- /library/data_structure/union_find.hpp
- /library/data_structure/union_find.hpp.html
title: "\u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059"
---
