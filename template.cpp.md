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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: gandalfr/basic:\
    \ line -1: no such header\n"
  code: "#include <bits/stdc++.h>\n#include \"gandalfr/basic\"\nusing namespace std;\n\
    using ll = long long;\nconst int INF = 1001001001;\nconst ll INFLL = 1001001001001001001;\n\
    const ll MOD  = 1000000007;\nconst ll _MOD = 998244353;\n#define rep(i, j, n)\
    \ for(ll i = (ll)(j); i < (ll)(n); i++)\n#define rrep(i, j, n) for(ll i = (ll)(n-1);\
    \ i >= (ll)(j); i--)\n#define all(a) (a).begin(),(a).end()\n#define LF cout <<\
    \ endl\n#ifdef ENABLE_MULTI_FOR\n#define mfor(it, v) for(multi_iter it(v); !it.fin();\
    \ ++it)\n#endif\ntemplate<typename T1, typename T2> inline bool chmax(T1 &a, T2\
    \ b) { return a < b && (a = b, true); }\ntemplate<typename T1, typename T2> inline\
    \ bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }\nvoid Yes(bool ok){\
    \ std::cout << (ok ? \"Yes\" : \"No\") << std::endl; }\n\nint main(void){\n\n\
    \    int N;\n    cin >> N;\n    vector<int> A(N), B(N);\n    cin >> A >> B;\n\n\
    \    vector dp(N, vector<vector<ll>>(2, vector<ll>(2, INFLL)));\n    dp[0][0][0]\
    \ = A[0];\n    dp[0][1][1] = 0;\n    rep(i,1,N) {\n        rep(j,0,2) rep(k,0,2)\
    \ rep(prvj,0,2) {\n            chmin(dp[i][j][k], dp[i-1][prvj][k] +\n       \
    \         (j == 0 ? A[i] : 0) + (j == prvj ? B[i] : 0));\n        }\n    }\n\n\
    \    ll ans = INFLL;\n    rep(j,0,2) rep(k,0,2) {\n        chmin(ans, dp[N-1][j][k]\
    \ + (j == k ? B[N-1] : 0));\n    }\n    cout << ans << endl;\n    \n\n}\n"
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
