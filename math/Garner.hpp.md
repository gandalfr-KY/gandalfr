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
    - https://kopricky.github.io/code/Computation_Advanced/garner.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.17/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: mod_inverse.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <vector>\n\n#include \"mod_inverse.hpp\"\n\n/*\n *\
    \ O(N)\n * from : https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    \ */\nlong long Garner(std::vector<long long> a, std::vector<long long> p,\n \
    \                const int mod) {\n    for (long long &x : a)\n        x %= mod;\n\
    \    int sz = a.size();\n    std::vector<long long> kp(sz + 1, 0), rmult(sz +\
    \ 1, 1);\n    p.push_back(mod);\n    for (int i = 0; i < sz; ++i) {\n        long\
    \ long x = (a[i] - kp[i]) * mod_inverse(rmult[i], p[i]) % p[i];\n        x = (x\
    \ < 0) ? (x + p[i]) : x;\n        for (int j = i + 1; j < sz + 1; ++j) {\n   \
    \         kp[j] = (kp[j] + rmult[j] * x) % p[j];\n            rmult[j] = rmult[j]\
    \ * p[i] % p[j];\n        }\n    }\n    return kp[sz];\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/Garner.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/Garner.hpp
layout: document
redirect_from:
- /library/math/Garner.hpp
- /library/math/Garner.hpp.html
title: math/Garner.hpp
---
