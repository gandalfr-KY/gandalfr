---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: standard/rolling_hash.hpp
    title: "rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\u5217\
      \u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "#line 1 \"test/alds1-14-b.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\
    \n#include <bits/stdc++.h>\n#line 1 \"standard/rolling_hash.hpp\"\n\n\n#line 5\
    \ \"standard/rolling_hash.hpp\"\n\n// verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7318906#1\n\
    \n/**\n * @brief rolling_hash\u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u3067\u6587\u5B57\
    \u5217\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\n */\nclass rolling_hash{\n\
    private:\n    const __uint128_t _base = 10007, _mod = ((__uint128_t)1<<61) - 1;\n\
    \tstd::vector<__uint128_t> hashes, bases; \n\npublic:\n\trolling_hash(const std::string\
    \ &s) : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {\n\t\tbases[0] = 1;\n\
    \t\tfor(int i = 0; i < (int)s.size(); i++){\n\t\t\thashes[i + 1] = (hashes[i]\
    \ * _base + s[i]) % _mod;\n\t\t\tbases[i + 1] = (bases[i] * _base) % _mod;\n\t\
    \t}\n\t}\n\n\t/**\n     * @brief \u534A\u958B\u533A\u9593\u3092\u6307\u5B9A\n\
    \     * @return string[l, r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n     */\n\t\
    __uint128_t get(int l, int r){\n\t\treturn (hashes[r] + _mod - (hashes[l] * bases[r\
    \ - l]) % _mod) % _mod;\n\t}\n\n\t/**\n     * @brief \u6587\u5B57\u5217\u3092\u7D50\
    \u5408\u3057\u3066\u30CF\u30C3\u30B7\u30E5\u5024\u3092\u8A08\u7B97\n     * @return\
    \ get(_l, _r) == r_hash \u306A\u308B string[_l, _r) \u306B\u5BFE\u3057\u3066\u3001\
    [_l, _r) + [l, r) \u306E\u30CF\u30C3\u30B7\u30E5\u5024\n     */\n    __uint128_t\
    \ concat(__uint128_t r_hash, int l, int r){\n        return (r_hash * bases[r\
    \ - l] + get(l, r)) % _mod;\n\t}\n\n    /**\n     * @return string[l1, r1), string[l2,\
    \ r2) \u306E\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n   \
    \  */\n    int longest_common_prefix(int l1, int r1, int l2, int r2){\n      \
    \  int ok = 0, ng = std::min(r1 - l1, r2 - l2) + 1;\n        while(std::abs(ok\
    \ - ng) > 1){\n            int mid = (ok + ng) / 2;\n            if(get(l1, l1\
    \ + mid) == get(l2, l2 + mid)) ok = mid;\n            else ng = mid;\n       \
    \ }\n        return ok;\n    }\n};\n\n\n#line 4 \"test/alds1-14-b.test.cpp\"\n\
    using namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j);\
    \ i < (ll)(n); i++)\n\nint main(void){\n\n    //ifstream in(\"in\");\n    //cin.rdbuf(in.rdbuf());\n\
    \    //ofstream fout(\"out\");\n\n    // input\n\n\tstring s, t;\n\tcin >> s >>\
    \ t;\n\trolling_hash rh(s), _rh(t);\n    auto t_hash = _rh.get(0, t.size());\n\
    \n\t// calculate\n\n\tvector<int> ans;\n    rep(i,0,(int)s.size() - (int)t.size()\
    \ + 1){\n        if(rh.get(i, i + t.size()) == t_hash) cout << i << endl;\n  \
    \  }\n    \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    #include <bits/stdc++.h>\n#include \"../standard/rolling_hash.hpp\"\nusing namespace\
    \ std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n);\
    \ i++)\n\nint main(void){\n\n    //ifstream in(\"in\");\n    //cin.rdbuf(in.rdbuf());\n\
    \    //ofstream fout(\"out\");\n\n    // input\n\n\tstring s, t;\n\tcin >> s >>\
    \ t;\n\trolling_hash rh(s), _rh(t);\n    auto t_hash = _rh.get(0, t.size());\n\
    \n\t// calculate\n\n\tvector<int> ans;\n    rep(i,0,(int)s.size() - (int)t.size()\
    \ + 1){\n        if(rh.get(i, i + t.size()) == t_hash) cout << i << endl;\n  \
    \  }\n    \n}\n"
  dependsOn:
  - standard/rolling_hash.hpp
  isVerificationFile: true
  path: test/alds1-14-b.test.cpp
  requiredBy: []
  timestamp: '2023-06-10 03:01:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/alds1-14-b.test.cpp
layout: document
redirect_from:
- /verify/test/alds1-14-b.test.cpp
- /verify/test/alds1-14-b.test.cpp.html
title: test/alds1-14-b.test.cpp
---
