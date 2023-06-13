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
      \u3067\u6307\u5B9A\u3057\u3001\u5EA7\u6A19\u5727\u7E2E\u3059\u308B"
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
    \n#include <bits/stdc++.h>\n#line 1 \"standard/inversion.hpp\"\n\n\n#line 5 \"\
    standard/inversion.hpp\"\n#include <type_traits>\n#line 1 \"standard/compress.hpp\"\
    \n\n\n#line 6 \"standard/compress.hpp\"\n\n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\
    \u306E\u8981\u7D20\u3092\u534A\u958B\u533A\u9593\u3067\u6307\u5B9A\u3057\u3001\
    \u5EA7\u6A19\u5727\u7E2E\u3059\u308B\n * @param __begin \u5EA7\u5727\u3059\u308B\
    \u5DE6\u7AEF\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @param __end \u53F3\u7AEF\
    \u306E\u30A4\u30C6\u30EC\u30FC\u30BF\n * @attention 0 \u306F\u3058\u307E\u308A\
    \u3067\u5727\u7E2E\u3059\u308B\u3002\n */\ntemplate<typename InputIterator>\n\
    std::vector<int> compress(const InputIterator &__begin,  const InputIterator &__end){\n\
    \    std::vector<int> ret;\n    ret.reserve(std::distance(__begin, __end));\n\
    \    std::vector<typename std::iterator_traits<InputIterator>::value_type> w(__begin,\
    \ __end);\n    std::sort(w.begin(), w.end());\n    w.erase(std::unique(w.begin(),\
    \ w.end()), w.end());\n    for(auto it = __begin; it != __end; it++)\n       \
    \ ret.push_back(std::lower_bound(w.begin(), w.end(), *it) - w.begin());\n    return\
    \ ret;\n}\n\n\n#line 1 \"data_structure/binary_indexed_tree.hpp\"\n\n\n#line 4\
    \ \"data_structure/binary_indexed_tree.hpp\"\n\n/**\n * @brief \u4E00\u70B9\u52A0\
    \u7B97\u3001\u533A\u9593\u548C\u306E\u53D6\u5F97\n * @attention 0-indexed\n*/\n\
    template<class T>\nstruct binary_indexed_tree{\n  private:\n    int N;\n    std::vector<T>\
    \ bit;\n\n  public:\n    binary_indexed_tree(int siz) : N(siz), bit(N, 0) {}\n\
    \n    /** \n     * @return a \u306E\u4F4D\u7F6E\u306B w \u3092\u52A0\u7B97\n \
    \    */\n    void add(int a, T w){\n        for(int x = a + 1; x <= N; x += x\
    \ & -x) bit[x - 1] += w;\n    }\n\n    /** \n     * @return [0, a) \u306E\u7DCF\
    \u548C\n     */\n    T get(int a){\n        T ret = 0;\n        for(int x = a;\
    \ x > 0; x -= x & -x) ret += bit[x - 1];\n        return ret;\n    }\n};\n\n\n\
    #line 8 \"standard/inversion.hpp\"\n\n/**\n * @brief \u30B3\u30F3\u30C6\u30CA\u306E\
    \u8981\u7D20\u3092\u534A\u958B\u533A\u9593\u3067\u6307\u5B9A\u3057\u3001\u8EE2\
    \u5012\u6570\u3092\u6C42\u3081\u308B\n * @attention \u533A\u9593\u9577\u304C 0\
    \ \u306A\u3089\u3070 0\n */\ntemplate<typename InputIterator>\nlong long inversion(const\
    \ InputIterator &__begin, const InputIterator &__end){\n    int N = std::distance(__begin,\
    \ __end);\n    if(!N) return 0;\n    std::vector<int> cmp = compress(__begin,\
    \ __end);\n    binary_indexed_tree<long long> bit(*std::max_element(cmp.begin(),\
    \ cmp.end()) + 1);\n    long long ret = (long long)N * (N + 1) / 2;\n    for(auto\
    \ &x : cmp){\n        bit.add(x, 1);\n        ret -= bit.get(x + 1);\n    }\n\
    \    return ret;\n}\n\n/**\n * @brief \u8981\u7D20\u306E\u96C6\u5408\u304C\u7B49\
    \u3057\u3044\u534A\u958B\u533A\u9593\u30922\u3064\u6307\u5B9A\u3002\u4E00\u65B9\
    \u3092\u3082\u3046\u4E00\u65B9\u3068\u540C\u3058\u3088\u3046\u306B\u4E26\u3079\
    \u66FF\u3048\u308B\u305F\u3081\u306E swap \u306E\u30B3\u30B9\u30C8\n * @attention\
    \ \u8981\u7D20\u306E\u96C6\u5408\u304C\u4E0D\u4E00\u81F4\u306A\u3089\u3070 -1\u3001\
    \u533A\u9593\u9577\u304C 0 \u306A\u3089\u3070 0\n * @see <a href=\"https://atcoder.jp/contests/arc120/submissions/42083168\"\
    >verify</a>\n */\ntemplate<typename InputIterator>\nlong long inversion(const\
    \ InputIterator &__begin1, const InputIterator &__end1,\n                    const\
    \ InputIterator &__begin2, const InputIterator &__end2){\n    int N = std::distance(__begin1,\
    \ __end1);\n    if(N != std::distance(__begin2, __end2)) return -1;\n    if(N\
    \ == 0) return 0;\n    std::multiset<typename std::iterator_traits<InputIterator>::value_type>\n\
    \        st1(__begin1, __end1), st2(__begin2, __end2);\n    if(st1 != st2) return\
    \ -1;\n\n    std::vector<int> cmp1 = compress(__begin1, __end1), cmp2 = compress(__begin2,\
    \ __end2);\n    std::vector<std::vector<int>> ord(*std::max_element(cmp2.begin(),\
    \ cmp2.end()) + 1);\n    for(int i = 0; i < N; i++) ord[cmp2[i]].push_back(i);\n\
    \    for(int i = N - 1; i >= 0; i--){\n        int tmp = ord[cmp1[i]].back();\n\
    \        ord[cmp1[i]].pop_back();\n        cmp1[i] = tmp;\n    }\n    return inversion(cmp1.begin(),\
    \ cmp1.end());\n}\n\n\n#line 1 \"other/io_supporter.hpp\"\n\n\n#line 8 \"other/io_supporter.hpp\"\
    \n\ntemplate <template <typename, typename...> class ContainerType, typename ValueType>\n\
    std::ostream& operator<<(std::ostream &os, const ContainerType<ValueType>& container)\
    \ {\n    auto it = container.cbegin();\n    if(it == container.end()) return os;\n\
    \    for(; std::next(it) != container.cend(); ++it){\n        os << *it << ' ';\n\
    \    }\n    return os << *it;\n}\n\ntemplate <template <typename, typename...>\
    \ class ContainerType, typename ValueType>\nstd::istream& operator>>(std::istream\
    \ &is, ContainerType<ValueType>& container) {\n    for(auto &x : container) is\
    \ >> x;\n    return is;\n}\n\nstd::ostream& operator<<(std::ostream &os, const\
    \ std::string& s) {\n    std::operator<<(os, s);\n    return os;\n}\n\nstd::istream&\
    \ operator>>(std::istream &is, std::string& s) {\n    std::operator>>(is, s);\n\
    \    return is;\n}\n\ntemplate<typename T1, typename T2>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T1, T2>& p) {\n    os << p.first << ' ' << p.second;\n\
    \    return os;\n}\ntemplate<typename T1, typename T2>\nstd::istream &operator>>(std::istream\
    \ &is, std::pair<T1, T2> &p) {\n    is >> p.first >> p.second;\n    return is;\n\
    }\n\ntemplate<typename T>\nstd::ostream &operator<<(std::ostream &os, std::queue<T>&\
    \ q) {\n    int sz = q.size();\n    while(--sz){\n        os << q.front() << '\
    \ ';\n        q.push(q.front());\n        q.pop();\n    }\n    os << q.front();\n\
    \    q.push(q.front());\n    q.pop();\n    return os;\n}\n\n\n#line 5 \"test/alds1-5-d.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i =\
    \ (ll)(j); i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\nvoid Yes(bool\
    \ ok){ cout << (ok ? \"Yes\" : \"No\") << endl; }\n\nint main(void){\n \n    /*ifstream\
    \ in(\"input.txt\");\n    cin.rdbuf(in.rdbuf());\n    ofstream fout(\"output.txt\"\
    );*/\n \n \n    //input\n \n    int N;\n    cin >> N;\n    vector<int> A(N);\n\
    \    cin >> A;\n\n    //calculate\n    \n    cout << inversion(A.begin(), A.end())\
    \ << endl;\n \n}\n"
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
  timestamp: '2023-06-13 16:07:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/alds1-5-d.test.cpp
layout: document
redirect_from:
- /verify/test/alds1-5-d.test.cpp
- /verify/test/alds1-5-d.test.cpp.html
title: test/alds1-5-d.test.cpp
---
