---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
  - icon: ':question:'
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
  - icon: ':warning:'
    path: graph/is_isomorphic.hpp
    title: graph/is_isomorphic.hpp
  - icon: ':x:'
    path: graph/lowest_common_ancestor.hpp
    title: "\u7121\u5411\u5358\u7D14\u6728\u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\
      \u3092\u6C42\u3081\u308B\u30AF\u30E9\u30B9"
  - icon: ':warning:'
    path: graph/traveling_salesman.hpp
    title: graph/traveling_salesman.hpp
  - icon: ':warning:'
    path: other/random.hpp
    title: other/random.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/grl-1-a.test.cpp
    title: test/grl-1-a.test.cpp
  - icon: ':x:'
    path: test/grl-1-c.test.cpp
    title: test/grl-1-c.test.cpp
  - icon: ':x:'
    path: test/grl-2-a.test.cpp
    title: test/grl-2-a.test.cpp
  - icon: ':x:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':x:'
    path: test/grl-3-b.test.cpp
    title: test/grl-3-b.test.cpp
  - icon: ':x:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  - icon: ':x:'
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
  - icon: ':heavy_check_mark:'
    path: test/shortest_path.test.cpp
    title: test/shortest_path.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
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
    \   int size_W() const { return W; }\n    void transpose() {\n        matrix<T>\
    \ ret(W, H);\n        for (int i = 0; i < H; i++)\n            for (int j = 0;\
    \ j < W; j++)\n                ret.table[j][i] = table[i][j];\n        *this =\
    \ std::move(ret);\n    }\n\n    void row_assign(int i, const std::valarray<T>\
    \ &row) {\n        assert(W == (int)row.size());\n        table[i] = std::move(row);\n\
    \    }\n\n    void row_swap(int i, int j) {\n        assert(0 <= i && i < H);\n\
    \        assert(0 <= j && j < H);\n        table[i].swap(table[j]);\n    }\n\n\
    \    /**\n     * @attention O(n^3)\n     * @attention \u6574\u6570\u578B\u3067\
    \u306F\u6B63\u3057\u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002double \u3084\
    \ fraction \u3092\u4F7F\u3046\u3053\u3068\u3002\n     * @attention \u67A2\u8EF8\
    \u9078\u3073\u3092\u3057\u3066\u3044\u306A\u3044\u306E\u3067 double \u3067\u306F\
    \u8AA4\u5DEE\u304C\u51FA\u308B\u304B\u3082\u3002\n     */\n    operations_history\
    \ sweep_method() {\n        operations_history hist;\n        T ret = 1;\n   \
    \     for (int h = 0, w = 0; h < H && w < W; w++) {\n            if (table[h][w]\
    \ == 0) {\n                for (int piv = h + 1; piv < H; piv++) {\n         \
    \           if (table[piv][w] != 0) {\n                        hist.push_back({SWAP,\
    \ h, piv, 0});\n                        row_swap(h, piv);\n                  \
    \      break;\n                    }\n                }\n                if (table[h][w]\
    \ == 0) {\n                    continue;\n                }\n            }\n \
    \           T inv = 1 / table[h][w];\n            hist.push_back({SCALE, -1, w,\
    \ inv});\n            table[h] *= inv;\n            for (int j = h + 1; j < H;\
    \ j++) {\n                hist.push_back({ADD, h, j, -table[j][w]});\n       \
    \         table[j] -= table[h] * table[j][w];\n            }\n            h++;\n\
    \        }\n        return hist;\n    }\n\n    int rank() {\n        auto U(*this);\n\
    \        U.sweep_method();\n        int r = 0;\n        for (int i = 0; i < H;\
    \ ++i) {\n            for (int j = i; j < W; ++j) {\n                if (U.table[i][j]\
    \ != 0) {\n                    r++;\n                    break;\n            \
    \    }\n            }\n        }\n        return r;\n    }\n\n    T determinant()\
    \ const {\n        assert(H == W);\n        matrix<T> U(*this);\n        T det\
    \ = 1;\n        auto hist = U.sweep_method();\n        if (U.table[H - 1][H -\
    \ 1] == 0)\n            return 0;\n        for (auto &[op, tar, res, scl] : hist)\
    \ {\n            switch (op) {\n            case SCALE:\n                det /=\
    \ scl;\n                break;\n            case SWAP:\n                det *=\
    \ -1;\n                break;\n            }\n        }\n        return det;\n\
    \    }\n\n    std::vector<T> solve_system_of_equations(const std::vector<T> &y)\
    \ {\n        assert(H == W);\n        std::vector<T> x(y);\n        matrix<T>\
    \ U(*this);\n        auto hist = U.sweep_method();\n        if (U.table[H - 1][H\
    \ - 1] == 0)\n            return {};\n\n        for (auto &[op, tar, res, scl]\
    \ : hist) {\n            switch (op) {\n            case SCALE:\n            \
    \    x[res] *= scl;\n                break;\n            case SWAP:\n        \
    \        std::swap(x[tar], x[res]);\n                break;\n            case\
    \ ADD:\n                x[res] += x[tar] * scl;\n                break;\n    \
    \        }\n        }\n\n        for (int i = H - 1; i >= 0; --i) {\n        \
    \    for (int j = 0; j < i; ++j) {\n                x[j] -= U.table[j][i] * x[i];\n\
    \            }\n        }\n        return x;\n    }\n\n    matrix<T> inverse()\
    \ {\n        assert(H == W);\n        matrix<T> INV(matrix<T>::E(H)), U(*this);\n\
    \        auto hist = U.sweep_method();\n        if (U.table[H - 1][H - 1] == 0)\n\
    \            return matrix<T>(0, 0);\n\n        for (auto &[op, tar, res, scl]\
    \ : hist) {\n            switch (op) {\n            case SCALE:\n            \
    \    INV.table[res] *= scl;\n                break;\n            case SWAP:\n\
    \                std::swap(INV.table[tar], INV.table[res]);\n                break;\n\
    \            case ADD:\n                INV.table[res] += INV.table[tar] * scl;\n\
    \                break;\n            }\n        }\n\n        for (int i = H -\
    \ 1; i >= 0; --i) {\n            for (int j = 0; j < i; ++j) {\n             \
    \   INV.table[j] -= INV.table[i] * U.table[j][i];\n            }\n        }\n\
    \        return INV;\n    }\n\n    void print() const {\n        for (int i =\
    \ 0; i < H; i++) {\n            for (int j = 0; j < W; j++) {\n              \
    \  std::cout << table[i][j] << (j == W - 1 ? \"\" : \" \");\n            }\n \
    \           std::cout << std::endl;\n        }\n    }\n\n    matrix<T> &operator+=(const\
    \ matrix<T> &a) {\n        this->table += a.table;\n        return *this;\n  \
    \  }\n    matrix<T> &operator-=(const matrix<T> &a) {\n        this->table -=\
    \ a.table;\n        return *this;\n    }\n    matrix<T> &operator*=(const T &a)\
    \ {\n        this->table *= a;\n        return *this;\n    }\n    matrix<T> &operator*=(const\
    \ matrix<T> &a) {\n        assert(W == a.H);\n        matrix<T> a_t(a), ret(H,\
    \ a.W);\n        a_t.transpose();\n        for (int i = 0; i < H; i++) {\n   \
    \         for (int j = 0; j < a_t.H; j++) {\n                ret.table[i][j] =\
    \ (table[i] * a_t.table[j]).sum();\n            }\n        }\n        *this =\
    \ std::move(ret);\n        return *this;\n    }\n    matrix<T> &operator/=(const\
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
    \ long n) { return matrix<T>(*this) ^= n; }\n    friend std::istream &operator>>(std::istream\
    \ &is, matrix<T> &mt) {\n        for (auto &arr : mt.table)\n            for (auto\
    \ &x : arr)\n                is >> x;\n        return is;\n    }\n    T &operator()(int\
    \ h, int w) {\n        assert(0 <= h && h < H && 0 <= w && w <= W);\n        return\
    \ table[h][w];\n    }\n\n    /**\n     * @brief \u30B5\u30A4\u30BA n \u306E\u5358\
    \u4F4D\u884C\u5217\u3002\n     */\n    static matrix<T> E(int N) {\n        matrix<T>\
    \ ret(N, N);\n        for (int i = 0; i < N; i++)\n            ret.table[i][i]\
    \ = 1;\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include <assert.h>\n\n#include <iostream>\n#include <utility>\n\
    #include <valarray>\n#include <vector>\n\ntemplate <class T> class matrix {\n\
    \  private:\n    int H, W;\n    std::valarray<std::valarray<T>> table;\n\n   \
    \ enum rowtrans_operation_name { SCALE, SWAP, ADD };\n    struct rowtrans_operation\
    \ {\n        int op, tar, res;\n        T scl;\n    };\n    using operations_history\
    \ = std::vector<rowtrans_operation>;\n\n  public:\n    matrix() = default;\n \
    \   matrix(int _H, int _W, T val = 0)\n        : H(_H), W(_W), table(std::valarray<T>(val,\
    \ _W), _H) {}\n    matrix(const std::vector<std::vector<T>> &vv)\n        : H(vv.size()),\
    \ W(vv[0].size()), table(std::valarray<T>(W), H) {\n        for (int i = 0; i\
    \ < H; i++)\n            for (int j = 0; j < W; j++)\n                table[i][j]\
    \ = vv[i][j];\n    }\n    matrix(const std::valarray<std::valarray<T>> &vv)\n\
    \        : H(vv.size()), W(vv[0].size()), table(vv) {}\n\n    /**\n     * @brief\
    \ \u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002\n     * @param\
    \ val \u62E1\u5F35\u90E8\u5206\u306E\u5024\n     */\n    void resize(int _H, int\
    \ _W, T val = 0) {\n        H = _H, W = _W;\n        table.resize(_H, std::valarray<T>(val,\
    \ _H));\n    }\n    int size_H() const { return H; }\n    int size_W() const {\
    \ return W; }\n    void transpose() {\n        matrix<T> ret(W, H);\n        for\
    \ (int i = 0; i < H; i++)\n            for (int j = 0; j < W; j++)\n         \
    \       ret.table[j][i] = table[i][j];\n        *this = std::move(ret);\n    }\n\
    \n    void row_assign(int i, const std::valarray<T> &row) {\n        assert(W\
    \ == (int)row.size());\n        table[i] = std::move(row);\n    }\n\n    void\
    \ row_swap(int i, int j) {\n        assert(0 <= i && i < H);\n        assert(0\
    \ <= j && j < H);\n        table[i].swap(table[j]);\n    }\n\n    /**\n     *\
    \ @attention O(n^3)\n     * @attention \u6574\u6570\u578B\u3067\u306F\u6B63\u3057\
    \u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002double \u3084 fraction \u3092\u4F7F\
    \u3046\u3053\u3068\u3002\n     * @attention \u67A2\u8EF8\u9078\u3073\u3092\u3057\
    \u3066\u3044\u306A\u3044\u306E\u3067 double \u3067\u306F\u8AA4\u5DEE\u304C\u51FA\
    \u308B\u304B\u3082\u3002\n     */\n    operations_history sweep_method() {\n \
    \       operations_history hist;\n        T ret = 1;\n        for (int h = 0,\
    \ w = 0; h < H && w < W; w++) {\n            if (table[h][w] == 0) {\n       \
    \         for (int piv = h + 1; piv < H; piv++) {\n                    if (table[piv][w]\
    \ != 0) {\n                        hist.push_back({SWAP, h, piv, 0});\n      \
    \                  row_swap(h, piv);\n                        break;\n       \
    \             }\n                }\n                if (table[h][w] == 0) {\n\
    \                    continue;\n                }\n            }\n           \
    \ T inv = 1 / table[h][w];\n            hist.push_back({SCALE, -1, w, inv});\n\
    \            table[h] *= inv;\n            for (int j = h + 1; j < H; j++) {\n\
    \                hist.push_back({ADD, h, j, -table[j][w]});\n                table[j]\
    \ -= table[h] * table[j][w];\n            }\n            h++;\n        }\n   \
    \     return hist;\n    }\n\n    int rank() {\n        auto U(*this);\n      \
    \  U.sweep_method();\n        int r = 0;\n        for (int i = 0; i < H; ++i)\
    \ {\n            for (int j = i; j < W; ++j) {\n                if (U.table[i][j]\
    \ != 0) {\n                    r++;\n                    break;\n            \
    \    }\n            }\n        }\n        return r;\n    }\n\n    T determinant()\
    \ const {\n        assert(H == W);\n        matrix<T> U(*this);\n        T det\
    \ = 1;\n        auto hist = U.sweep_method();\n        if (U.table[H - 1][H -\
    \ 1] == 0)\n            return 0;\n        for (auto &[op, tar, res, scl] : hist)\
    \ {\n            switch (op) {\n            case SCALE:\n                det /=\
    \ scl;\n                break;\n            case SWAP:\n                det *=\
    \ -1;\n                break;\n            }\n        }\n        return det;\n\
    \    }\n\n    std::vector<T> solve_system_of_equations(const std::vector<T> &y)\
    \ {\n        assert(H == W);\n        std::vector<T> x(y);\n        matrix<T>\
    \ U(*this);\n        auto hist = U.sweep_method();\n        if (U.table[H - 1][H\
    \ - 1] == 0)\n            return {};\n\n        for (auto &[op, tar, res, scl]\
    \ : hist) {\n            switch (op) {\n            case SCALE:\n            \
    \    x[res] *= scl;\n                break;\n            case SWAP:\n        \
    \        std::swap(x[tar], x[res]);\n                break;\n            case\
    \ ADD:\n                x[res] += x[tar] * scl;\n                break;\n    \
    \        }\n        }\n\n        for (int i = H - 1; i >= 0; --i) {\n        \
    \    for (int j = 0; j < i; ++j) {\n                x[j] -= U.table[j][i] * x[i];\n\
    \            }\n        }\n        return x;\n    }\n\n    matrix<T> inverse()\
    \ {\n        assert(H == W);\n        matrix<T> INV(matrix<T>::E(H)), U(*this);\n\
    \        auto hist = U.sweep_method();\n        if (U.table[H - 1][H - 1] == 0)\n\
    \            return matrix<T>(0, 0);\n\n        for (auto &[op, tar, res, scl]\
    \ : hist) {\n            switch (op) {\n            case SCALE:\n            \
    \    INV.table[res] *= scl;\n                break;\n            case SWAP:\n\
    \                std::swap(INV.table[tar], INV.table[res]);\n                break;\n\
    \            case ADD:\n                INV.table[res] += INV.table[tar] * scl;\n\
    \                break;\n            }\n        }\n\n        for (int i = H -\
    \ 1; i >= 0; --i) {\n            for (int j = 0; j < i; ++j) {\n             \
    \   INV.table[j] -= INV.table[i] * U.table[j][i];\n            }\n        }\n\
    \        return INV;\n    }\n\n    void print() const {\n        for (int i =\
    \ 0; i < H; i++) {\n            for (int j = 0; j < W; j++) {\n              \
    \  std::cout << table[i][j] << (j == W - 1 ? \"\" : \" \");\n            }\n \
    \           std::cout << std::endl;\n        }\n    }\n\n    matrix<T> &operator+=(const\
    \ matrix<T> &a) {\n        this->table += a.table;\n        return *this;\n  \
    \  }\n    matrix<T> &operator-=(const matrix<T> &a) {\n        this->table -=\
    \ a.table;\n        return *this;\n    }\n    matrix<T> &operator*=(const T &a)\
    \ {\n        this->table *= a;\n        return *this;\n    }\n    matrix<T> &operator*=(const\
    \ matrix<T> &a) {\n        assert(W == a.H);\n        matrix<T> a_t(a), ret(H,\
    \ a.W);\n        a_t.transpose();\n        for (int i = 0; i < H; i++) {\n   \
    \         for (int j = 0; j < a_t.H; j++) {\n                ret.table[i][j] =\
    \ (table[i] * a_t.table[j]).sum();\n            }\n        }\n        *this =\
    \ std::move(ret);\n        return *this;\n    }\n    matrix<T> &operator/=(const\
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
    \ long n) { return matrix<T>(*this) ^= n; }\n    friend std::istream &operator>>(std::istream\
    \ &is, matrix<T> &mt) {\n        for (auto &arr : mt.table)\n            for (auto\
    \ &x : arr)\n                is >> x;\n        return is;\n    }\n    T &operator()(int\
    \ h, int w) {\n        assert(0 <= h && h < H && 0 <= w && w <= W);\n        return\
    \ table[h][w];\n    }\n\n    /**\n     * @brief \u30B5\u30A4\u30BA n \u306E\u5358\
    \u4F4D\u884C\u5217\u3002\n     */\n    static matrix<T> E(int N) {\n        matrix<T>\
    \ ret(N, N);\n        for (int i = 0; i < N; i++)\n            ret.table[i][i]\
    \ = 1;\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix.hpp
  requiredBy:
  - graph/graph.hpp
  - graph/traveling_salesman.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/doubling.hpp
  - graph/is_isomorphic.hpp
  - graph/lowest_common_ancestor.hpp
  - other/random.hpp
  timestamp: '2023-07-31 19:01:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/grl-2-a.test.cpp
  - test/shortest_path.test.cpp
  - test/grl-5-c.test.cpp
  - test/grl-5-a.test.cpp
  - test/grl-1-c.test.cpp
  - test/manhattan-mst.test.cpp
  - test/grl-3-b.test.cpp
  - test/jsc2021-g.test.cpp
  - test/grl-1-a.test.cpp
  - test/itp1-t-d.test.cpp
  - test/grl-3-a.test.cpp
documentation_of: math/matrix.hpp
layout: document
redirect_from:
- /library/math/matrix.hpp
- /library/math/matrix.hpp.html
title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
---
