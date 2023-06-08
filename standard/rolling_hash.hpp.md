---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7318906#1
  bundledCode: "#line 1 \"standard/rolling_hash.hpp\"\n#include <string>\n#include\
    \ <vector>\n\n// verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7318906#1\n\
    \nclass rolling_hash{\n  private:\n    const int len;\n\tconst __uint128_t _base\
    \ = 10007, _mod = ((__uint128_t)1<<61) - 1;\n\tstd::vector<__uint128_t> hashes,\
    \ bases; \n\n  public:\n\trolling_hash(const std::string &s) : len(s.size()),\
    \ hashes(len + 1, 0), bases(len + 1, 0)  {\n\t\tbases[0] = 1;\n\t\tfor(int i =\
    \ 0; i < len; i++){\n\t\t\thashes[i + 1] = (hashes[i] * _base + s[i]) % _mod;\n\
    \t\t\tbases[i + 1] = (bases[i] * _base) % _mod;\n\t\t}\n\t}\n\n\t/* s[l, r) \u306E\
    \u30CF\u30C3\u30B7\u30E5\u5024\u3092\u8A08\u7B97\n     * O(1)\n     */\n\t__uint128_t\
    \ get(int l, int r){\n\t\treturn (hashes[r] + _mod - (hashes[l] * bases[r-l])\
    \ % _mod) % _mod;\n\t}\n\n    __uint128_t get(int l1, int r1, int l2, int r2){\n\
    \        __uint128_t hsh1 = get(l1, r1), hsh2 = get(l2, r2);\n        return (hsh1\
    \ * bases[r2 - l2] + hsh2) % _mod;\n\t}\n\n\n    /* s[l1, r1), s[l2, r2) \u306E\
    \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\n     * O(logN)\n     */\n    int longest_common_prefix(int\
    \ l1, int r1, int l2, int r2){\n        // [ok, ng)\n        int ok = 0, ng =\
    \ std::min(r1 - l1, r2 - l2) + 1;\n        while(abs(ok - ng) > 1){\n        \
    \    int mid = (ok + ng) / 2;\n            if(get(l1, l1 + mid) == get(l2, l2\
    \ + mid)) ok = mid;\n            else ng = mid;\n        }\n        return ok;\n\
    \    }\n\n};\n"
  code: "#include <string>\n#include <vector>\n\n// verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7318906#1\n\
    \nclass rolling_hash{\n  private:\n    const int len;\n\tconst __uint128_t _base\
    \ = 10007, _mod = ((__uint128_t)1<<61) - 1;\n\tstd::vector<__uint128_t> hashes,\
    \ bases; \n\n  public:\n\trolling_hash(const std::string &s) : len(s.size()),\
    \ hashes(len + 1, 0), bases(len + 1, 0)  {\n\t\tbases[0] = 1;\n\t\tfor(int i =\
    \ 0; i < len; i++){\n\t\t\thashes[i + 1] = (hashes[i] * _base + s[i]) % _mod;\n\
    \t\t\tbases[i + 1] = (bases[i] * _base) % _mod;\n\t\t}\n\t}\n\n\t/* s[l, r) \u306E\
    \u30CF\u30C3\u30B7\u30E5\u5024\u3092\u8A08\u7B97\n     * O(1)\n     */\n\t__uint128_t\
    \ get(int l, int r){\n\t\treturn (hashes[r] + _mod - (hashes[l] * bases[r-l])\
    \ % _mod) % _mod;\n\t}\n\n    __uint128_t get(int l1, int r1, int l2, int r2){\n\
    \        __uint128_t hsh1 = get(l1, r1), hsh2 = get(l2, r2);\n        return (hsh1\
    \ * bases[r2 - l2] + hsh2) % _mod;\n\t}\n\n\n    /* s[l1, r1), s[l2, r2) \u306E\
    \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\n     * O(logN)\n     */\n    int longest_common_prefix(int\
    \ l1, int r1, int l2, int r2){\n        // [ok, ng)\n        int ok = 0, ng =\
    \ std::min(r1 - l1, r2 - l2) + 1;\n        while(abs(ok - ng) > 1){\n        \
    \    int mid = (ok + ng) / 2;\n            if(get(l1, l1 + mid) == get(l2, l2\
    \ + mid)) ok = mid;\n            else ng = mid;\n        }\n        return ok;\n\
    \    }\n\n};"
  dependsOn: []
  isVerificationFile: false
  path: standard/rolling_hash.hpp
  requiredBy: []
  timestamp: '2023-04-12 00:32:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/rolling_hash.hpp
layout: document
redirect_from:
- /library/standard/rolling_hash.hpp
- /library/standard/rolling_hash.hpp.html
title: standard/rolling_hash.hpp
---
