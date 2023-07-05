---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':heavy_check_mark:'
    path: graph/Warshall_Floyd.hpp
    title: graph/Warshall_Floyd.hpp
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
  - icon: ':question:'
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
  - icon: ':warning:'
    path: graph/is_isomorphic.hpp
    title: graph/is_isomorphic.hpp
  - icon: ':heavy_check_mark:'
    path: graph/lowest_common_ancestor.hpp
    title: "\u7121\u5411\u5358\u7D14\u6728\u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\
      \u3092\u6C42\u3081\u308B\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: "\u5358\u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\u70B9\u30FB\
      \u6A4B\u3092\u6C42\u3081\u308B"
  - icon: ':warning:'
    path: graph/traveling_salesman.hpp
    title: graph/traveling_salesman.hpp
  - icon: ':warning:'
    path: other/random.hpp
    title: other/random.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-1-a.test.cpp
    title: test/grl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-1-c.test.cpp
    title: test/grl-1-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-2-a.test.cpp
    title: test/grl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-b.test.cpp
    title: test/grl-3-b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-5-c.test.cpp
    title: test/grl-5-c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/itp1-t-d.test.cpp
    title: test/itp1-t-d.test.cpp
  - icon: ':x:'
    path: test/jsc2021-g.test.cpp
    title: test/jsc2021-g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/manhattan-mst.test.cpp
    title: test/manhattan-mst.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
    links: []
  bundledCode: "#line 2 \"math/matrix.hpp\"\n#include <assert.h>\n\n#include <iostream>\n\
    #include <valarray>\n#include <vector>\n\ntemplate <class T> class matrix {\n\
    \  private:\n    int H, W;\n    std::valarray<std::valarray<T>> table;\n\n  public:\n\
    \    matrix() = default;\n    matrix(int _H, int _W, T val = 0)\n        : H(_H),\
    \ W(_W), table(std::valarray<T>(val, _W), _H) {}\n    matrix(const std::vector<std::vector<T>>\
    \ &vv)\n        : H(vv.size()), W(vv[0].size()), table(std::valarray<T>(W), H)\
    \ {\n        for (int i = 0; i < H; i++)\n            for (int j = 0; j < W; j++)\n\
    \                table[i][j] = vv[i][j];\n    }\n    matrix(const std::valarray<std::valarray<T>>\
    \ &vv)\n        : H(vv.size()), W(vv[0].size()), table(vv) {}\n\n    /**\n   \
    \  * @brief \u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002\n   \
    \  * @param val \u62E1\u5F35\u90E8\u5206\u306E\u5024\n     */\n    void resize(int\
    \ _H, int _W, T val = 0) {\n        H = _H, W = _W;\n        table.resize(_H,\
    \ std::valarray<T>(val, _H));\n    }\n    int size_H() const { return H; }\n \
    \   int size_W() const { return W; }\n    matrix<T> transpose() const {\n    \
    \    matrix<T> ret(W, H);\n        for (int i = 0; i < H; i++)\n            for\
    \ (int j = 0; j < W; j++)\n                ret[j][i] = table[i][j];\n        return\
    \ ret;\n    }\n    /**\n     * @attention O(n^3)\n     * @attention \u6574\u6570\
    \u578B\u3067\u306F\u6B63\u3057\u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002\
    double \u3084 fraction \u3092\u4F7F\u3046\u3053\u3068\u3002\n     */\n    const\
    \ T determinant() const {\n        assert(H == W);\n        matrix<T> dfm(*this);\n\
    \        T ret = 1;\n        for (int i = 0; i < H; i++) {\n            if (dfm[i][i]\
    \ == 0) {\n                int piv;\n                for (piv = i + 1; piv < H;\
    \ piv++)\n                    if (dfm[piv][i] != 0)\n                        break;\n\
    \                if (piv == H)\n                    return 0;\n              \
    \  dfm[i].swap(dfm[piv]);\n                ret *= -1;\n            }\n       \
    \     for (int j = i + 1; j < H; j++)\n                dfm[j] -= dfm[i] * (dfm[j][i]\
    \ / dfm[i][i]);\n            ret *= dfm[i][i];\n        }\n        return ret;\n\
    \    }\n\n    void print() const {\n        for (int i = 0; i < H; i++) {\n  \
    \          for (int j = 0; j < W; j++) {\n                std::cout << table[i][j]\
    \ << (j == W - 1 ? \"\" : \" \");\n            }\n            std::cout << std::endl;\n\
    \        }\n    }\n\n    matrix<T> &operator+=(const matrix<T> &a) {\n       \
    \ this->table += a.table;\n        return *this;\n    }\n    matrix<T> &operator-=(const\
    \ matrix<T> &a) {\n        this->table -= a.table;\n        return *this;\n  \
    \  }\n    matrix<T> &operator*=(const T &a) {\n        this->table *= a;\n   \
    \     return *this;\n    }\n    matrix<T> &operator*=(const matrix<T> &a) {\n\
    \        assert(W == a.H);\n        matrix<T> a_t(a.transpose()), ret(H, a.W);\n\
    \        for (int i = 0; i < H; i++) {\n            for (int j = 0; j < a.W; j++)\
    \ {\n                ret[i][j] = (this->table[i] * a_t.table[j]).sum();\n    \
    \        }\n        }\n        return *this = ret;\n    }\n    matrix<T> &operator/=(const\
    \ T &a) {\n        this->table /= a;\n        return *this;\n    }\n    /**\n\
    \     * @brief \u884C\u5217\u306E\u51AA\u4E57\u3002\n     * @param n \u6307\u6570\
    \n     * @attention n \u304C 0 \u306A\u3089\u5358\u4F4D\u884C\u5217\u3002\n  \
    \   * @attention \u6F14\u7B97\u5B50\u306E\u512A\u5148\u5EA6\u306B\u6CE8\u610F\u3002\
    \n     */\n    matrix<T> operator^=(long long n) {\n        assert(H == W);\n\
    \        if (n == 0)\n            return *this = E(H);\n        n--;\n       \
    \ matrix<T> x(*this);\n        while (n) {\n            if (n & 1)\n         \
    \       *this *= x;\n            x *= x;\n            n >>= 1;\n        }\n  \
    \      return *this;\n    }\n\n    matrix<T> operator+() { return *this; }\n \
    \   matrix<T> operator-() { return matrix<T>(*this) *= -1; }\n    matrix<T> operator+(const\
    \ matrix<T> &a) { return matrix<T>(*this) += a; }\n    matrix<T> operator-(const\
    \ matrix<T> &a) { return matrix<T>(*this) -= a; }\n    template <typename S> matrix<T>\
    \ operator*(const S &a) {\n        return matrix<T>(*this) *= a;\n    }\n    matrix<T>\
    \ operator/(const T &a) { return matrix<T>(*this) /= a; }\n    matrix<T> operator^(long\
    \ long n) { return matrix<T>(*this) ^= n; }\n    std::valarray<T> &operator[](int\
    \ h) { return table[h]; }\n    friend std::istream &operator>>(std::istream &is,\
    \ matrix<T> &mt) {\n        for (auto &arr : mt.table)\n            for (auto\
    \ &x : arr)\n                is >> x;\n        return is;\n    }\n    /**\n  \
    \   * @brief \u30B5\u30A4\u30BA n \u306E\u5358\u4F4D\u884C\u5217\u3002\n     */\n\
    \    static matrix<T> E(int N) {\n        matrix<T> ret(N, N);\n        for (int\
    \ i = 0; i < N; i++)\n            ret[i][i] = 1;\n        return ret;\n    }\n\
    };\n"
  code: "#pragma once\n#include <assert.h>\n\n#include <iostream>\n#include <valarray>\n\
    #include <vector>\n\ntemplate <class T> class matrix {\n  private:\n    int H,\
    \ W;\n    std::valarray<std::valarray<T>> table;\n\n  public:\n    matrix() =\
    \ default;\n    matrix(int _H, int _W, T val = 0)\n        : H(_H), W(_W), table(std::valarray<T>(val,\
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
    \            ret[i][i] = 1;\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix.hpp
  requiredBy:
  - other/random.hpp
  - graph/is_isomorphic.hpp
  - graph/lowest_common_ancestor.hpp
  - graph/graph.hpp
  - graph/Warshall_Floyd.hpp
  - graph/doubling.hpp
  - graph/lowlink.hpp
  - graph/traveling_salesman.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/grl-1-a.test.cpp
  - test/jsc2021-g.test.cpp
  - test/grl-2-a.test.cpp
  - test/grl-5-c.test.cpp
  - test/grl-5-a.test.cpp
  - test/manhattan-mst.test.cpp
  - test/grl-1-c.test.cpp
  - test/grl-3-a.test.cpp
  - test/grl-3-b.test.cpp
  - test/itp1-t-d.test.cpp
documentation_of: math/matrix.hpp
layout: document
redirect_from:
- /library/math/matrix.hpp
- /library/math/matrix.hpp.html
title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
---
