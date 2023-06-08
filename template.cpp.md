---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: gandalfr/all:\
    \ line -1: no such header\n"
  code: "#include <bits/stdc++.h>\n#include \"gandalfr/all\"\nusing namespace std;\n\
    using ll = long long;\nconst int INF = 1001001001;\nconst int MAXINT = std::numeric_limits<int>::max();\n\
    const int MININT = std::numeric_limits<int>::min();\nconst ll INFL = 1001001001001001001;\n\
    const ll MAXLL = std::numeric_limits<ll>::max();\nconst ll MINLL = std::numeric_limits<ll>::min();\n\
    const ll MOD  = 1000000007;\nconst ll _MOD = 998244353;\n#define rep(i, j, n)\
    \ for(ll i = (ll)(j); i < (ll)(n); i++)\n#define rrep(i, j, n) for(ll i = (ll)(n-1);\
    \ i >= (ll)(j); i--)\n#define fore(i,a) for(auto &i : a)\n#define all(a) (a).begin(),(a).end()\n\
    #define lr(a, l, r) (a).begin()+(l),(a).begin()+(r)\n#define LF cout << endl\n\
    template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { return a <\
    \ b && (a = b, true); }\ntemplate<typename T1, typename T2> inline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\nvoid Yes(bool ok){ cout << (ok\
    \ ? \"Yes\" : \"No\") << endl; }\nusing mint = mod_integer<MOD>;\nusing _mint\
    \ = mod_integer<_MOD>;\nusing binom = binomial_coefficients<mint>;\nusing _binom\
    \ = binomial_coefficients<_mint>;\n\nint main(void){\n \n    /*ifstream in(\"\
    in\");\n    cin.rdbuf(in.rdbuf());\n    ofstream fout(\"out\");*/\n \n    //input\n\
    \n\n\n    //calculate\n\n    \n\n\n}"
  dependsOn: []
  isVerificationFile: false
  path: template.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template.cpp
layout: document
redirect_from:
- /library/template.cpp
- /library/template.cpp.html
title: template.cpp
---
