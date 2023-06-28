---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/abc284-f.test.cpp
    title: test/abc284-f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/alds1-14-b.test.cpp
    title: test/alds1-14-b.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\
      \u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
    links: []
  bundledCode: "#line 2 \"standard/rolling_hash.hpp\"\n#include <random>\n#include\
    \ <string>\n#include <vector>\n\n/**\n * @brief rolling_hash\u30A2\u30EB\u30B4\
    \u30EA\u30BA\u30E0\u3067\u6587\u5B57\u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\
    \u30E9\u30B9\u3002\n * @attention \u8907\u6570\u306E\u30A4\u30F3\u30B9\u30BF\u30F3\
    \u30B9\u3092\u751F\u6210\u3057\u3066\u3082\u3001\u57FA\u6570\u306F\u5171\u6709\
    \u3055\u308C\u308B\u3002\n */\nclass rolling_hash {\n  private:\n    static inline\
    \ unsigned long long _base = 0;\n    static inline const unsigned long long _mod\
    \ = (1LL << 61) - 1;\n    std::vector<unsigned long long> hashes, bases;\n   \
    \ static inline const std::vector<unsigned long long> base_list{\n        1809535154732661841LL,\
    \ 1884190988654199289LL, 1743269039721525290LL,\n        443670500607027996LL,\
    \  1847920912542467715LL, 854073078368186965LL,\n        1223509603385983965LL,\
    \ 1417510665238831134LL, 1078954822254450931LL,\n        544731273123194097LL,\
    \  628194563995444860LL,  2068028567818163032LL,\n        382415649034687899LL,\
    \  1278119205153488676LL, 1191116173253440671LL,\n        1896252179888216214LL,\
    \ 1559071116560504239LL, 924438638735228819LL,\n        1857807495571573189LL,\
    \ 307827764609342932LL,  152462581942784977LL};\n\n  public:\n    rolling_hash(const\
    \ std::string &s)\n        : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {\n\
    \        if (_base == 0) {\n            std::random_device rd;\n            std::mt19937\
    \ gen(rd());\n            std::uniform_int_distribution<> distr(0, base_list.size()\
    \ - 1);\n            _base = base_list[distr(gen)];\n        }\n        bases[0]\
    \ = 1;\n        for (int i = 0; i < (int)s.size(); i++) {\n            hashes[i\
    \ + 1] = ((__uint128_t)hashes[i] * _base + s[i]) % _mod;\n            bases[i\
    \ + 1] = ((__uint128_t)bases[i] * _base) % _mod;\n        }\n    }\n\n    /**\n\
    \     * @brief \u534A\u958B\u533A\u9593\u3092\u6307\u5B9A\n     * @return string[l,\
    \ r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n     */\n    unsigned long long get(int\
    \ l, int r) {\n        return (hashes[r] + _mod -\n                ((__uint128_t)hashes[l]\
    \ * bases[r - l]) % _mod) %\n               _mod;\n    }\n\n    /**\n     * @brief\
    \ r_hash == get(_l, _r) \u306A\u308B\u30CF\u30C3\u30B7\u30E5\u5024\u3092\u3001\
    string([_l, _r) + [l, r))\n     * \u306E\u30CF\u30C3\u30B7\u30E5\u5024\u306B\u66F4\
    \u65B0\u3002\n     */\n    void concat(unsigned long long &r_hash, int l, int\
    \ r) {\n        r_hash = ((__uint128_t)r_hash * bases[r - l] + get(l, r)) % _mod;\n\
    \    }\n\n    /**\n     * @return string[l1, r1), string[l2, r2) \u306E\u6700\u9577\
    \u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n     */\n    int longest_common_prefix(int\
    \ l1, int r1, int l2, int r2) {\n        int ok = 0, ng = std::min(r1 - l1, r2\
    \ - l2) + 1;\n        while (std::abs(ok - ng) > 1) {\n            int mid = (ok\
    \ + ng) / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 + mid))\n      \
    \          ok = mid;\n            else\n                ng = mid;\n        }\n\
    \        return ok;\n    }\n};\n"
  code: "#pragma once\n#include <random>\n#include <string>\n#include <vector>\n\n\
    /**\n * @brief rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\
    \u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002\n * @attention \u8907\
    \u6570\u306E\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\u3092\u751F\u6210\u3057\u3066\
    \u3082\u3001\u57FA\u6570\u306F\u5171\u6709\u3055\u308C\u308B\u3002\n */\nclass\
    \ rolling_hash {\n  private:\n    static inline unsigned long long _base = 0;\n\
    \    static inline const unsigned long long _mod = (1LL << 61) - 1;\n    std::vector<unsigned\
    \ long long> hashes, bases;\n    static inline const std::vector<unsigned long\
    \ long> base_list{\n        1809535154732661841LL, 1884190988654199289LL, 1743269039721525290LL,\n\
    \        443670500607027996LL,  1847920912542467715LL, 854073078368186965LL,\n\
    \        1223509603385983965LL, 1417510665238831134LL, 1078954822254450931LL,\n\
    \        544731273123194097LL,  628194563995444860LL,  2068028567818163032LL,\n\
    \        382415649034687899LL,  1278119205153488676LL, 1191116173253440671LL,\n\
    \        1896252179888216214LL, 1559071116560504239LL, 924438638735228819LL,\n\
    \        1857807495571573189LL, 307827764609342932LL,  152462581942784977LL};\n\
    \n  public:\n    rolling_hash(const std::string &s)\n        : hashes(s.size()\
    \ + 1, 0), bases(s.size() + 1, 0) {\n        if (_base == 0) {\n            std::random_device\
    \ rd;\n            std::mt19937 gen(rd());\n            std::uniform_int_distribution<>\
    \ distr(0, base_list.size() - 1);\n            _base = base_list[distr(gen)];\n\
    \        }\n        bases[0] = 1;\n        for (int i = 0; i < (int)s.size();\
    \ i++) {\n            hashes[i + 1] = ((__uint128_t)hashes[i] * _base + s[i])\
    \ % _mod;\n            bases[i + 1] = ((__uint128_t)bases[i] * _base) % _mod;\n\
    \        }\n    }\n\n    /**\n     * @brief \u534A\u958B\u533A\u9593\u3092\u6307\
    \u5B9A\n     * @return string[l, r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n   \
    \  */\n    unsigned long long get(int l, int r) {\n        return (hashes[r] +\
    \ _mod -\n                ((__uint128_t)hashes[l] * bases[r - l]) % _mod) %\n\
    \               _mod;\n    }\n\n    /**\n     * @brief r_hash == get(_l, _r) \u306A\
    \u308B\u30CF\u30C3\u30B7\u30E5\u5024\u3092\u3001string([_l, _r) + [l, r))\n  \
    \   * \u306E\u30CF\u30C3\u30B7\u30E5\u5024\u306B\u66F4\u65B0\u3002\n     */\n\
    \    void concat(unsigned long long &r_hash, int l, int r) {\n        r_hash =\
    \ ((__uint128_t)r_hash * bases[r - l] + get(l, r)) % _mod;\n    }\n\n    /**\n\
    \     * @return string[l1, r1), string[l2, r2) \u306E\u6700\u9577\u5171\u901A\u63A5\
    \u982D\u8F9E\u306E\u9577\u3055\n     */\n    int longest_common_prefix(int l1,\
    \ int r1, int l2, int r2) {\n        int ok = 0, ng = std::min(r1 - l1, r2 - l2)\
    \ + 1;\n        while (std::abs(ok - ng) > 1) {\n            int mid = (ok + ng)\
    \ / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 + mid))\n            \
    \    ok = mid;\n            else\n                ng = mid;\n        }\n     \
    \   return ok;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/rolling_hash.hpp
  requiredBy: []
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/alds1-14-b.test.cpp
  - test/abc284-f.test.cpp
documentation_of: standard/rolling_hash.hpp
layout: document
redirect_from:
- /library/standard/rolling_hash.hpp
- /library/standard/rolling_hash.hpp.html
title: "rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\u5217\u3092\
  \u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
---
