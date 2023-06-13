---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/alds1-5-d.test.cpp
    title: test/alds1-5-d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/io_supporter.hpp\"\n\n\n#include <iostream>\n#include\
    \ <iterator>\n#include <utility>\n#include <queue>\n\ntemplate <template <typename,\
    \ typename...> class ContainerType, typename ValueType>\nstd::ostream& operator<<(std::ostream\
    \ &os, const ContainerType<ValueType>& container) {\n    auto it = container.cbegin();\n\
    \    for(; std::next(it) != container.cend(); ++it){\n        os << *it << ' ';\n\
    \    }\n    return os << *it;\n}\n\ntemplate <template <typename, typename...>\
    \ class ContainerType, typename ValueType>\nstd::istream& operator>>(std::istream\
    \ &is, ContainerType<ValueType>& container) {\n    for(auto &x : container) is\
    \ >> x;\n    return is;\n}\n\ntemplate<typename T1, typename T2>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::pair<T1, T2>& p) {\n    os << p.first\
    \ << ' ' << p.second;\n    return os;\n}\ntemplate<typename T1, typename T2>\n\
    std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {\n    is >>\
    \ p.first >> p.second;\n    return is;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, std::queue<T>& q) {\n    int sz = q.size();\n\
    \    while(--sz){\n        os << q.front() << ' ';\n        q.push(q.front());\n\
    \        q.pop();\n    }\n    os << q.front();\n    q.push(q.front());\n    q.pop();\n\
    \    return os;\n}\n\n\n"
  code: "#ifndef IO_SUPPORTER\n#define IO_SUPPORTER\n#include <iostream>\n#include\
    \ <iterator>\n#include <utility>\n#include <queue>\n\ntemplate <template <typename,\
    \ typename...> class ContainerType, typename ValueType>\nstd::ostream& operator<<(std::ostream\
    \ &os, const ContainerType<ValueType>& container) {\n    auto it = container.cbegin();\n\
    \    for(; std::next(it) != container.cend(); ++it){\n        os << *it << ' ';\n\
    \    }\n    return os << *it;\n}\n\ntemplate <template <typename, typename...>\
    \ class ContainerType, typename ValueType>\nstd::istream& operator>>(std::istream\
    \ &is, ContainerType<ValueType>& container) {\n    for(auto &x : container) is\
    \ >> x;\n    return is;\n}\n\ntemplate<typename T1, typename T2>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::pair<T1, T2>& p) {\n    os << p.first\
    \ << ' ' << p.second;\n    return os;\n}\ntemplate<typename T1, typename T2>\n\
    std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {\n    is >>\
    \ p.first >> p.second;\n    return is;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, std::queue<T>& q) {\n    int sz = q.size();\n\
    \    while(--sz){\n        os << q.front() << ' ';\n        q.push(q.front());\n\
    \        q.pop();\n    }\n    os << q.front();\n    q.push(q.front());\n    q.pop();\n\
    \    return os;\n}\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: other/io_supporter.hpp
  requiredBy: []
  timestamp: '2023-06-13 15:49:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/alds1-5-d.test.cpp
documentation_of: other/io_supporter.hpp
layout: document
redirect_from:
- /library/other/io_supporter.hpp
- /library/other/io_supporter.hpp.html
title: other/io_supporter.hpp
---
