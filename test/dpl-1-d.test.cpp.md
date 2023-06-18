---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/io_supporter.hpp
    title: other/io_supporter.hpp
  - icon: ':heavy_check_mark:'
    path: standard/longest_increasing_subsequence.hpp
    title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\
      \u3067\u6307\u5B9A\u3057\u3001\u6700\u9577\u90E8\u5206\u5897\u52A0\u5217\u306E\
      \u306E\u9577\u3055\u3092\u6C42\u3081\u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D
  bundledCode: "#line 1 \"test/dpl-1-d.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D\"\
    \n#include <bits/stdc++.h>\n#line 4 \"standard/longest_increasing_subsequence.hpp\"\
    \n#include <type_traits>\n#line 6 \"standard/longest_increasing_subsequence.hpp\"\
    \n\n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\
    \u533A\u9593\u3067\u6307\u5B9A\u3057\u3001\u6700\u9577\u90E8\u5206\u5897\u52A0\
    \u5217\u306E\u306E\u9577\u3055\u3092\u6C42\u3081\u308B\n * @attention \u533A\u9593\
    \u9577\u304C 0 \u306A\u3089\u3070 0\n * @param strict true ? \u72ED\u7FA9\u5897\
    \u52A0 : \u5E83\u7FA9\u5897\u52A0\n */\ntemplate <typename InputIterator>\nint\
    \ longest_increasing_subsequence(const InputIterator &__begin,\n             \
    \                      const InputIterator &__end,\n                         \
    \          bool strict = false) {\n    std::vector<typename std::iterator_traits<InputIterator>::value_type>\
    \ dp;\n    auto dp_it = dp.begin();\n    for (auto arg_it = __begin; arg_it !=\
    \ __end; ++arg_it) {\n        if (strict)\n            dp_it = std::lower_bound(dp.begin(),\
    \ dp.end(), *arg_it);\n        else\n            dp_it = std::upper_bound(dp.begin(),\
    \ dp.end(), *arg_it);\n        if (dp_it != dp.end())\n            *dp_it = *arg_it;\n\
    \        else\n            dp.push_back(*arg_it);\n    }\n    return dp.size();\n\
    }\n#line 7 \"other/io_supporter.hpp\"\n\ntemplate <typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::vector<T> &v) {\n    for (int i = 0; i < (int)v.size(); i++)\n\
    \        os << v[i] << (i + 1 != (int)v.size() ? \" \" : \"\");\n    return os;\n\
    }\ntemplate <typename T>\nstd::ostream &operator<<(std::ostream &os, const std::set<T>\
    \ &st) {\n    for (const T &x : st) {\n        std::cout << x << \" \";\n    }\n\
    \    return os;\n}\n\ntemplate <typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::multiset<T> &st) {\n    for (const T &x : st) {\n        std::cout\
    \ << x << \" \";\n    }\n    return os;\n}\ntemplate <typename T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::deque<T> &dq) {\n    for (const T &x\
    \ : dq) {\n        std::cout << x << \" \";\n    }\n    return os;\n}\ntemplate\
    \ <typename T1, typename T2>\nstd::ostream &operator<<(std::ostream &os, const\
    \ std::pair<T1, T2> &p) {\n    os << p.first << ' ' << p.second;\n    return os;\n\
    }\ntemplate <typename T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T>\
    \ &q) {\n    int sz = q.size();\n    while (--sz) {\n        os << q.front() <<\
    \ ' ';\n        q.push(q.front());\n        q.pop();\n    }\n    os << q.front();\n\
    \    q.push(q.front());\n    q.pop();\n    return os;\n}\n\ntemplate <typename\
    \ T>\nstd::istream &operator>>(std::istream &is, std::vector<T> &v) {\n    for\
    \ (T &in : v)\n        is >> in;\n    return is;\n}\ntemplate <typename T1, typename\
    \ T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {\n  \
    \  is >> p.first >> p.second;\n    return is;\n}\n#line 5 \"test/dpl-1-d.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i =\
    \ (ll)(j); i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\nint main(void){\n\
    \ \n    //input\n \n    int N;\n    cin >> N;\n    vector<int> A(N);\n    rep(i,0,N)\
    \ cin >> A[i];\n\n    //calculate\n \n    cout << longest_increasing_subsequence(all(A),\
    \ true) << endl;\n \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D\"\n#include\
    \ <bits/stdc++.h>\n#include \"../standard/longest_increasing_subsequence.hpp\"\
    \n#include \"../other/io_supporter.hpp\"\nusing namespace std;\nusing ll = long\
    \ long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n#define all(a)\
    \ (a).begin(),(a).end()\nint main(void){\n \n    //input\n \n    int N;\n    cin\
    \ >> N;\n    vector<int> A(N);\n    rep(i,0,N) cin >> A[i];\n\n    //calculate\n\
    \ \n    cout << longest_increasing_subsequence(all(A), true) << endl;\n \n}"
  dependsOn:
  - standard/longest_increasing_subsequence.hpp
  - other/io_supporter.hpp
  isVerificationFile: true
  path: test/dpl-1-d.test.cpp
  requiredBy: []
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dpl-1-d.test.cpp
layout: document
redirect_from:
- /verify/test/dpl-1-d.test.cpp
- /verify/test/dpl-1-d.test.cpp.html
title: test/dpl-1-d.test.cpp
---