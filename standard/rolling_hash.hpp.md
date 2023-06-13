---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/alds1-14-b.test.cpp
    title: test/alds1-14-b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\
      \u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9"
    links: []
  bundledCode: "#line 1 \"standard/rolling_hash.hpp\"\n\n\n#include <string>\n#include\
    \ <vector>\n#include <random>\n\n/**\n * @brief rolling_hash\u30A2\u30EB\u30B4\
    \u30EA\u30BA\u30E0\u3067\u6587\u5B57\u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\
    \u30E9\u30B9\n */\nclass rolling_hash{\nprivate:\n    static inline unsigned long\
    \ long _base = 0;\n    static inline const unsigned long long _mod = (1LL<<61)\
    \ - 1;\n\tstd::vector<unsigned long long> hashes, bases;\n    static inline const\
    \ std::vector<unsigned long long> base_list{\n        1809535154732661841LL,\n\
    \        1884190988654199289LL,\n        1743269039721525290LL,\n        443670500607027996LL,\n\
    \        1847920912542467715LL,\n        854073078368186965LL,\n        1223509603385983965LL,\n\
    \        1417510665238831134LL,\n        1078954822254450931LL,\n        544731273123194097LL,\n\
    \        628194563995444860LL,\n        2068028567818163032LL,\n        382415649034687899LL,\n\
    \        1278119205153488676LL,\n        1191116173253440671LL,\n        1896252179888216214LL,\n\
    \        1559071116560504239LL,\n        924438638735228819LL,\n        1857807495571573189LL,\n\
    \        307827764609342932LL,\n        152462581942784977LL\n    };\n\npublic:\n\
    \trolling_hash(const std::string &s) : hashes(s.size() + 1, 0), bases(s.size()\
    \ + 1, 0) {\n        if(_base == 0) {\n            std::random_device rd;\n  \
    \          std::mt19937 gen(rd());\n            std::uniform_int_distribution<>\
    \ distr(0, base_list.size() - 1);\n            _base = base_list[distr(gen)];\n\
    \        }\n\t\tbases[0] = 1;\n\t\tfor(int i = 0; i < (int)s.size(); i++){\n\t\
    \t\thashes[i + 1] = ((__uint128_t)hashes[i] * _base + s[i]) % _mod;\n\t\t\tbases[i\
    \ + 1] = ((__uint128_t)bases[i] * _base) % _mod;\n\t\t}\n\t}\n\n\t/**\n     *\
    \ @brief \u534A\u958B\u533A\u9593\u3092\u6307\u5B9A\n     * @return string[l,\
    \ r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n     */\n\tunsigned long long get(int\
    \ l, int r){\n\t\treturn (hashes[r] + _mod - ((__uint128_t)hashes[l] * bases[r\
    \ - l]) % _mod) % _mod;\n\t}\n\n\t/**\n     * @brief \u6587\u5B57\u5217\u3092\u7D50\
    \u5408\u3057\u3066\u30CF\u30C3\u30B7\u30E5\u5024\u3092\u8A08\u7B97\n     * @return\
    \ get(_l, _r) == r_hash \u306A\u308B string[_l, _r) \u306B\u5BFE\u3057\u3066\u3001\
    [_l, _r) + [l, r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n     */\n    unsigned\
    \ long long concat(__uint128_t r_hash, int l, int r){\n        return ((__uint128_t)r_hash\
    \ * bases[r - l] + get(l, r)) % _mod;\n\t}\n\n    /**\n     * @return string[l1,\
    \ r1), string[l2, r2) \u306E\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\
    \u3055\n     */\n    int longest_common_prefix(int l1, int r1, int l2, int r2){\n\
    \        int ok = 0, ng = std::min(r1 - l1, r2 - l2) + 1;\n        while(std::abs(ok\
    \ - ng) > 1){\n            int mid = (ok + ng) / 2;\n            if(get(l1, l1\
    \ + mid) == get(l2, l2 + mid)) ok = mid;\n            else ng = mid;\n       \
    \ }\n        return ok;\n    }\n};\n\n\n"
  code: "#ifndef ROLLING_HASH\n#define ROLLING_HASH\n#include <string>\n#include <vector>\n\
    #include <random>\n\n/**\n * @brief rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\
    \u30E0\u3067\u6587\u5B57\u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\
    \n */\nclass rolling_hash{\nprivate:\n    static inline unsigned long long _base\
    \ = 0;\n    static inline const unsigned long long _mod = (1LL<<61) - 1;\n\tstd::vector<unsigned\
    \ long long> hashes, bases;\n    static inline const std::vector<unsigned long\
    \ long> base_list{\n        1809535154732661841LL,\n        1884190988654199289LL,\n\
    \        1743269039721525290LL,\n        443670500607027996LL,\n        1847920912542467715LL,\n\
    \        854073078368186965LL,\n        1223509603385983965LL,\n        1417510665238831134LL,\n\
    \        1078954822254450931LL,\n        544731273123194097LL,\n        628194563995444860LL,\n\
    \        2068028567818163032LL,\n        382415649034687899LL,\n        1278119205153488676LL,\n\
    \        1191116173253440671LL,\n        1896252179888216214LL,\n        1559071116560504239LL,\n\
    \        924438638735228819LL,\n        1857807495571573189LL,\n        307827764609342932LL,\n\
    \        152462581942784977LL\n    };\n\npublic:\n\trolling_hash(const std::string\
    \ &s) : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {\n        if(_base ==\
    \ 0) {\n            std::random_device rd;\n            std::mt19937 gen(rd());\n\
    \            std::uniform_int_distribution<> distr(0, base_list.size() - 1);\n\
    \            _base = base_list[distr(gen)];\n        }\n\t\tbases[0] = 1;\n\t\t\
    for(int i = 0; i < (int)s.size(); i++){\n\t\t\thashes[i + 1] = ((__uint128_t)hashes[i]\
    \ * _base + s[i]) % _mod;\n\t\t\tbases[i + 1] = ((__uint128_t)bases[i] * _base)\
    \ % _mod;\n\t\t}\n\t}\n\n\t/**\n     * @brief \u534A\u958B\u533A\u9593\u3092\u6307\
    \u5B9A\n     * @return string[l, r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n   \
    \  */\n\tunsigned long long get(int l, int r){\n\t\treturn (hashes[r] + _mod -\
    \ ((__uint128_t)hashes[l] * bases[r - l]) % _mod) % _mod;\n\t}\n\n\t/**\n    \
    \ * @brief \u6587\u5B57\u5217\u3092\u7D50\u5408\u3057\u3066\u30CF\u30C3\u30B7\u30E5\
    \u5024\u3092\u8A08\u7B97\n     * @return get(_l, _r) == r_hash \u306A\u308B string[_l,\
    \ _r) \u306B\u5BFE\u3057\u3066\u3001[_l, _r) + [l, r) \u306E\u30CF\u30C3\u30B7\
    \u30E5\u5024\n     */\n    unsigned long long concat(__uint128_t r_hash, int l,\
    \ int r){\n        return ((__uint128_t)r_hash * bases[r - l] + get(l, r)) % _mod;\n\
    \t}\n\n    /**\n     * @return string[l1, r1), string[l2, r2) \u306E\u6700\u9577\
    \u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n     */\n    int longest_common_prefix(int\
    \ l1, int r1, int l2, int r2){\n        int ok = 0, ng = std::min(r1 - l1, r2\
    \ - l2) + 1;\n        while(std::abs(ok - ng) > 1){\n            int mid = (ok\
    \ + ng) / 2;\n            if(get(l1, l1 + mid) == get(l2, l2 + mid)) ok = mid;\n\
    \            else ng = mid;\n        }\n        return ok;\n    }\n};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: standard/rolling_hash.hpp
  requiredBy: []
  timestamp: '2023-06-13 14:42:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/alds1-14-b.test.cpp
documentation_of: standard/rolling_hash.hpp
layout: document
redirect_from:
- /library/standard/rolling_hash.hpp
- /library/standard/rolling_hash.hpp.html
title: "rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\u5217\u3092\
  \u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9"
---
