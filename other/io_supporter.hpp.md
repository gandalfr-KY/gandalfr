---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/alds1-5-d.test.cpp
    title: test/alds1-5-d.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/io_supporter.hpp\"\n\n\n#include <iostream>\n#include\
    \ <vector>\n#include <utility>\n#include <queue>\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::vector<T> &v) {\n    for(int i=0; i<(int)v.size();\
    \ i++) os << v[i] << (i+1 != (int)v.size() ? \" \" : \"\");\n    return os;\n\
    }\ntemplate<typename T>\nstd::istream &operator>>(std::istream &is, std::vector<T>\
    \ &v){\n    for(T &in : v) is >> in;\n    return is;\n}\n\ntemplate<typename T1,\
    \ typename T2>\nstd::ostream &operator<<(std::ostream &os, const std::pair<T1,\
    \ T2>& p) {\n    os << p.first << \" \" << p.second;\n    return os;\n}\ntemplate<typename\
    \ T1, typename T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2>\
    \ &p) {\n    is >> p.first >> p.second;\n    return is;\n}\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T> v) {\n    int N\
    \ = v.size();\n    for(int i=0; i<N; i++) {\n        os << v.front() << (i+1 !=\
    \ N ? \" \" : \"\");\n        v.pop();\n    }\n    return os;\n}\ntemplate<typename\
    \ T>\nstd::istream &operator>>(std::istream &is, std::queue<T> &v) {\n    for(T\
    \ &in : is) v.push(is);\n    return is;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::set<T> &st) {\n    for(const T &x :\
    \ st){\n        std::cout << x << \" \";\n    }\n    return os;\n}\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {\n\
    \    for(const T &x : st){\n        std::cout << x << \" \";\n    }\n    return\
    \ os;\n}\n\n\n\n"
  code: "#ifndef IO_SUPPORTER\n#define IO_SUPPORTER\n#include <iostream>\n#include\
    \ <vector>\n#include <utility>\n#include <queue>\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::vector<T> &v) {\n    for(int i=0; i<(int)v.size();\
    \ i++) os << v[i] << (i+1 != (int)v.size() ? \" \" : \"\");\n    return os;\n\
    }\ntemplate<typename T>\nstd::istream &operator>>(std::istream &is, std::vector<T>\
    \ &v){\n    for(T &in : v) is >> in;\n    return is;\n}\n\ntemplate<typename T1,\
    \ typename T2>\nstd::ostream &operator<<(std::ostream &os, const std::pair<T1,\
    \ T2>& p) {\n    os << p.first << \" \" << p.second;\n    return os;\n}\ntemplate<typename\
    \ T1, typename T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2>\
    \ &p) {\n    is >> p.first >> p.second;\n    return is;\n}\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T> v) {\n    int N\
    \ = v.size();\n    for(int i=0; i<N; i++) {\n        os << v.front() << (i+1 !=\
    \ N ? \" \" : \"\");\n        v.pop();\n    }\n    return os;\n}\ntemplate<typename\
    \ T>\nstd::istream &operator>>(std::istream &is, std::queue<T> &v) {\n    for(T\
    \ &in : is) v.push(is);\n    return is;\n}\n\ntemplate<typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::set<T> &st) {\n    for(const T &x :\
    \ st){\n        std::cout << x << \" \";\n    }\n    return os;\n}\n\ntemplate<typename\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {\n\
    \    for(const T &x : st){\n        std::cout << x << \" \";\n    }\n    return\
    \ os;\n}\n\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: other/io_supporter.hpp
  requiredBy: []
  timestamp: '2023-05-17 17:02:34+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/alds1-5-d.test.cpp
documentation_of: other/io_supporter.hpp
layout: document
redirect_from:
- /library/other/io_supporter.hpp
- /library/other/io_supporter.hpp.html
title: other/io_supporter.hpp
---
