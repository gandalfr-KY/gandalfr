---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"standard/longest_increasing_subsequence.hpp\"\n\n\n#include\
    \ <vector>\n#include <set>\n#include <algorithm>\n\n/* \u6700\u9577\u90E8\u5206\
    \u5897\u52A0\u5217\u306E\u9577\u3055\u3092\u8FD4\u3059\n * strict == true ? \u72ED\
    \u7FA9\u5897\u52A0 : \u5E83\u7FA9\u5897\u52A0\n */\ntemplate<class T>\nint longest_increasing_subsequence(const\
    \ std::vector<T> &v, bool strict = false){\n    std::vector<T> dp;\n    auto it\
    \ = dp.begin();\n    for(const T &x : v){    \n        if(strict) it = std::lower_bound(dp.begin(),\
    \ dp.end(), x);\n        else it = std::upper_bound(dp.begin(), dp.end(), x);\n\
    \        if(it != dp.end()) *it = x;\n        else dp.push_back(x);\n    }\n \
    \   return dp.size();\n}\n\n\n"
  code: "#ifndef LONGEST_INCREASINNG_SUBSEQUENCE\n#define LONGEST_INCREASINNG_SUBSEQUENCE\n\
    #include <vector>\n#include <set>\n#include <algorithm>\n\n/* \u6700\u9577\u90E8\
    \u5206\u5897\u52A0\u5217\u306E\u9577\u3055\u3092\u8FD4\u3059\n * strict == true\
    \ ? \u72ED\u7FA9\u5897\u52A0 : \u5E83\u7FA9\u5897\u52A0\n */\ntemplate<class T>\n\
    int longest_increasing_subsequence(const std::vector<T> &v, bool strict = false){\n\
    \    std::vector<T> dp;\n    auto it = dp.begin();\n    for(const T &x : v){ \
    \   \n        if(strict) it = std::lower_bound(dp.begin(), dp.end(), x);\n   \
    \     else it = std::upper_bound(dp.begin(), dp.end(), x);\n        if(it != dp.end())\
    \ *it = x;\n        else dp.push_back(x);\n    }\n    return dp.size();\n}\n\n\
    #endif"
  dependsOn: []
  isVerificationFile: false
  path: standard/longest_increasing_subsequence.hpp
  requiredBy: []
  timestamp: '2022-11-02 15:37:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/longest_increasing_subsequence.hpp
layout: document
redirect_from:
- /library/standard/longest_increasing_subsequence.hpp
- /library/standard/longest_increasing_subsequence.hpp.html
title: standard/longest_increasing_subsequence.hpp
---
