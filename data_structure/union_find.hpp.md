---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/Kruscal.hpp
    title: graph/Kruscal.hpp
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':heavy_check_mark:'
    path: graph/Warshall_Floyd.hpp
    title: graph/Warshall_Floyd.hpp
  - icon: ':heavy_check_mark:'
    path: graph/diameter.hpp
    title: graph/diameter.hpp
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
  - icon: ':question:'
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
  - icon: ':warning:'
    path: graph/is_isomorphic.hpp
    title: graph/is_isomorphic.hpp
  - icon: ':warning:'
    path: graph/lowest_common_ancestor.hpp
    title: graph/lowest_common_ancestor.hpp
  - icon: ':question:'
    path: graph/lowlink.hpp
    title: "\u5358\u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\u70B9\u30FB\
      \u6A4B\u3092\u6C42\u3081\u308B"
  - icon: ':warning:'
    path: graph/reversed_graph.hpp
    title: graph/reversed_graph.hpp
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: graph/shortest_path.hpp
  - icon: ':warning:'
    path: graph/strongly_connected_components.hpp
    title: graph/strongly_connected_components.hpp
  - icon: ':warning:'
    path: graph/topological_sort.hpp
    title: graph/topological_sort.hpp
  - icon: ':warning:'
    path: graph/traveling_salesman.hpp
    title: graph/traveling_salesman.hpp
  - icon: ':question:'
    path: math/matrix.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u96A3\u63A5\u884C\u5217\u306B\u5909\u63DB"
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
  - icon: ':heavy_check_mark:'
    path: test/grl-2-a.test.cpp
    title: test/grl-2-a.test.cpp
  - icon: ':x:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-b.test.cpp
    title: test/grl-3-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/itp1-t-d.test.cpp
    title: test/itp1-t-d.test.cpp
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/manhattan-mst.test.cpp
    title: test/manhattan-mst.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/union_find.hpp\"\n\n\n#include <vector>\n\
    #include <algorithm>\n#include <assert.h>\n\nclass union_find{\n  private:\n \
    \   int N;\n    std::vector<int> par, group_siz;\n    int group_num; // \u96C6\
    \u5408\u306E\u6570\n\n  public:\n    union_find() : N(0) {}\n    union_find(int\
    \ n) : N(n), par(n, -1), group_siz(n, 1), group_num(n) {}\n\n    void expand(int\
    \ n){\n        if(n <= N) return;\n        N = n;\n        par.resize(n, -1);\n\
    \        group_siz.resize(n, 1);\n        group_num += n - N;\n    }\n\n    int\
    \ leader(int x){\n        if(par[x] == -1) return x;\n        else return par[x]\
    \ = leader(par[x]);\n    }\n \n    bool same(int x, int y){\n        return leader(x)\
    \ == leader(y);\n    }\n \n    bool merge(int x, int y){\n        x = leader(x);\
    \ y = leader(y);\n        if(x == y) return false;\n        // \u5C0F\u3055\u3044\
    \u307B\u3046\u306B\u7D71\u5408\n        if(group_siz[x] < group_siz[y]) std::swap(x,\
    \ y);\n        par[y] = x;\n        group_siz[x] += group_siz[y];\n        group_num--;\n\
    \        return true;\n    }\n\n    // x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\
    \u30D7\u306E\u30B5\u30A4\u30BA\u3092\u8FD4\u3059\n    int size(int x){\n     \
    \   return group_siz[leader(x)];\n    }\n\n    int count_groups() const {\n  \
    \      return group_num;\n    }\n\n    std::vector<std::vector<int>> groups(){\n\
    \        std::vector<std::vector<int>> result(N);\n        for(int i = 0; i <\
    \ N; i++) result[i].reserve(group_siz[i]);\n        for(int i = 0; i < N; i++)\
    \ result[leader(i)].push_back(i);\n        result.erase(\n            std::remove_if(result.begin(),\
    \ result.end(),\n            [&](const std::vector<int>& v) { return v.empty();\
    \ }), result.end());\n        return result;\n    }\n};\n\n\n"
  code: "#ifndef UNION_FIND\n#define UNION_FIND\n#include <vector>\n#include <algorithm>\n\
    #include <assert.h>\n\nclass union_find{\n  private:\n    int N;\n    std::vector<int>\
    \ par, group_siz;\n    int group_num; // \u96C6\u5408\u306E\u6570\n\n  public:\n\
    \    union_find() : N(0) {}\n    union_find(int n) : N(n), par(n, -1), group_siz(n,\
    \ 1), group_num(n) {}\n\n    void expand(int n){\n        if(n <= N) return;\n\
    \        N = n;\n        par.resize(n, -1);\n        group_siz.resize(n, 1);\n\
    \        group_num += n - N;\n    }\n\n    int leader(int x){\n        if(par[x]\
    \ == -1) return x;\n        else return par[x] = leader(par[x]);\n    }\n \n \
    \   bool same(int x, int y){\n        return leader(x) == leader(y);\n    }\n\
    \ \n    bool merge(int x, int y){\n        x = leader(x); y = leader(y);\n   \
    \     if(x == y) return false;\n        // \u5C0F\u3055\u3044\u307B\u3046\u306B\
    \u7D71\u5408\n        if(group_siz[x] < group_siz[y]) std::swap(x, y);\n     \
    \   par[y] = x;\n        group_siz[x] += group_siz[y];\n        group_num--;\n\
    \        return true;\n    }\n\n    // x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\
    \u30D7\u306E\u30B5\u30A4\u30BA\u3092\u8FD4\u3059\n    int size(int x){\n     \
    \   return group_siz[leader(x)];\n    }\n\n    int count_groups() const {\n  \
    \      return group_num;\n    }\n\n    std::vector<std::vector<int>> groups(){\n\
    \        std::vector<std::vector<int>> result(N);\n        for(int i = 0; i <\
    \ N; i++) result[i].reserve(group_siz[i]);\n        for(int i = 0; i < N; i++)\
    \ result[leader(i)].push_back(i);\n        result.erase(\n            std::remove_if(result.begin(),\
    \ result.end(),\n            [&](const std::vector<int>& v) { return v.empty();\
    \ }), result.end());\n        return result;\n    }\n};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/union_find.hpp
  requiredBy:
  - other/random.hpp
  - math/matrix.hpp
  - graph/diameter.hpp
  - graph/Warshall_Floyd.hpp
  - graph/lowest_common_ancestor.hpp
  - graph/lowlink.hpp
  - graph/shortest_path.hpp
  - graph/Kruscal.hpp
  - graph/reversed_graph.hpp
  - graph/strongly_connected_components.hpp
  - graph/graph.hpp
  - graph/is_isomorphic.hpp
  - graph/traveling_salesman.hpp
  - graph/doubling.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/topological_sort.hpp
  timestamp: '2023-04-01 20:47:10+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/grl-3-a.test.cpp
  - test/itp1-t-d.test.cpp
  - test/grl-3-b.test.cpp
  - test/grl-1-a.test.cpp
  - test/grl-2-a.test.cpp
  - test/manhattan-mst.test.cpp
  - test/grl-5-a.test.cpp
  - test/grl-1-c.test.cpp
  - test/jsc2021-g.test.cpp
documentation_of: data_structure/union_find.hpp
layout: document
redirect_from:
- /library/data_structure/union_find.hpp
- /library/data_structure/union_find.hpp.html
title: data_structure/union_find.hpp
---
