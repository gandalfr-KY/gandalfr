---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.16/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: gandalfr/graph/lowlink.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B\"\n#include\
    \ <bits/stdc++.h>\n#include \"gandalfr/graph/lowlink.hpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    #define all(a) (a).begin(),(a).end()\n\nint main(void){\n\n    int N, M;\n   \
    \ cin >> N >> M;\n    graph<int, false> G(N);\n    rep(i,0,M){\n        int a,\
    \ b;\n        cin >> a >> b;\n        G.add_edge(a, b);\n    }\n    lowlink LL(G);\n\
    \    vector<edge<int>> ans;\n    for(auto id : LL.bridges()) {\n        ans.push_back(G.edges()[id]);\n\
    \    }\n    for(auto &e : ans) if(e.from > e.to) swap(e.from, e.to);\n    sort(all(ans));\n\
    \    for(auto &e : ans) cout << e << endl;\n\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/grl-3-b.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/grl-3-b.test.cpp
layout: document
redirect_from:
- /verify/test/grl-3-b.test.cpp
- /verify/test/grl-3-b.test.cpp.html
title: test/grl-3-b.test.cpp
---
