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
  code: '#include <bits/stdc++.h>

    #include "gandalfr/basic"

    using namespace std;

    using ll = long long;

    const int INF = 1001001001;

    const int MAXINT = std::numeric_limits<int>::max();

    const int MININT = std::numeric_limits<int>::min();

    const ll INFLL = 1001001001001001001;

    const ll MAXLL = std::numeric_limits<ll>::max();

    const ll MINLL = std::numeric_limits<ll>::min();

    const ll MOD  = 1000000007;

    const ll _MOD = 998244353;

    #define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)

    #define rrep(i, j, n) for(ll i = (ll)(n-1); i >= (ll)(j); i--)

    #define all(a) (a).begin(),(a).end()

    #define LF cout << endl

    #ifdef ENABLE_MULTI_FOR

    #define mfor(it, v) for(multi_iter it(v); !it.fin(); ++it)

    #endif

    template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) { return a <
    b && (a = b, true); }

    template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) { return a >
    b && (a = b, true); }

    void Yes(bool ok){ std::cout << (ok ? "Yes" : "No") << std::endl; }


    int main(void){




    }

    '
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
