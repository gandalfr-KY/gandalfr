---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/matrix.hpp
    title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-1-c.test.cpp
    title: test/grl-1-c.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/matrix.hpp\"\n#include <assert.h>\n\n#include <iostream>\n\
    #include <utility>\n#include <valarray>\n#include <vector>\n\ntemplate <class\
    \ T> class matrix {\n  private:\n    int H, W;\n    std::valarray<std::valarray<T>>\
    \ table;\n\n    enum rowtrans_operation_name { SCALE, SWAP, ADD };\n    struct\
    \ rowtrans_operation {\n        int op, tar, res;\n        T scl;\n    };\n  \
    \  using operations_history = std::vector<rowtrans_operation>;\n\n  public:\n\
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
    \ ret;\n    }\n\n    void row_swap(int i, int j) {\n        assert(0 <= i && i\
    \ < H);\n        assert(0 <= j && j < H);\n        table[i].swap(table[j]);\n\
    \    }\n    \n    /**\n     * @attention O(n^3)\n     * @attention \u6574\u6570\
    \u578B\u3067\u306F\u6B63\u3057\u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002\
    double \u3084 fraction \u3092\u4F7F\u3046\u3053\u3068\u3002\n     */\n    operations_history\
    \ sweep_method() {\n        operations_history hist;\n        T ret = 1;\n   \
    \     for (int h = 0, w = 0; h < H && w < W; w++) {\n            for (int piv\
    \ = h + 1; piv < H; piv++) {\n                if (table[h][w] < table[piv][w])\
    \ {\n                    hist.push_back({SWAP, h, piv, 0});\n                \
    \    row_swap(h, piv);\n                    \n                }\n            }\n\
    \            if (table[h][w] == 0) {\n                continue;\n            }\n\
    \n            T inv = 1 / table[h][w];\n            hist.push_back({SCALE, -1,\
    \ w, inv});\n            table[h] *= inv;\n            for (int j = h + 1; j <\
    \ H; j++) {\n                hist.push_back({ADD, h, j, - table[j][w]});\n   \
    \             table[j] -= table[h] * table[j][w];\n            }\n           \
    \ h++;\n        }\n        return hist;\n    }\n\n    int rank() {\n        auto\
    \ U(*this);\n        U.sweep_method();\n        int r = 0; // rank\n        for\
    \ (int i = 0; i < H; ++i) {\n            for (int j = 0; j < W; ++j) {\n     \
    \           if (U[i][j] != 0) {\n                    r++;\n                  \
    \  break;\n                }\n            }\n        }\n        return r;\n  \
    \  }\n\n    T determinant() const {\n        assert(H == W);\n        auto U(*this);\n\
    \        T det = 1;\n        auto hist = U.sweep_method();\n        if (U[H-1][H-1]\
    \ == 0) return 0;\n        for (auto &[op, tar, res, scl] : hist) {\n        \
    \    switch (op) {\n            case SCALE:\n                det /= scl;\n   \
    \             break;\n            case SWAP:\n                det *= -1;\n   \
    \             break;\n            }\n        }\n        return det;\n    }\n\n\
    \    std::vector<T> solve_system_of_equations(const std::vector<T> &y) {\n   \
    \     assert(H == W);\n        std::vector<T> x(y);\n        auto U(*this);\n\
    \        auto hist = U.sweep_method();\n        if (U[H-1][H-1] == 0) return {};\n\
    \n        for (auto &[op, tar, res, scl] : hist) {\n            switch (op) {\n\
    \            case SCALE:\n                x[res] *= scl;\n                break;\n\
    \            case SWAP:\n                std::swap(x[tar], x[res]);\n        \
    \        break;\n            case ADD:\n                x[res] += x[tar] * scl;\n\
    \                break;\n            }\n        }\n        \n        for (int\
    \ i = H - 1; i >= 0; --i) {\n            for (int j = 0; j < i; ++j) {\n     \
    \           x[j] -= U[j][i] * x[i];\n            }\n        }\n        return\
    \ x;\n    }\n\n    matrix<T> inverse() {\n        assert(H == W);\n        auto\
    \ INV(matrix<T>::E(H));\n        auto U(*this);\n        auto hist = U.sweep_method();\n\
    \        if (U[H-1][H-1] == 0) return matrix<T>(0, 0);\n\n        for (auto &[op,\
    \ tar, res, scl] : hist) {\n            switch (op) {\n            case SCALE:\n\
    \                INV[res] *= scl;\n                break;\n            case SWAP:\n\
    \                std::swap(INV[tar], INV[res]);\n                break;\n    \
    \        case ADD:\n                INV[res] += INV[tar] * scl;\n            \
    \    break;\n            }\n        }\n        \n        for (int i = H - 1; i\
    \ >= 0; --i) {\n            for (int j = 0; j < i; ++j) {\n                INV[j]\
    \ -= INV[i] * U[j][i];\n            }\n        }\n        return INV;\n    }\n\
    \n\n    void print() const {\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int j = 0; j < W; j++) {\n                std::cout << table[i][j] <<\
    \ (j == W - 1 ? \"\" : \" \");\n            }\n            std::cout << std::endl;\n\
    \        }\n    }\n\n    matrix<T> &operator+=(const matrix<T> &a) {\n       \
    \ this->table += a.table;\n        return *this;\n    }\n    matrix<T> &operator-=(const\
    \ matrix<T> &a) {\n        this->table -= a.table;\n        return *this;\n  \
    \  }\n    matrix<T> &operator*=(const T &a) {\n        this->table *= a;\n   \
    \     return *this;\n    }\n    matrix<T> &operator*=(const matrix<T> &a) {\n\
    \        assert(W == a.H);\n        matrix<T> a_t(a.transpose()), ret(H, a.W);\n\
    \        for (int i = 0; i < H; i++) {\n            for (int j = 0; j < a.W; j++)\
    \ {\n                ret[i][j] = (this->table[i] * a_t.table[j]).sum();\n    \
    \        }\n        }\n        *this = std::move(ret);\n        return *this;\n\
    \    }\n    matrix<T> &operator/=(const T &a) {\n        this->table /= a;\n \
    \       return *this;\n    }\n    /**\n     * @brief \u884C\u5217\u306E\u51AA\u4E57\
    \u3002\n     * @param n \u6307\u6570\n     * @attention n \u304C 0 \u306A\u3089\
    \u5358\u4F4D\u884C\u5217\u3002\n     * @attention \u6F14\u7B97\u5B50\u306E\u512A\
    \u5148\u5EA6\u306B\u6CE8\u610F\u3002\n     */\n    matrix<T> operator^=(long long\
    \ n) {\n        assert(H == W);\n        if (n == 0)\n            return *this\
    \ = E(H);\n        n--;\n        matrix<T> x(*this);\n        while (n) {\n  \
    \          if (n & 1)\n                *this *= x;\n            x *= x;\n    \
    \        n >>= 1;\n        }\n        return *this;\n    }\n\n    matrix<T> operator+()\
    \ { return *this; }\n    matrix<T> operator-() { return matrix<T>(*this) *= -1;\
    \ }\n    matrix<T> operator+(const matrix<T> &a) { return matrix<T>(*this) +=\
    \ a; }\n    matrix<T> operator-(const matrix<T> &a) { return matrix<T>(*this)\
    \ -= a; }\n    template <typename S> matrix<T> operator*(const S &a) {\n     \
    \   return matrix<T>(*this) *= a;\n    }\n    matrix<T> operator/(const T &a)\
    \ { return matrix<T>(*this) /= a; }\n    matrix<T> operator^(long long n) { return\
    \ matrix<T>(*this) ^= n; }\n    std::valarray<T> &operator[](int h) { return table[h];\
    \ }\n    friend std::istream &operator>>(std::istream &is, matrix<T> &mt) {\n\
    \        for (auto &arr : mt.table)\n            for (auto &x : arr)\n       \
    \         is >> x;\n        return is;\n    }\n\n    /**\n     * @brief \u30B5\
    \u30A4\u30BA n \u306E\u5358\u4F4D\u884C\u5217\u3002\n     */\n    static matrix<T>\
    \ E(int N) {\n        matrix<T> ret(N, N);\n        for (int i = 0; i < N; i++)\n\
    \            ret[i][i] = 1;\n        return ret;\n    }\n};\n#line 3 \"graph/Warshall_Floyd.hpp\"\
    \n\ntemplate <class T> matrix<T> Warshall_Floyd(matrix<T> mt) {\n    int N = mt.size_H();\n\
    \    for (int k = 0; k < N; k++)         // \u7D4C\u7531\u3059\u308B\u9802\u70B9\
    \n        for (int i = 0; i < N; i++)     // \u59CB\u70B9\n            for (int\
    \ j = 0; j < N; j++) // \u7D42\u70B9\n                mt[i][j] = std::min(mt[i][j],\
    \ mt[i][k] + mt[k][j]);\n    return mt;\n}\n"
  code: "#pragma once\n#include \"../math/matrix.hpp\"\n\ntemplate <class T> matrix<T>\
    \ Warshall_Floyd(matrix<T> mt) {\n    int N = mt.size_H();\n    for (int k = 0;\
    \ k < N; k++)         // \u7D4C\u7531\u3059\u308B\u9802\u70B9\n        for (int\
    \ i = 0; i < N; i++)     // \u59CB\u70B9\n            for (int j = 0; j < N; j++)\
    \ // \u7D42\u70B9\n                mt[i][j] = std::min(mt[i][j], mt[i][k] + mt[k][j]);\n\
    \    return mt;\n}\n"
  dependsOn:
  - math/matrix.hpp
  isVerificationFile: false
  path: graph/Warshall_Floyd.hpp
  requiredBy: []
  timestamp: '2023-07-21 23:18:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/grl-1-c.test.cpp
documentation_of: graph/Warshall_Floyd.hpp
layout: document
redirect_from:
- /library/graph/Warshall_Floyd.hpp
- /library/graph/Warshall_Floyd.hpp.html
title: graph/Warshall_Floyd.hpp
---
