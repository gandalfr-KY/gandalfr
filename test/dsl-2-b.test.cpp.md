---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/binary_indexed_tree.hpp
    title: "\u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B
  bundledCode: "#line 1 \"test/dsl-2-b.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B\"\
    \n#include <bits/stdc++.h>\n#line 1 \"data_structure/binary_indexed_tree.hpp\"\
    \n\n\n#line 4 \"data_structure/binary_indexed_tree.hpp\"\n\n/**\n * @brief \u4E00\
    \u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97\n * @attention 0-indexed\n\
    */\ntemplate<class T>\nstruct binary_indexed_tree{\n  private:\n    int N;\n \
    \   std::vector<T> bit;\n\n  public:\n    binary_indexed_tree(int siz) : N(siz),\
    \ bit(N, 0) {}\n\n    /** \n     * @return a \u306E\u4F4D\u7F6E\u306B w \u3092\
    \u52A0\u7B97\n     */\n    void add(int a, T w){\n        for(int x = a + 1; x\
    \ <= N; x += x & -x) bit[x - 1] += w;\n    }\n\n    /** \n     * @return [0, a)\
    \ \u306E\u7DCF\u548C\n     */\n    T get(int a){\n        T ret = 0;\n       \
    \ for(int x = a; x > 0; x -= x & -x) ret += bit[x - 1];\n        return ret;\n\
    \    }\n};\n\n\n#line 4 \"test/dsl-2-b.test.cpp\"\nusing namespace std;\nusing\
    \ ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    #define all(a) (a).begin(),(a).end()\nvoid Yes(bool ok){ cout << (ok ? \"Yes\"\
    \ : \"No\") << endl; }\n\nint main(void){\n \n    /*ifstream in(\"input.txt\"\
    );\n    cin.rdbuf(in.rdbuf());\n    ofstream fout(\"output.txt\");*/\n \n \n \
    \   //input\n \n    int N, Q;\n    cin >> N >> Q;\n    binary_indexed_tree<ll>\
    \ bit(N);\n\n    //calculate\n\n    rep(i,0,Q){\n        int a, b, c;\n      \
    \  cin >> a >> b >> c;\n        if(a == 0) bit.add(b - 1, c);\n        else cout\
    \ << bit.get(c) - bit.get(b - 1) << endl;\n    }\n \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B\"\n#include\
    \ <bits/stdc++.h>\n#include \"../data_structure/binary_indexed_tree.hpp\"\nusing\
    \ namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j);\
    \ i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\nvoid Yes(bool ok){\
    \ cout << (ok ? \"Yes\" : \"No\") << endl; }\n\nint main(void){\n \n    /*ifstream\
    \ in(\"input.txt\");\n    cin.rdbuf(in.rdbuf());\n    ofstream fout(\"output.txt\"\
    );*/\n \n \n    //input\n \n    int N, Q;\n    cin >> N >> Q;\n    binary_indexed_tree<ll>\
    \ bit(N);\n\n    //calculate\n\n    rep(i,0,Q){\n        int a, b, c;\n      \
    \  cin >> a >> b >> c;\n        if(a == 0) bit.add(b - 1, c);\n        else cout\
    \ << bit.get(c) - bit.get(b - 1) << endl;\n    }\n \n}"
  dependsOn:
  - data_structure/binary_indexed_tree.hpp
  isVerificationFile: true
  path: test/dsl-2-b.test.cpp
  requiredBy: []
  timestamp: '2023-06-07 01:37:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dsl-2-b.test.cpp
layout: document
redirect_from:
- /verify/test/dsl-2-b.test.cpp
- /verify/test/dsl-2-b.test.cpp.html
title: test/dsl-2-b.test.cpp
---
