---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/practice2/submissions/36388906
  bundledCode: "#line 2 \"graph/strongly_connected_components.hpp\"\n\n/* \u5F37\u9023\
    \u7D50\u6210\u5206\u5206\u89E3\n * groups() := \u540C\u4E00\u9023\u7D50\u6210\u5206\
    \u3092\u307E\u3068\u3081\u305F\u4E8C\u6B21\u5143\u914D\u5217\u3092\u8FD4\u3059\
    \n * group_id()[i] := \u30CE\u30FC\u30C9 i \u304C groups() \u306E\u3069\u306E\u30A4\
    \u30F3\u30C7\u30C3\u30AF\u30B9\u306B\u683C\u7D0D\u3055\u308C\u3066\u3044\u308B\
    \u304B\n * simplified_graph() :=\n * \u5F37\u9023\u7D50\u6210\u5206\u3092\u7C21\
    \u7D04\u3057\u305F\u30B0\u30E9\u30D5\u3092\u8FD4\u3059\u3002\u305F\u3060\u3057\
    \u3001\u81EA\u5DF1\u30EB\u30FC\u30D7\u7121\u3057\u3001\u591A\u91CD\u8FBA\u3042\
    \u308A \u524D\u51E6\u7406\n * O(N) verify : https://atcoder.jp/contests/practice2/submissions/36388906\n\
    \ */\ntemplate <typename WEIGHT> class strongly_connected_components {\n  private:\n\
    \    std::vector<int> grp_id;\n    std::vector<std::vector<int>> grps;\n    graph<WEIGHT,\
    \ true> S;\n\n    void dfs1(const graph<WEIGHT, true> &G, int cu, std::vector<int>\
    \ &ord,\n              std::vector<bool> &used) {\n        if (used[cu])\n   \
    \         return;\n        used[cu] = true;\n        for (auto &e : G[cu])\n \
    \           dfs1(G, e.to, ord, used);\n        ord.push_back(cu);\n    }\n\n \
    \   void dfs2(const graph<WEIGHT, true> &G, int cu, int id) {\n        if (grp_id[cu]\
    \ != -1)\n            return;\n        grp_id[cu] = id;\n        for (auto &e\
    \ : G[cu])\n            dfs2(G, e.to, id);\n    }\n\n  public:\n    strongly_connected_components(const\
    \ graph<WEIGHT, true> &G)\n        : grp_id(G.count_nodes(), -1) {\n        int\
    \ N = G.count_nodes();\n        std::vector<bool> used(N, false);\n        std::vector<int>\
    \ ord;\n        graph<WEIGHT, true> R(G.reverse());\n\n        for (int i = 0;\
    \ i < N; i++) {\n            dfs1(G, i, ord, used);\n        }\n\n        int\
    \ id = 0;\n        for (int i = N - 1; i >= 0; i--)\n            if (grp_id[ord[i]]\
    \ == -1) {\n                dfs2(R, ord[i], id);\n                id++;\n    \
    \        }\n\n        grps.resize(id);\n        for (int i = 0; i < N; i++)\n\
    \            grps[grp_id[i]].push_back(i);\n\n        S.expand(grps.size());\n\
    \        for (auto e : G.edges()) {\n            e.from = grp_id[e.from];\n  \
    \          e.to = grp_id[e.to];\n            if (e.from != e.to)\n           \
    \     S.add_edge(e);\n        }\n    }\n\n    const std::vector<std::vector<int>>\
    \ &groups() { return grps; }\n    const std::vector<int> &group_id() { return\
    \ grp_id; }\n    const graph<WEIGHT, true> &simplified_graph() { return S; };\n\
    };\n"
  code: "#pragma once\n\n/* \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\n * groups()\
    \ := \u540C\u4E00\u9023\u7D50\u6210\u5206\u3092\u307E\u3068\u3081\u305F\u4E8C\u6B21\
    \u5143\u914D\u5217\u3092\u8FD4\u3059\n * group_id()[i] := \u30CE\u30FC\u30C9 i\
    \ \u304C groups() \u306E\u3069\u306E\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u306B\
    \u683C\u7D0D\u3055\u308C\u3066\u3044\u308B\u304B\n * simplified_graph() :=\n *\
    \ \u5F37\u9023\u7D50\u6210\u5206\u3092\u7C21\u7D04\u3057\u305F\u30B0\u30E9\u30D5\
    \u3092\u8FD4\u3059\u3002\u305F\u3060\u3057\u3001\u81EA\u5DF1\u30EB\u30FC\u30D7\
    \u7121\u3057\u3001\u591A\u91CD\u8FBA\u3042\u308A \u524D\u51E6\u7406\n * O(N) verify\
    \ : https://atcoder.jp/contests/practice2/submissions/36388906\n */\ntemplate\
    \ <typename WEIGHT> class strongly_connected_components {\n  private:\n    std::vector<int>\
    \ grp_id;\n    std::vector<std::vector<int>> grps;\n    graph<WEIGHT, true> S;\n\
    \n    void dfs1(const graph<WEIGHT, true> &G, int cu, std::vector<int> &ord,\n\
    \              std::vector<bool> &used) {\n        if (used[cu])\n           \
    \ return;\n        used[cu] = true;\n        for (auto &e : G[cu])\n         \
    \   dfs1(G, e.to, ord, used);\n        ord.push_back(cu);\n    }\n\n    void dfs2(const\
    \ graph<WEIGHT, true> &G, int cu, int id) {\n        if (grp_id[cu] != -1)\n \
    \           return;\n        grp_id[cu] = id;\n        for (auto &e : G[cu])\n\
    \            dfs2(G, e.to, id);\n    }\n\n  public:\n    strongly_connected_components(const\
    \ graph<WEIGHT, true> &G)\n        : grp_id(G.count_nodes(), -1) {\n        int\
    \ N = G.count_nodes();\n        std::vector<bool> used(N, false);\n        std::vector<int>\
    \ ord;\n        graph<WEIGHT, true> R(G.reverse());\n\n        for (int i = 0;\
    \ i < N; i++) {\n            dfs1(G, i, ord, used);\n        }\n\n        int\
    \ id = 0;\n        for (int i = N - 1; i >= 0; i--)\n            if (grp_id[ord[i]]\
    \ == -1) {\n                dfs2(R, ord[i], id);\n                id++;\n    \
    \        }\n\n        grps.resize(id);\n        for (int i = 0; i < N; i++)\n\
    \            grps[grp_id[i]].push_back(i);\n\n        S.expand(grps.size());\n\
    \        for (auto e : G.edges()) {\n            e.from = grp_id[e.from];\n  \
    \          e.to = grp_id[e.to];\n            if (e.from != e.to)\n           \
    \     S.add_edge(e);\n        }\n    }\n\n    const std::vector<std::vector<int>>\
    \ &groups() { return grps; }\n    const std::vector<int> &group_id() { return\
    \ grp_id; }\n    const graph<WEIGHT, true> &simplified_graph() { return S; };\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components.hpp
  requiredBy: []
  timestamp: '2023-07-01 19:17:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/strongly_connected_components.hpp
layout: document
redirect_from:
- /library/graph/strongly_connected_components.hpp
- /library/graph/strongly_connected_components.hpp.html
title: graph/strongly_connected_components.hpp
---
