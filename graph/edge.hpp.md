---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/Kruscal.hpp
    title: graph/Kruscal.hpp
  - icon: ':warning:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: graph/Manhattan_minimum_spanning_tree.hpp
  - icon: ':heavy_check_mark:'
    path: graph/Warshall_Floyd.hpp
    title: graph/Warshall_Floyd.hpp
  - icon: ':heavy_check_mark:'
    path: graph/diameter.hpp
    title: graph/diameter.hpp
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: "\u30CE\u30FC\u30C9\u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\u3059"
  - icon: ':warning:'
    path: graph/is_isomorphic.hpp
    title: graph/is_isomorphic.hpp
  - icon: ':warning:'
    path: graph/lowest_common_ancestor.hpp
    title: graph/lowest_common_ancestor.hpp
  - icon: ':warning:'
    path: graph/lowlink.hpp
    title: graph/lowlink.hpp
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
  - icon: ':heavy_check_mark:'
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
  - icon: ':heavy_check_mark:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/itp1-t-d.test.cpp
    title: test/itp1-t-d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/edge.hpp\"\n\n\n#include <iostream>\n\nnamespace internal{\n\
    \    template<class DERIVED, class WEIGHT>\n    struct _base_edge{\n        int\
    \ from;\n        int to;\n        WEIGHT cost;\n        int id;\n        _base_edge(int\
    \ _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to), cost(_cost),\
    \ id(_id) {}\n\n        friend bool operator>(const _base_edge &e1, const _base_edge\
    \ &e){\n            return e1.compare(e) > 0;\n        }\n        friend bool\
    \ operator>=(const _base_edge &e1, const _base_edge &e){\n            return e1.compare(e)\
    \ >= 0;\n        }\n        friend bool operator<(const _base_edge &e1, const\
    \ _base_edge &e){\n            return e1.compare(e) < 0;\n        }\n        friend\
    \ bool operator<=(const _base_edge &e1, const _base_edge &e){\n            return\
    \ e1.compare(e) <= 0;\n        }\n        friend std::ostream &operator<<(std::ostream\
    \ &os, const _base_edge<DERIVED, WEIGHT> &e) {\n            e.print(os);\n   \
    \         return os;\n        }\n        const _base_edge &operator=(const _base_edge\
    \ &e){\n            from = e.from, to = e.to, cost = e.cost, id = e.id;\n    \
    \        return *this;\n        }\n\n        virtual ~_base_edge() = default;\
    \ \n\n      protected:\n        virtual void print(std::ostream &os) const = 0;\n\
    \        virtual int compare(const _base_edge &e) const = 0;\n    };\n}\n\ntemplate<class\
    \ WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>, WEIGHT>{\n\
    \    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0, 0) {}\n    using\
    \ internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n  protected:\n    void\
    \ print(std::ostream &os) const override {\n        os << this->from << \" \"\
    \ << this->to << \" \" << this->cost;\n    }  \n    int compare(const internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT>& e) const override {\n        if(this->cost == e.cost){\n          \
    \  if(this->from == e.from){\n                return this->to - e.to;\n      \
    \      }\n            return this->from - e.from;\n        }\n        return this->cost\
    \ - e.cost;\n    }\n};\n\ntemplate<>\nstruct edge<int> : public internal::_base_edge<edge<int>,\
    \ int>{\n    const int cost = 1;\n    edge() : internal::_base_edge<edge<int>,\
    \ int>(0, 0, 0, 0) {}\n    edge(int _from, int _to, int _id) : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int>& e) const override {\n\
    \        if(this->from == e.from){\n            return this->to - e.to;\n    \
    \    }\n        return this->from - e.from;\n    }\n};\n\n\n"
  code: "#ifndef EDGE_STRUCT\n#define EDGE_STRUCT\n#include <iostream>\n\nnamespace\
    \ internal{\n    template<class DERIVED, class WEIGHT>\n    struct _base_edge{\n\
    \        int from;\n        int to;\n        WEIGHT cost;\n        int id;\n \
    \       _base_edge(int _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to),\
    \ cost(_cost), id(_id) {}\n\n        friend bool operator>(const _base_edge &e1,\
    \ const _base_edge &e){\n            return e1.compare(e) > 0;\n        }\n  \
    \      friend bool operator>=(const _base_edge &e1, const _base_edge &e){\n  \
    \          return e1.compare(e) >= 0;\n        }\n        friend bool operator<(const\
    \ _base_edge &e1, const _base_edge &e){\n            return e1.compare(e) < 0;\n\
    \        }\n        friend bool operator<=(const _base_edge &e1, const _base_edge\
    \ &e){\n            return e1.compare(e) <= 0;\n        }\n        friend std::ostream\
    \ &operator<<(std::ostream &os, const _base_edge<DERIVED, WEIGHT> &e) {\n    \
    \        e.print(os);\n            return os;\n        }\n        const _base_edge\
    \ &operator=(const _base_edge &e){\n            from = e.from, to = e.to, cost\
    \ = e.cost, id = e.id;\n            return *this;\n        }\n\n        virtual\
    \ ~_base_edge() = default; \n\n      protected:\n        virtual void print(std::ostream\
    \ &os) const = 0;\n        virtual int compare(const _base_edge &e) const = 0;\n\
    \    };\n}\n\ntemplate<class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT>{\n    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0, 0)\
    \ {}\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n  protected:\n\
    \    void print(std::ostream &os) const override {\n        os << this->from <<\
    \ \" \" << this->to << \" \" << this->cost;\n    }  \n    int compare(const internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT>& e) const override {\n        if(this->cost == e.cost){\n          \
    \  if(this->from == e.from){\n                return this->to - e.to;\n      \
    \      }\n            return this->from - e.from;\n        }\n        return this->cost\
    \ - e.cost;\n    }\n};\n\ntemplate<>\nstruct edge<int> : public internal::_base_edge<edge<int>,\
    \ int>{\n    const int cost = 1;\n    edge() : internal::_base_edge<edge<int>,\
    \ int>(0, 0, 0, 0) {}\n    edge(int _from, int _to, int _id) : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int>& e) const override {\n\
    \        if(this->from == e.from){\n            return this->to - e.to;\n    \
    \    }\n        return this->from - e.from;\n    }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/edge.hpp
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
  timestamp: '2023-06-07 00:04:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/itp1-t-d.test.cpp
  - test/grl-1-a.test.cpp
  - test/grl-2-a.test.cpp
  - test/grl-5-a.test.cpp
  - test/grl-1-c.test.cpp
documentation_of: graph/edge.hpp
layout: document
redirect_from:
- /library/graph/edge.hpp
- /library/graph/edge.hpp.html
title: graph/edge.hpp
---
