---
data:
  _extendedDependsOn:
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
    \n#include <bits/stdc++.h>\n#line 1 \"standard/longest_increasing_subsequence.hpp\"\
    \n\n\n#line 6 \"standard/longest_increasing_subsequence.hpp\"\n#include <type_traits>\n\
    \n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\
    \u9593\u3067\u6307\u5B9A\u3057\u3001\u6700\u9577\u90E8\u5206\u5897\u52A0\u5217\
    \u306E\u306E\u9577\u3055\u3092\u6C42\u3081\u308B\n * @attention \u533A\u9593\u9577\
    \u304C 0 \u306A\u3089\u3070 0\n * @param strict true ? \u72ED\u7FA9\u5897\u52A0\
    \ : \u5E83\u7FA9\u5897\u52A0\n */\ntemplate<typename InputIterator>\nint longest_increasing_subsequence(const\
    \ InputIterator &__begin, const InputIterator &__end, bool strict = false) {\n\
    \    std::vector<typename std::iterator_traits<InputIterator>::value_type> dp;\n\
    \    auto dp_it = dp.begin();\n    for(auto arg_it = __begin; arg_it != __end;\
    \ ++arg_it){  \n        if(strict) dp_it = std::lower_bound(dp.begin(), dp.end(),\
    \ *arg_it);\n        else dp_it = std::upper_bound(dp.begin(), dp.end(), *arg_it);\n\
    \        if(dp_it != dp.end()) *dp_it = *arg_it;\n        else dp.push_back(*arg_it);\n\
    \    }\n    return dp.size();\n}\n\n\n#line 4 \"test/dpl-1-d.test.cpp\"\nusing\
    \ namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j);\
    \ i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\nint main(void){\n \n\
    \    //input\n \n    int N;\n    cin >> N;\n    vector<int> A(N);\n    rep(i,0,N)\
    \ cin >> A[i];\n\n    //calculate\n \n    cout << longest_increasing_subsequence(all(A),\
    \ true) << endl;\n \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D\"\n#include\
    \ <bits/stdc++.h>\n#include \"../standard/longest_increasing_subsequence.hpp\"\
    \nusing namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i =\
    \ (ll)(j); i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\nint main(void){\n\
    \ \n    //input\n \n    int N;\n    cin >> N;\n    vector<int> A(N);\n    rep(i,0,N)\
    \ cin >> A[i];\n\n    //calculate\n \n    cout << longest_increasing_subsequence(all(A),\
    \ true) << endl;\n \n}"
  dependsOn:
  - standard/longest_increasing_subsequence.hpp
  isVerificationFile: true
  path: test/dpl-1-d.test.cpp
  requiredBy: []
  timestamp: '2023-06-10 01:20:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dpl-1-d.test.cpp
layout: document
redirect_from:
- /verify/test/dpl-1-d.test.cpp
- /verify/test/dpl-1-d.test.cpp.html
title: test/dpl-1-d.test.cpp
---