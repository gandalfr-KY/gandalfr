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
    \ <utility>\n#include <queue>\n#include <deque>\n#include <string>\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {\n\
    \    for(int i=0; i<(int)v.size(); i++) os << v[i] << (i+1 != (int)v.size() ?\
    \ \" \" : \"\");\n    return os;\n}\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::set<T> &st) {\n    for(const T &x : st){\n        std::cout\
    \ << x << \" \";\n    }\n    return os;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::multiset<T> &st) {\n    for(const T\
    \ &x : st){\n        std::cout << x << \" \";\n    }\n    return os;\n}\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::deque<T> &dq) {\n\
    \    for(const T &x : dq){\n        std::cout << x << \" \";\n    }\n    return\
    \ os;\n}\ntemplate<typename T1, typename T2>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T1, T2>& p) {\n    os << p.first << ' ' << p.second;\n\
    \    return os;\n}\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, std::queue<T>& q) {\n    int sz = q.size();\n    while(--sz){\n       \
    \ os << q.front() << ' ';\n        q.push(q.front());\n        q.pop();\n    }\n\
    \    os << q.front();\n    q.push(q.front());\n    q.pop();\n    return os;\n\
    }\n\ntemplate<typename T>\nstd::istream &operator>>(std::istream &is, std::vector<T>\
    \ &v){\n    for(T &in : v) is >> in;\n    return is;\n}\ntemplate<typename T1,\
    \ typename T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2> &p)\
    \ {\n    is >> p.first >> p.second;\n    return is;\n}\n\n\n\n"
  code: "#ifndef IO_SUPPORTER\n#define IO_SUPPORTER\n#include <iostream>\n#include\
    \ <utility>\n#include <queue>\n#include <deque>\n#include <string>\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {\n\
    \    for(int i=0; i<(int)v.size(); i++) os << v[i] << (i+1 != (int)v.size() ?\
    \ \" \" : \"\");\n    return os;\n}\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::set<T> &st) {\n    for(const T &x : st){\n        std::cout\
    \ << x << \" \";\n    }\n    return os;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::multiset<T> &st) {\n    for(const T\
    \ &x : st){\n        std::cout << x << \" \";\n    }\n    return os;\n}\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::deque<T> &dq) {\n\
    \    for(const T &x : dq){\n        std::cout << x << \" \";\n    }\n    return\
    \ os;\n}\ntemplate<typename T1, typename T2>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T1, T2>& p) {\n    os << p.first << ' ' << p.second;\n\
    \    return os;\n}\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, std::queue<T>& q) {\n    int sz = q.size();\n    while(--sz){\n       \
    \ os << q.front() << ' ';\n        q.push(q.front());\n        q.pop();\n    }\n\
    \    os << q.front();\n    q.push(q.front());\n    q.pop();\n    return os;\n\
    }\n\ntemplate<typename T>\nstd::istream &operator>>(std::istream &is, std::vector<T>\
    \ &v){\n    for(T &in : v) is >> in;\n    return is;\n}\ntemplate<typename T1,\
    \ typename T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2> &p)\
    \ {\n    is >> p.first >> p.second;\n    return is;\n}\n\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: other/io_supporter.hpp
  requiredBy: []
  timestamp: '2023-06-15 14:58:26+09:00'
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
