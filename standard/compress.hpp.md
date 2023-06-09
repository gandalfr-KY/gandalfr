---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: standard/inversion.hpp
    title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\
      \u3067\u6307\u5B9A\u3057\u3001\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/alds1-5-d.test.cpp
    title: test/alds1-5-d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\
      \u9593\u3067\u6307\u5B9A\u3057\u3001\u5EA7\u6A19\u5727\u7E2E\u3059\u308B"
    links: []
  bundledCode: "#line 1 \"standard/compress.hpp\"\n\n\n#include <algorithm>\n#include\
    \ <iterator>\n#include <type_traits>\n\n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\
    \u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\u3067\u6307\u5B9A\u3057\u3001\
    \u5EA7\u6A19\u5727\u7E2E\u3059\u308B\n * @param __begin \u5EA7\u5727\u3059\u308B\
    \u5DE6\u7AEF\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @param __end \u53F3\u7AEF\
    \u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @attention 0 \u306F\u3058\u307E\u308A\
    \u3067\u5727\u7E2E\u3059\u308B\u3002\n */\ntemplate<typename InputIterator>\n\
    std::vector<int> compress(const InputIterator &__begin,  const InputIterator &__end){\n\
    \    std::vector<int> ret;\n    ret.reserve(std::distance(__begin, __end));\n\
    \    std::vector<typename std::iterator_traits<InputIterator>::value_type> w(__begin,\
    \ __end);\n    std::sort(w.begin(), w.end());\n    w.erase(std::unique(w.begin(),\
    \ w.end()), w.end());\n    for(auto it = __begin; it != __end; it++)\n       \
    \ ret.push_back(std::lower_bound(w.begin(), w.end(), *it) - w.begin());\n    return\
    \ ret;\n}\n\n\n"
  code: "#ifndef COMPRESS\n#define COMPRESS\n#include <algorithm>\n#include <iterator>\n\
    #include <type_traits>\n\n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\
    \u3092\u534A\u958B\u533A\u9593\u3067\u6307\u5B9A\u3057\u3001\u5EA7\u6A19\u5727\
    \u7E2E\u3059\u308B\n * @param __begin \u5EA7\u5727\u3059\u308B\u5DE6\u7AEF\u306E\
    \u30A4\u30C6\u30EC\u30FC\u30BF\n * @param __end \u53F3\u7AEF\u306E\u30A4\u30C6\
    \u30EC\u30FC\u30BF\n * @attention 0 \u306F\u3058\u307E\u308A\u3067\u5727\u7E2E\
    \u3059\u308B\u3002\n */\ntemplate<typename InputIterator>\nstd::vector<int> compress(const\
    \ InputIterator &__begin,  const InputIterator &__end){\n    std::vector<int>\
    \ ret;\n    ret.reserve(std::distance(__begin, __end));\n    std::vector<typename\
    \ std::iterator_traits<InputIterator>::value_type> w(__begin, __end);\n    std::sort(w.begin(),\
    \ w.end());\n    w.erase(std::unique(w.begin(), w.end()), w.end());\n    for(auto\
    \ it = __begin; it != __end; it++)\n        ret.push_back(std::lower_bound(w.begin(),\
    \ w.end(), *it) - w.begin());\n    return ret;\n}\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: standard/compress.hpp
  requiredBy:
  - standard/inversion.hpp
  timestamp: '2023-06-09 12:40:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/alds1-5-d.test.cpp
documentation_of: standard/compress.hpp
layout: document
redirect_from:
- /library/standard/compress.hpp
- /library/standard/compress.hpp.html
title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\u3067\
  \u6307\u5B9A\u3057\u3001\u5EA7\u6A19\u5727\u7E2E\u3059\u308B"
---
