---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/binary_indexed_tree.hpp
    title: "\u4E00\u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97"
  - icon: ':heavy_check_mark:'
    path: other/io_supporter.hpp
    title: other/io_supporter.hpp
  - icon: ':heavy_check_mark:'
    path: standard/compress.hpp
    title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\
      \u3067\u6307\u5B9A\u3057\u3001\u7834\u58CA\u7684\u306B\u5EA7\u6A19\u5727\u7E2E\
      \u3059\u308B"
  - icon: ':heavy_check_mark:'
    path: standard/inversion.hpp
    title: "\u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\
      \u3067\u6307\u5B9A\u3057\u3001\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
  bundledCode: "#line 1 \"test/alds1-5-d.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D\"\
    \n#include <bits/stdc++.h>\n#line 1 \"standard/inversion.hpp\"\n\n\n#line 1 \"\
    standard/compress.hpp\"\n\n\n#line 5 \"standard/compress.hpp\"\n#include <type_traits>\n\
    \n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\
    \u9593\u3067\u6307\u5B9A\u3057\u3001\u7834\u58CA\u7684\u306B\u5EA7\u6A19\u5727\
    \u7E2E\u3059\u308B\n * @param __begin \u5EA7\u5727\u3059\u308B\u5DE6\u7AEF\u306E\
    \u30A4\u30C6\u30EC\u30FC\u30BF\n * @param __end \u53F3\u7AEF\u306E\u30A4\u30C6\
    \u30EC\u30FC\u30BF\n * @attention 0 \u306F\u3058\u307E\u308A\u3067\u5727\u7E2E\
    \u3059\u308B\u3002\n */\ntemplate<typename InputIterator>\nvoid compress(InputIterator\
    \ __begin, InputIterator __end){\n    using T = typename std::iterator_traits<InputIterator>::value_type;\n\
    \    std::vector<T> w(__begin, __end);\n    std::sort(w.begin(), w.end());\n \
    \   w.erase(std::unique(w.begin(), w.end()), w.end());\n    for(auto it = __begin;\
    \ it != __end; it++) *it = static_cast<T>(std::lower_bound(w.begin(), w.end(),\
    \ *it) - w.begin());\n}\n\n\n#line 1 \"data_structure/binary_indexed_tree.hpp\"\
    \n\n\n#line 4 \"data_structure/binary_indexed_tree.hpp\"\n\n/**\n * @brief \u4E00\
    \u70B9\u52A0\u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97\n * @attention 0-indexed\n\
    */\ntemplate<class T>\nstruct binary_indexed_tree{\n  private:\n    int N;\n \
    \   std::vector<T> bit;\n\n  public:\n    binary_indexed_tree(int siz) : N(siz),\
    \ bit(N, 0) {}\n\n    /** \n     * @return a \u306E\u4F4D\u7F6E\u306B w \u3092\
    \u52A0\u7B97\n     */\n    void add(int a, T w){\n        for(int x = a + 1; x\
    \ <= N; x += x & -x) bit[x - 1] += w;\n    }\n\n    /** \n     * @return [0, a)\
    \ \u306E\u7DCF\u548C\n     */\n    T get(int a){\n        T ret = 0;\n       \
    \ for(int x = a; x > 0; x -= x & -x) ret += bit[x - 1];\n        return ret;\n\
    \    }\n};\n\n\n#line 6 \"standard/inversion.hpp\"\n\n/**\n * @brief \u30B3\u30F3\
    \u30C6\u30CA\u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\u3067\u6307\u5B9A\
    \u3057\u3001\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B\n * @param __begin \u5DE6\
    \u7AEF\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @param __end \u53F3\u7AEF\u306E\
    \u30A4\u30C6\u30EC\u30FC\u30BF\n */\ntemplate<typename InputIterator>\nlong long\
    \ inversion(const InputIterator &__begin, const InputIterator &__end){\n    int\
    \ N = std::distance(__begin, __end);\n    if(!N) return 0;\n    std::vector<typename\
    \ std::iterator_traits<InputIterator>::value_type> cmp(__begin, __end);  // vector\u3092\
    \u4F5C\u6210\n    compress(cmp.begin(), cmp.end());\n    binary_indexed_tree<long\
    \ long> bit(static_cast<int>(*std::max_element(cmp.begin(), cmp.end())));\n  \
    \  long long ret = (long long)N * (N - 1) / 2;\n    for(auto &x : cmp){\n    \
    \    bit.add(static_cast<int>(x), 1);\n        ret -= bit.get(static_cast<int>(x));\n\
    \    }\n    return ret;\n}\n\n\n#line 1 \"other/io_supporter.hpp\"\n\n\n#line\
    \ 7 \"other/io_supporter.hpp\"\n\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::vector<T> &v) {\n    for(int i=0; i<(int)v.size(); i++) os <<\
    \ v[i] << (i+1 != (int)v.size() ? \" \" : \"\");\n    return os;\n}\ntemplate<typename\
    \ T>\nstd::istream &operator>>(std::istream &is, std::vector<T> &v){\n    for(T\
    \ &in : v) is >> in;\n    return is;\n}\n\ntemplate<typename T1, typename T2>\n\
    std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2>& p) {\n   \
    \ os << p.first << \" \" << p.second;\n    return os;\n}\ntemplate<typename T1,\
    \ typename T2>\nstd::istream &operator>>(std::istream &is, std::pair<T1, T2> &p)\
    \ {\n    is >> p.first >> p.second;\n    return is;\n}\n\ntemplate<typename T>\n\
    std::ostream &operator<<(std::ostream &os, std::queue<T> v) {\n    int N = v.size();\n\
    \    for(int i=0; i<N; i++) {\n        os << v.front() << (i+1 != N ? \" \" :\
    \ \"\");\n        v.pop();\n    }\n    return os;\n}\n\ntemplate<typename T>\n\
    std::ostream &operator<<(std::ostream &os, const std::set<T> &st) {\n    for(const\
    \ T &x : st){\n        std::cout << x << \" \";\n    }\n    return os;\n}\n\n\
    template<typename T>\nstd::ostream &operator<<(std::ostream &os, const std::multiset<T>\
    \ &st) {\n    for(const T &x : st){\n        std::cout << x << \" \";\n    }\n\
    \    return os;\n}\n\n\n\n#line 5 \"test/alds1-5-d.test.cpp\"\nusing namespace\
    \ std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n);\
    \ i++)\n#define all(a) (a).begin(),(a).end()\nvoid Yes(bool ok){ cout << (ok ?\
    \ \"Yes\" : \"No\") << endl; }\n\nint main(void){\n \n    /*ifstream in(\"input.txt\"\
    );\n    cin.rdbuf(in.rdbuf());\n    ofstream fout(\"output.txt\");*/\n \n \n \
    \   //input\n \n    int N;\n    cin >> N;\n    vector<int> A(N);\n    cin >> A;\n\
    \n    //calculate\n    \n    cout << inversion(A.begin(), A.end()) << endl;\n\
    \ \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D\"\n\
    #include <bits/stdc++.h>\n#include \"../standard/inversion.hpp\"\n#include \"\
    ../other/io_supporter.hpp\"\nusing namespace std;\nusing ll = long long;\n#define\
    \ rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\n\
    void Yes(bool ok){ cout << (ok ? \"Yes\" : \"No\") << endl; }\n\nint main(void){\n\
    \ \n    /*ifstream in(\"input.txt\");\n    cin.rdbuf(in.rdbuf());\n    ofstream\
    \ fout(\"output.txt\");*/\n \n \n    //input\n \n    int N;\n    cin >> N;\n \
    \   vector<int> A(N);\n    cin >> A;\n\n    //calculate\n    \n    cout << inversion(A.begin(),\
    \ A.end()) << endl;\n \n}"
  dependsOn:
  - standard/inversion.hpp
  - standard/compress.hpp
  - data_structure/binary_indexed_tree.hpp
  - other/io_supporter.hpp
  isVerificationFile: true
  path: test/alds1-5-d.test.cpp
  requiredBy: []
  timestamp: '2023-06-08 21:09:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/alds1-5-d.test.cpp
layout: document
redirect_from:
- /verify/test/alds1-5-d.test.cpp
- /verify/test/alds1-5-d.test.cpp.html
title: test/alds1-5-d.test.cpp
---
