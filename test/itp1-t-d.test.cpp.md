---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/matrix.hpp
    title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D
  bundledCode: "#line 1 \"test/itp1-t-d.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D\"\
    \n#include <bits/stdc++.h>\n#line 1 \"math/matrix.hpp\"\n\n\n#line 4 \"math/matrix.hpp\"\
    \n\n#line 8 \"math/matrix.hpp\"\n\ntemplate <class T> class matrix {\n  private:\n\
    \    int H, W;\n    std::valarray<std::valarray<T>> table;\n\n  public:\n    matrix()\
    \ = default;\n    matrix(int _H, int _W, T val = 0)\n        : H(_H), W(_W), table(std::valarray<T>(val,\
    \ _W), _H) {}\n    matrix(const std::vector<std::vector<T>> &vv)\n        : H(vv.size()),\
    \ W(vv[0].size()), table(std::valarray<T>(W), H) {\n        for (int i = 0; i\
    \ < H; i++)\n            for (int j = 0; j < W; j++)\n                table[i][j]\
    \ = vv[i][j];\n    }\n    matrix(const std::valarray<std::valarray<T>> &vv)\n\
    \        : H(vv.size()), W(vv[0].size()), table(vv) {}\n\n    /**\n     * @brief\
    \ \u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002\n     * @param\
    \ val \u62E1\u5F35\u90E8\u5206\u306E\u5024\n     */\n    void resize(int _H, int\
    \ _W, T val = 0) {\n        H = _H, W = _W;\n        table.resize(_H, std::valarray<T>(val,\
    \ _H));\n    }\n    int size_H() const { return H; }\n    int size_W() const {\
    \ return W; }\n    matrix<T> transpose() const {\n        matrix<T> ret(W, H);\n\
    \        for (int i = 0; i < H; i++)\n            for (int j = 0; j < W; j++)\n\
    \                ret[j][i] = table[i][j];\n        return ret;\n    }\n    /**\n\
    \     * @attention O(n^3)\n     * @attention \u6574\u6570\u578B\u3067\u306F\u6B63\
    \u3057\u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002double \u3084 fraction \u3092\
    \u4F7F\u3046\u3053\u3068\u3002\n     */\n    const T determinant() const {\n \
    \       assert(H == W);\n        matrix<T> dfm(*this);\n        T ret = 1;\n \
    \       for (int i = 0; i < H; i++) {\n            if (dfm[i][i] == 0) {\n   \
    \             int piv;\n                for (piv = i + 1; piv < H; piv++)\n  \
    \                  if (dfm[piv][i] != 0)\n                        break;\n   \
    \             if (piv == H)\n                    return 0;\n                dfm[i].swap(dfm[piv]);\n\
    \                ret *= -1;\n            }\n            for (int j = i + 1; j\
    \ < H; j++)\n                dfm[j] -= dfm[i] * (dfm[j][i] / dfm[i][i]);\n   \
    \         ret *= dfm[i][i];\n        }\n        return ret;\n    }\n\n    void\
    \ print() const {\n        for (int i = 0; i < H; i++) {\n            for (int\
    \ j = 0; j < W; j++) {\n                std::cout << table[i][j] << (j == W -\
    \ 1 ? \"\" : \" \");\n            }\n            std::cout << std::endl;\n   \
    \     }\n    }\n\n    matrix<T> &operator+=(const matrix<T> &a) {\n        this->table\
    \ += a.table;\n        return *this;\n    }\n    matrix<T> &operator-=(const matrix<T>\
    \ &a) {\n        this->table -= a.table;\n        return *this;\n    }\n    matrix<T>\
    \ &operator*=(const T &a) {\n        this->table *= a;\n        return *this;\n\
    \    }\n    matrix<T> &operator*=(const matrix<T> &a) {\n        assert(W == a.H);\n\
    \        matrix<T> a_t(a.transpose()), ret(H, a.W);\n        for (int i = 0; i\
    \ < H; i++) {\n            for (int j = 0; j < a.W; j++) {\n                ret[i][j]\
    \ = (this->table[i] * a_t.table[j]).sum();\n            }\n        }\n       \
    \ return *this = ret;\n    }\n    matrix<T> &operator/=(const T &a) {\n      \
    \  this->table /= a;\n        return *this;\n    }\n    /**\n     * @brief \u884C\
    \u5217\u306E\u51AA\u4E57\u3002\n     * @param n \u6307\u6570\n     * @attention\
    \ n \u304C 0 \u306A\u3089\u5358\u4F4D\u884C\u5217\u3002\n     * @attention \u6F14\
    \u7B97\u5B50\u306E\u512A\u5148\u5EA6\u306B\u6CE8\u610F\u3002\n     */\n    matrix<T>\
    \ operator^=(long long n) {\n        assert(H == W);\n        if (n == 0)\n  \
    \          return *this = E(H);\n        n--;\n        matrix<T> x(*this);\n \
    \       while (n) {\n            if (n & 1)\n                *this *= x;\n   \
    \         x *= x;\n            n >>= 1;\n        }\n        return *this;\n  \
    \  }\n\n    matrix<T> operator+() { return *this; }\n    matrix<T> operator-()\
    \ { return matrix<T>(*this) *= -1; }\n    matrix<T> operator+(const matrix<T>\
    \ &a) { return matrix<T>(*this) += a; }\n    matrix<T> operator-(const matrix<T>\
    \ &a) { return matrix<T>(*this) -= a; }\n    template <typename S> matrix<T> operator*(const\
    \ S &a) {\n        return matrix<T>(*this) *= a;\n    }\n    matrix<T> operator/(const\
    \ T &a) { return matrix<T>(*this) /= a; }\n    matrix<T> operator^(long long n)\
    \ { return matrix<T>(*this) ^= n; }\n    std::valarray<T> &operator[](int h) {\
    \ return table[h]; }\n    friend std::istream &operator>>(std::istream &is, matrix<T>\
    \ &mt) {\n        for (auto &arr : mt.table)\n            for (auto &x : arr)\n\
    \                is >> x;\n        return is;\n    }\n    /**\n     * @brief \u30B5\
    \u30A4\u30BA n \u306E\u5358\u4F4D\u884C\u5217\u3002\n     */\n    static matrix<T>\
    \ E(int N) {\n        matrix<T> ret(N, N);\n        for (int i = 0; i < N; i++)\n\
    \            ret[i][i] = 1;\n        return ret;\n    }\n};\n\n\n#line 4 \"test/itp1-t-d.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i =\
    \ (ll)(j); i < (ll)(n); i++)\n\nint main(void){\n \n    //input\n \n    int H,\
    \ W, L;\n    cin >> H >> W >> L;\n    matrix<ll> A(H, W), B(W, L);\n    cin >>\
    \ A >> B;\n\n    //calculate\n \n    (A * B).print();\n \n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D\"\n\
    #include <bits/stdc++.h>\n#include \"../math/matrix.hpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n \n    //input\n \n    int H, W, L;\n    cin >> H >> W >> L;\n\
    \    matrix<ll> A(H, W), B(W, L);\n    cin >> A >> B;\n\n    //calculate\n \n\
    \    (A * B).print();\n \n}"
  dependsOn:
  - math/matrix.hpp
  isVerificationFile: true
  path: test/itp1-t-d.test.cpp
  requiredBy: []
  timestamp: '2023-06-19 01:40:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/itp1-t-d.test.cpp
layout: document
redirect_from:
- /verify/test/itp1-t-d.test.cpp
- /verify/test/itp1-t-d.test.cpp.html
title: test/itp1-t-d.test.cpp
---
