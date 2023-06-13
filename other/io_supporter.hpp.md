---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/alds1-5-d.test.cpp
    title: test/alds1-5-d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dpl-1-d.test.cpp
    title: test/dpl-1-d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/io_supporter.hpp\"\n\n\n#include <iostream>\n#include\
    \ <utility>\n#include <queue>\n#include <string>\n\ntemplate <template <typename,\
    \ typename...> class ContainerType, typename ValueType>\nstd::ostream& operator<<(std::ostream\
    \ &os, const ContainerType<ValueType>& container) {\n    auto it = container.cbegin();\n\
    \    if(it == container.end()) return os;\n    os << *it;\n    while(++it != container.cend())\
    \ os << ' ' << *it;\n    return os;\n}\n\ntemplate <template <typename, typename...>\
    \ class ContainerType, typename ValueType>\nstd::istream& operator>>(std::istream\
    \ &is, ContainerType<ValueType>& container) {\n    for(auto &x : container) is\
    \ >> x;\n    return is;\n}\n\nstd::ostream& operator<<(std::ostream &os, const\
    \ std::string& s) {\n    std::operator<<(os, s);\n    return os;\n}\n\nstd::istream&\
    \ operator>>(std::istream &is, std::string& s) {\n    std::operator>>(is, s);\n\
    \    return is;\n}\n\ntemplate<typename T1, typename T2>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T1, T2>& p) {\n    os << p.first << ' ' << p.second;\n\
    \    return os;\n}\ntemplate<typename T1, typename T2>\nstd::istream &operator>>(std::istream\
    \ &is, std::pair<T1, T2> &p) {\n    is >> p.first >> p.second;\n    return is;\n\
    }\n\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T>&\
    \ q) {\n    int sz = q.size();\n    while(--sz){\n        os << q.front() << '\
    \ ';\n        q.push(q.front());\n        q.pop();\n    }\n    os << q.front();\n\
    \    q.push(q.front());\n    q.pop();\n    return os;\n}\n\n\n"
  code: "#ifndef IO_SUPPORTER\n#define IO_SUPPORTER\n#include <iostream>\n#include\
    \ <utility>\n#include <queue>\n#include <string>\n\ntemplate <template <typename,\
    \ typename...> class ContainerType, typename ValueType>\nstd::ostream& operator<<(std::ostream\
    \ &os, const ContainerType<ValueType>& container) {\n    auto it = container.cbegin();\n\
    \    if(it == container.end()) return os;\n    os << *it;\n    while(++it != container.cend())\
    \ os << ' ' << *it;\n    return os;\n}\n\ntemplate <template <typename, typename...>\
    \ class ContainerType, typename ValueType>\nstd::istream& operator>>(std::istream\
    \ &is, ContainerType<ValueType>& container) {\n    for(auto &x : container) is\
    \ >> x;\n    return is;\n}\n\nstd::ostream& operator<<(std::ostream &os, const\
    \ std::string& s) {\n    std::operator<<(os, s);\n    return os;\n}\n\nstd::istream&\
    \ operator>>(std::istream &is, std::string& s) {\n    std::operator>>(is, s);\n\
    \    return is;\n}\n\ntemplate<typename T1, typename T2>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T1, T2>& p) {\n    os << p.first << ' ' << p.second;\n\
    \    return os;\n}\ntemplate<typename T1, typename T2>\nstd::istream &operator>>(std::istream\
    \ &is, std::pair<T1, T2> &p) {\n    is >> p.first >> p.second;\n    return is;\n\
    }\n\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T>&\
    \ q) {\n    int sz = q.size();\n    while(--sz){\n        os << q.front() << '\
    \ ';\n        q.push(q.front());\n        q.pop();\n    }\n    os << q.front();\n\
    \    q.push(q.front());\n    q.pop();\n    return os;\n}\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: other/io_supporter.hpp
  requiredBy: []
  timestamp: '2023-06-13 22:45:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dpl-1-d.test.cpp
  - test/alds1-5-d.test.cpp
documentation_of: other/io_supporter.hpp
layout: document
redirect_from:
- /library/other/io_supporter.hpp
- /library/other/io_supporter.hpp.html
title: other/io_supporter.hpp
---
