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
    path: graph/diameter.hpp
    title: "\u6728\u306E\u76F4\u5F84"
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
  - icon: ':heavy_check_mark:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':x:'
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
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/edge.hpp\"\n#include <iostream>\n\nnamespace internal\
    \ {\ntemplate <class DERIVED, class WEIGHT> struct _base_edge {\n    int from;\n\
    \    int to;\n    WEIGHT cost;\n    int id;\n    _base_edge(int _from, int _to,\
    \ WEIGHT _cost, int _id)\n        : from(_from), to(_to), cost(_cost), id(_id)\
    \ {}\n\n    friend bool operator>(const _base_edge &e1, const _base_edge &e) {\n\
    \        return e1.compare(e) > 0;\n    }\n    friend bool operator>=(const _base_edge\
    \ &e1, const _base_edge &e) {\n        return e1.compare(e) >= 0;\n    }\n   \
    \ friend bool operator<(const _base_edge &e1, const _base_edge &e) {\n       \
    \ return e1.compare(e) < 0;\n    }\n    friend bool operator<=(const _base_edge\
    \ &e1, const _base_edge &e) {\n        return e1.compare(e) <= 0;\n    }\n   \
    \ friend std::ostream &operator<<(std::ostream &os,\n                        \
    \            const _base_edge<DERIVED, WEIGHT> &e) {\n        e.print(os);\n \
    \       return os;\n    }\n    _base_edge &operator=(const _base_edge &e) = default;\n\
    \n    virtual ~_base_edge() = default;\n\n    operator int() const { return to;\
    \ }\n\n  protected:\n    virtual void print(std::ostream &os) const = 0;\n   \
    \ virtual int compare(const _base_edge &e) const = 0;\n};\n} // namespace internal\n\
    \ntemplate <class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT> {\n    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0,\
    \ 0) {}\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n\n\
    \  protected:\n    void print(std::ostream &os) const override {\n        os <<\
    \ this->from << \" \" << this->to << \" \" << this->cost;\n    }\n    int compare(\n\
    \        const internal::_base_edge<edge<WEIGHT>, WEIGHT> &e) const override {\n\
    \        if (this->cost == e.cost) {\n            if (this->from == e.from) {\n\
    \                return this->to - e.to;\n            }\n            return this->from\
    \ - e.from;\n        }\n        return this->cost - e.cost;\n    }\n};\n\ntemplate\
    \ <> struct edge<int> : public internal::_base_edge<edge<int>, int> {\n    static\
    \ const int cost = 1;\n    edge() : internal::_base_edge<edge<int>, int>(0, 0,\
    \ 0, 0) {}\n    edge(int _from, int _to, int _id)\n        : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int> &e) const override {\n\
    \        if (this->from == e.from) {\n            return this->to - e.to;\n  \
    \      }\n        return this->from - e.from;\n    }\n};\n"
  code: "#pragma once\n#include <iostream>\n\nnamespace internal {\ntemplate <class\
    \ DERIVED, class WEIGHT> struct _base_edge {\n    int from;\n    int to;\n   \
    \ WEIGHT cost;\n    int id;\n    _base_edge(int _from, int _to, WEIGHT _cost,\
    \ int _id)\n        : from(_from), to(_to), cost(_cost), id(_id) {}\n\n    friend\
    \ bool operator>(const _base_edge &e1, const _base_edge &e) {\n        return\
    \ e1.compare(e) > 0;\n    }\n    friend bool operator>=(const _base_edge &e1,\
    \ const _base_edge &e) {\n        return e1.compare(e) >= 0;\n    }\n    friend\
    \ bool operator<(const _base_edge &e1, const _base_edge &e) {\n        return\
    \ e1.compare(e) < 0;\n    }\n    friend bool operator<=(const _base_edge &e1,\
    \ const _base_edge &e) {\n        return e1.compare(e) <= 0;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os,\n                               \
    \     const _base_edge<DERIVED, WEIGHT> &e) {\n        e.print(os);\n        return\
    \ os;\n    }\n    _base_edge &operator=(const _base_edge &e) = default;\n\n  \
    \  virtual ~_base_edge() = default;\n\n    operator int() const { return to; }\n\
    \n  protected:\n    virtual void print(std::ostream &os) const = 0;\n    virtual\
    \ int compare(const _base_edge &e) const = 0;\n};\n} // namespace internal\n\n\
    template <class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT> {\n    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0,\
    \ 0) {}\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n\n\
    \  protected:\n    void print(std::ostream &os) const override {\n        os <<\
    \ this->from << \" \" << this->to << \" \" << this->cost;\n    }\n    int compare(\n\
    \        const internal::_base_edge<edge<WEIGHT>, WEIGHT> &e) const override {\n\
    \        if (this->cost == e.cost) {\n            if (this->from == e.from) {\n\
    \                return this->to - e.to;\n            }\n            return this->from\
    \ - e.from;\n        }\n        return this->cost - e.cost;\n    }\n};\n\ntemplate\
    \ <> struct edge<int> : public internal::_base_edge<edge<int>, int> {\n    static\
    \ const int cost = 1;\n    edge() : internal::_base_edge<edge<int>, int>(0, 0,\
    \ 0, 0) {}\n    edge(int _from, int _to, int _id)\n        : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int> &e) const override {\n\
    \        if (this->from == e.from) {\n            return this->to - e.to;\n  \
    \      }\n        return this->from - e.from;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/edge.hpp
  requiredBy:
  - graph/lowest_common_ancestor.hpp
  - graph/diameter.hpp
  - graph/reversed_graph.hpp
  - graph/graph.hpp
  - graph/Kruscal.hpp
  - graph/strongly_connected_components.hpp
  - graph/traveling_salesman.hpp
  - graph/shortest_path.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/topological_sort.hpp
  - graph/is_isomorphic.hpp
  - graph/lowlink.hpp
  - graph/doubling.hpp
  - other/random.hpp
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/jsc2021-g.test.cpp
  - test/grl-3-b.test.cpp
  - test/grl-5-a.test.cpp
  - test/grl-1-c.test.cpp
  - test/grl-1-a.test.cpp
  - test/grl-2-a.test.cpp
  - test/grl-3-a.test.cpp
  - test/manhattan-mst.test.cpp
  - test/grl-5-c.test.cpp
documentation_of: graph/edge.hpp
layout: document
redirect_from:
- /library/graph/edge.hpp
- /library/graph/edge.hpp.html
title: graph/edge.hpp
---
