---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/union_find.hpp
    title: "\u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059"
  - icon: ':question:'
    path: graph/edge.hpp
    title: graph/edge.hpp
  - icon: ':question:'
    path: math/matrix.hpp
    title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':warning:'
    path: graph/doubling.hpp
    title: graph/doubling.hpp
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
    document_title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\
      \u3002"
    links: []
  bundledCode: "#line 2 \"graph/graph.hpp\"\n#include <algorithm>\n#include <assert.h>\n\
    #include <queue>\n#include <stack>\n#include <tuple>\n#include <vector>\n\n#line\
    \ 3 \"data_structure/union_find.hpp\"\n\n#line 6 \"data_structure/union_find.hpp\"\
    \n\nclass union_find {\n  private:\n    int N;\n    mutable std::vector<int> par;\n\
    \    std::vector<int> nxt;\n    int group_num; // \u96C6\u5408\u306E\u6570\n\n\
    \  public:\n    union_find() : N(0) {}\n    union_find(int n) : N(n), par(n, -1),\
    \ nxt(n), group_num(n) {\n        std::iota(nxt.begin(), nxt.end(), 0);\n    }\n\
    \n    /**\n     * @brief \u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059\n\
    \     * @attention \u5C0F\u3055\u304F\u306F\u3067\u304D\u306A\u3044\n     */\n\
    \    void expand(int n) {\n        if (n <= N)\n            return;\n        par.resize(n,\
    \ -1);\n        nxt.resize(n);\n        for (int i = N; i < n; ++i)\n        \
    \    nxt[i] = i;\n        group_num += n - N;\n        N = n;\n    }\n\n    int\
    \ leader(int x) const {\n        return (par[x] < 0 ? x : par[x] = leader(par[x]));\n\
    \    }\n\n    bool same(int x, int y) const { return leader(x) == leader(y); }\n\
    \n    bool merge(int x, int y) {\n        if ((x = leader(x)) == (y = leader(y)))\n\
    \            return false;\n        if (-par[x] > -par[y])\n            std::swap(x,\
    \ y);\n\n        par[x] += par[y];\n        par[y] = x;\n        std::swap(nxt[x],\
    \ nxt[y]);\n        group_num--;\n        return true;\n    }\n\n    /**\n   \
    \  * @brief x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\u30D7\u306E\u30B5\u30A4\
    \u30BA\u3092\u8FD4\u3059\n     */\n    int size(int x) const { return -par[leader(x)];\
    \ }\n\n    /**\n     * @brief \u3059\u3079\u3066\u306E\u30CE\u30FC\u30C9\u306E\
    \u6570\n     */\n    int size() const { return N; }\n\n    std::vector<int> contained_group(int\
    \ x) const {\n        std::vector<int> ret{x};\n        for (int cu = nxt[x];\
    \ cu != ret[0]; cu = nxt[cu])\n            ret.push_back(cu);\n        return\
    \ ret;\n    }\n\n    int count_groups() const { return group_num; }\n\n    std::vector<std::vector<int>>\
    \ all_groups() const {\n        std::vector<std::vector<int>> result;\n      \
    \  result.reserve(group_num);\n        std::vector<bool> used(N, false);\n   \
    \     for (int i = 0; i < N; ++i) {\n            if (!used[i]) {\n           \
    \     result.emplace_back(contained_group(i));\n                for (int x : result.back())\
    \ {\n                    used[x] = true;\n                }\n            }\n \
    \       }\n        return result;\n    }\n};\n#line 3 \"math/matrix.hpp\"\n\n\
    #include <iostream>\n#include <valarray>\n#line 7 \"math/matrix.hpp\"\n\ntemplate\
    \ <class T> class matrix {\n  private:\n    int H, W;\n    std::valarray<std::valarray<T>>\
    \ table;\n\n  public:\n    matrix() = default;\n    matrix(int _H, int _W, T val\
    \ = 0)\n        : H(_H), W(_W), table(std::valarray<T>(val, _W), _H) {}\n    matrix(const\
    \ std::vector<std::vector<T>> &vv)\n        : H(vv.size()), W(vv[0].size()), table(std::valarray<T>(W),\
    \ H) {\n        for (int i = 0; i < H; i++)\n            for (int j = 0; j < W;\
    \ j++)\n                table[i][j] = vv[i][j];\n    }\n    matrix(const std::valarray<std::valarray<T>>\
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
    };\n#line 3 \"graph/edge.hpp\"\n\nnamespace internal {\ntemplate <class DERIVED,\
    \ class WEIGHT> struct _base_edge {\n    int from;\n    int to;\n    WEIGHT cost;\n\
    \    int id;\n    _base_edge() {}\n    _base_edge(int _from, int _to, WEIGHT _cost,\
    \ int _id)\n        : from(_from), to(_to), cost(_cost), id(_id) {}\n\n    friend\
    \ bool operator>(const _base_edge &e1, const _base_edge &e) {\n        return\
    \ e1.compare(e) > 0;\n    }\n    friend bool operator>=(const _base_edge &e1,\
    \ const _base_edge &e) {\n        return e1.compare(e) >= 0;\n    }\n    friend\
    \ bool operator<(const _base_edge &e1, const _base_edge &e) {\n        return\
    \ e1.compare(e) < 0;\n    }\n    friend bool operator<=(const _base_edge &e1,\
    \ const _base_edge &e) {\n        return e1.compare(e) <= 0;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os,\n                               \
    \     const _base_edge<DERIVED, WEIGHT> &e) {\n        e.print(os);\n        return\
    \ os;\n    }\n    _base_edge &operator=(const _base_edge &e) = default;\n\n  \
    \  virtual ~_base_edge() = default;\n\n    operator int() const { return to; }\n\
    \n  protected:\n    virtual void print(std::ostream &os) const = 0;\n    virtual\
    \ int compare(const _base_edge &e) const = 0;\n};\n} // namespace internal\n\n\
    template <class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT> {\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n\
    \n  protected:\n    void print(std::ostream &os) const override {\n        os\
    \ << this->from << \" \" << this->to << \" \" << this->cost;\n    }\n    int compare(\n\
    \        const internal::_base_edge<edge<WEIGHT>, WEIGHT> &e) const override {\n\
    \        if (this->cost == e.cost) {\n            if (this->from == e.from)\n\
    \                return this->to - e.to;\n            return this->from - e.from;\n\
    \        }\n        return this->cost - e.cost;\n    }\n};\n\ntemplate <> struct\
    \ edge<int> : public internal::_base_edge<edge<int>, int> {\n    static inline\
    \ const int cost = 1;\n    using internal::_base_edge<edge<int>, int>::_base_edge;\n\
    \    edge(int _from, int _to, int _id)\n        : _base_edge<edge<int>, int>(_from,\
    \ _to, 0, _id) {}\n\n  protected:\n    void print(std::ostream &os) const override\
    \ {\n        os << this->from << \" \" << this->to;\n    }\n    int compare(const\
    \ internal::_base_edge<edge<int>, int> &e) const override {\n        if (this->from\
    \ == e.from)\n            return this->to - e.to;\n        return this->from -\
    \ e.from;\n    }\n};\n#line 12 \"graph/graph.hpp\"\n\n/**\n * @brief \u30B0\u30E9\
    \u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002\n * @tparam WEIGHT\
    \ int \u306A\u3089\u91CD\u307F\u306A\u3057\u3001\u305D\u3046\u3067\u306A\u3044\
    \u306A\u3089\u91CD\u307F\u3064\u304D\u30B0\u30E9\u30D5\n * @tparam is_directed\
    \ \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3068\u3046\u304B\n */\ntemplate <typename\
    \ WEIGHT, bool is_directed> class graph {\n  private:\n    int N;\n    std::vector<std::vector<edge<WEIGHT>>>\
    \ G;\n    std::vector<edge<WEIGHT>> E;\n    union_find uf;\n    WEIGHT W = 0;\n\
    \n    mutable std::vector<bool> visited; // dfs / bfs \u306E\u305F\u3081\u306E\
    \u9818\u57DF\n    bool forest_flag = true;\n\n  public:\n    graph() : N(0){};\n\
    \    graph(int n) : N(n), G(n), uf(n), visited(n){};\n\n    /**\n     * @brief\
    \ \u30CE\u30FC\u30C9\u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\u3059\n\
    \     * @param n \u30B5\u30A4\u30BA\n     * @attention \u4ECA\u306E\u30CE\u30FC\
    \u30C9\u6570\u3088\u308A\u5C0F\u3055\u3044\u6570\u3092\u6E21\u3057\u305F\u3068\
    \u304D\u3001\u5909\u5316\u306A\u3057\n     */\n    void expand(int n) {\n    \
    \    if (n <= N)\n            return;\n        N = n;\n        G.resize(n);\n\
    \        uf.expand(n);\n        visited.resize(n);\n    }\n\n    /**\n     * @return\
    \ \u30CE\u30FC\u30C9\u306E\u6570\n     */\n    int count_nodes() const { return\
    \ N; }\n\n    /**\n     * @return \u8FBA\u306E\u6570\n     */\n    int count_edges()\
    \ const { return E.size(); }\n\n    /**\n     * @param n \u30CE\u30FC\u30C9\u756A\
    \u53F7\n     * @return \u30CE\u30FC\u30C9 n \u304B\u3089\u306E\u96A3\u63A5\u9802\
    \u70B9\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\n     */\n    const std::vector<edge<WEIGHT>>\
    \ &operator[](int n) const { return G[n]; }\n\n    /**\n     * @return \u30B0\u30E9\
    \u30D5\u5168\u4F53\u306E\u8FBA\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\
    \n     */\n    const std::vector<edge<WEIGHT>> &edges() const { return E; }\n\n\
    \    /**\n     * @param x \u30CE\u30FC\u30C9\u756A\u53F7\n     * @param y \u30CE\
    \u30FC\u30C9\u756A\u53F7\n     * @return x, y \u304C\u9023\u7D50\u304B\u3069\u3046\
    \u304B\n     */\n    bool are_connected(int x, int y) const { return uf.same(x,\
    \ y); }\n\n    /**\n     * @return \u9023\u7D50\u6210\u5206\u306E\u6570\n    \
    \ */\n    int count_connected_components() const { return uf.count_groups(); }\n\
    \n    /**\n     * @return \u9023\u7D50\u6210\u5206\u306E\u30EA\u30B9\u30C8\u306E\
    \u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>> weakly_connected_components()\
    \ const {\n        return uf.all_groups();\n    }\n\n    /**\n     * @return \u6728\
    \u304B\n     */\n    bool is_tree() const { return forest_flag && uf.count_groups()\
    \ == 1; }\n\n    /**\n     * @return \u68EE\u304B\n     */\n    bool is_forest()\
    \ const { return forest_flag; }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\u306E\
    \u91CD\u307F\n     */\n    WEIGHT weight() const { return W; }\n\n    /**\n  \
    \   * @param e \u8FBA\n     * @attention \u6E21\u3057\u305F\u8FBA\u306E id \u306F\
    \u4FDD\u6301\u3055\u308C\u308B\n     */\n    void add_edge(edge<WEIGHT> e) {\n\
    \        forest_flag &= uf.merge(e.from, e.to);\n        E.emplace_back(e);\n\
    \        G[e.from].emplace_back(e);\n        if (!is_directed && e.from != e.to)\
    \ {\n            std::swap(e.from, e.to);\n            G[e.from].emplace_back(e);\n\
    \        }\n        W += e.cost;\n    }\n\n    /**\n     * @attention \u8FBA\u306E\
    \ id \u306F\u3001(\u73FE\u5728\u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\
    \u632F\u3089\u308C\u308B\n     * @attention WEIGHT \u304C int \u3060\u3068\u30A8\
    \u30E9\u30FC\n     */\n    void add_edge(int from, int to, WEIGHT cost) {\n  \
    \      static_assert(!std::is_same<WEIGHT, int>::value);\n        if constexpr\
    \ (!is_directed)\n            if (from > to)\n                std::swap(from,\
    \ to);\n        add_edge(edge<WEIGHT>(from, to, cost, E.size()));\n    }\n\n \
    \   /**\n     * @attention \u8FBA\u306E id \u306F\u3001(\u73FE\u5728\u306E\u8FBA\
    \u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\u3089\u308C\u308B\n     * @attention\
    \ WEIGHT \u304C int \u4EE5\u5916\u3060\u3068\u30A8\u30E9\u30FC\n     */\n    void\
    \ add_edge(int from, int to) {\n        static_assert(std::is_same<WEIGHT, int>::value);\n\
    \        if constexpr (!is_directed)\n            if (from > to)\n           \
    \     std::swap(from, to);\n        add_edge(edge<int>(from, to, E.size()));\n\
    \    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\u7D50\u306A\u30B0\
    \u30E9\u30D5\u306B\u5206\u3051\u3066\u30EA\u30B9\u30C8\u306B\u3057\u3066\u8FD4\
    \u3059\n     * @example auto[Gs, gr, nd] = G.decompose();\n     * @returns\n \
    \    * 1.\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\n     * 2.\u5404\u30CE\u30FC\
    \u30C9\u304C\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\u306E\u4F55\u756A\u76EE\
    \u306B\u5C5E\u3059\u308B\u304B\n     * 3.\u5404\u30CE\u30FC\u30C9\u304C\u30B0\u30E9\
    \u30D5\u306E\u3069\u306E\u30CE\u30FC\u30C9\u306B\u306A\u3063\u3066\u3044\u308B\
    \u304B\n     */\n    std::tuple<std::vector<graph>, std::vector<int>, std::vector<int>>\n\
    \    decompose() const {\n        std::vector<graph> Gs(uf.count_groups());\n\
    \        std::vector<std::vector<int>> groups(uf.all_groups());\n        std::vector<int>\
    \ group_id(N), node_id(N);\n        for (int i = 0; i < (int)groups.size(); i++)\
    \ {\n            Gs[i].expand(groups[i].size());\n            for (int j = 0;\
    \ j < (int)groups[i].size(); j++) {\n                group_id[groups[i][j]] =\
    \ i;\n                node_id[groups[i][j]] = j;\n            }\n        }\n \
    \       for (auto e : E) {\n            int id = group_id[e.from];\n         \
    \   e.from = node_id[e.from];\n            e.to = node_id[e.to];\n           \
    \ Gs[id].add_edge(e);\n        }\n        return std::make_tuple(Gs, group_id,\
    \ node_id);\n    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u96A3\u63A5\
    \u884C\u5217\u306B\u5909\u63DB\n     * @param invalid \u8FBA\u306E\u306A\u3044\
    \u3068\u304D\u306E\u5024\n     * @attention G \u306B\u81EA\u5DF1\u30EB\u30FC\u30D7\
    \u304C\u542B\u307E\u308C\u3066\u3044\u306A\u3044\u9650\u308A\u3001\u5BFE\u89D2\
    \u6210\u5206\u306F 0\n     */\n    matrix<WEIGHT> to_adjajency(WEIGHT invalid\
    \ = 0) const {\n        matrix<WEIGHT> ret(N, N, invalid);\n        for (int i\
    \ = 0; i < N; i++)\n            ret[i][i] = 0;\n        for (int i = 0; i < N;\
    \ i++)\n            for (auto &e : G[i])\n                ret[i][e.to] = e.cost;\n\
    \        return ret;\n    }\n\n    /**\n     * @brief \u884C\u304D\u304C\u3051\
    \u9806\u306B bfs\n     */\n    std::vector<int> preorder(int start) const {\n\
    \        std::vector<int> result;\n        std::stack<std::pair<int, int>> stk;\n\
    \        for (int x : uf.contained_group(start))\n            visited[x] = false;\n\
    \        visited[start] = true;\n        stk.push({start, 0});\n\n        while\
    \ (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n            if (idx\
    \ == 0)\n                result.push_back(cu);\n            if (idx == G[cu].size())\
    \ {\n                stk.pop();\n            } else {\n                int to\
    \ = G[cu][idx++];\n                if (!visited[to]) {\n                    visited[to]\
    \ = true;\n                    stk.push({to, 0});\n                }\n       \
    \     }\n        }\n        return result;\n    }\n\n    /**\n     * @brief \u901A\
    \u308A\u304C\u3051\u9806\u306B bfs\n     */\n    std::vector<int> inorder(int\
    \ start) const {\n        std::vector<int> result;\n        std::stack<std::pair<int,\
    \ int>> stk;\n        for (int x : uf.contained_group(start))\n            visited[x]\
    \ = false;\n        visited[start] = true;\n        stk.push({start, 0});\n\n\
    \        while (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n  \
    \          if (idx == G[cu].size()) {\n                stk.pop();\n          \
    \      result.push_back(cu);\n            } else {\n                int to = G[cu][idx++];\n\
    \                if (!visited[to]) {\n                    visited[to] = true;\n\
    \                    stk.push({to, 0});\n                    result.push_back(cu);\n\
    \                }\n            }\n        }\n        return result;\n    }\n\n\
    \    /**\n     * @brief \u5E30\u308A\u304C\u3051\u9806\u306B bfs\n     */\n  \
    \  std::vector<int> postorder(int start) const {\n        std::vector<int> result;\n\
    \        std::stack<std::pair<int, int>> stk;\n        for (int x : uf.contained_group(start))\n\
    \            visited[x] = false;\n        visited[start] = true;\n        stk.push({start,\
    \ 0});\n\n        while (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n\
    \            if (idx == G[cu].size()) {\n                stk.pop();\n        \
    \        result.push_back(cu);\n            } else {\n                int to =\
    \ G[cu][idx++];\n                if (!visited[to]) {\n                    visited[to]\
    \ = true;\n                    stk.push({to, 0});\n                }\n       \
    \     }\n        }\n        return result;\n    }\n\n  private:\n    using PAIR\
    \ = std::pair<WEIGHT, int>;\n    using Dijkstra_queue =\n        std::priority_queue<PAIR,\
    \ std::vector<PAIR>, std::greater<PAIR>>;\n\n    void run_bfs(std::vector<int>\
    \ &dist, std::queue<int> &q) const {\n        while (!q.empty()) {\n         \
    \   int cu = q.front();\n            q.pop();\n            for (auto &e : G[cu])\
    \ {\n                if (dist[e.to] != std::numeric_limits<WEIGHT>::max())\n \
    \                   continue;\n                dist[e.to] = dist[cu] + 1;\n  \
    \              q.push(e.to);\n            }\n        }\n    }\n\n    void run_Dijkstra(std::vector<WEIGHT>\
    \ &dist, Dijkstra_queue &q) const {\n        while (!q.empty()) {\n          \
    \  WEIGHT cur_dist = q.top().first;\n            int cu = q.top().second;\n  \
    \          q.pop();\n\n            if (visited[cu])\n                continue;\n\
    \            visited[cu] = true;\n\n            for (auto &e : G[cu]) {\n    \
    \            WEIGHT alt = cur_dist + e.cost;\n                if (dist[e.to] <=\
    \ alt)\n                    continue;\n                dist[e.to] = alt;\n   \
    \             q.push({alt, e.to});\n            }\n        }\n    }\n\n  public:\n\
    \    /**\n     * @brief \u6700\u77ED\u8DDD\u96E2\u3092\u8A08\u7B97\u3059\u308B\
    \n     * @param start_node \u59CB\u70B9\n     * @param invalid \u5230\u9054\u4E0D\
    \u80FD\u306A\u9802\u70B9\u306B\u683C\u7D0D\u3055\u308C\u308B\u5024\n     * @return\
    \ \u5404\u30CE\u30FC\u30C9\u307E\u3067\u306E\u6700\u77ED\u8DDD\u96E2\u306E\u30EA\
    \u30B9\u30C8\n     */\n    std::vector<WEIGHT> calculate_shortest_distances(int\
    \ start_node,\n                                                     WEIGHT invalid)\
    \ const {\n        std::vector<WEIGHT> dist(N, std::numeric_limits<WEIGHT>::max());\n\
    \        dist[start_node] = 0;\n\n        if constexpr (std::is_same<WEIGHT, int>::value)\
    \ {\n            // BFS algorithm\n            std::queue<int> q;\n          \
    \  q.push(start_node);\n            run_bfs(dist, q);\n        } else {\n    \
    \        // Dijkstra's algorithm\n            Dijkstra_queue q;\n            q.push({0,\
    \ start_node});\n            for (int x : uf.contained_group(start_node))\n  \
    \              visited[x] = false;\n            run_Dijkstra(dist, q);\n     \
    \   }\n\n        for (auto &x : dist)\n            if (x == std::numeric_limits<WEIGHT>::max())\n\
    \                x = invalid;\n        return dist;\n    }\n\n    WEIGHT diameter()\
    \ const {\n        static_assert(!is_directed);\n        assert(is_tree());\n\
    \        std::vector<WEIGHT> dist(calculate_shortest_distances(0, -1));\n    \
    \    dist = calculate_shortest_distances(\n            std::max_element(dist.begin(),\
    \ dist.end()) - dist.begin(), -1);\n        return *std::max_element(dist.begin(),\
    \ dist.end());\n    }\n\n    graph reverse() const {\n        if constexpr (!is_directed)\
    \ {\n            return *this;\n        } else {\n            graph ret(N);\n\
    \            for (auto e : E) {\n                std::swap(e.from, e.to);\n  \
    \              ret.add_edge(e);\n            }\n            return ret;\n    \
    \    }\n    }\n\n    std::vector<int> topological_sort() {\n        static_assert(is_directed);\n\
    \        std::vector<int> indeg(N, 0), sorted;\n        for (int to : E)\n   \
    \         indeg[to]++;\n\n        std::queue<int> q;\n        for (int i = 0;\
    \ i < N; i++)\n            if (!indeg[i])\n                q.push(i);\n      \
    \  while (!q.empty()) {\n            int cu = q.front();\n            q.pop();\n\
    \            for (int to : G[cu]) {\n                if (!--indeg[to])\n     \
    \               q.push(to);\n            }\n            sorted.push_back(cu);\n\
    \        }\n        return sorted;\n    }\n\n    /**\n     * @return \u6700\u5C0F\
    \u5168\u57DF\u68EE\n     */\n    graph minimum_spanning_tree() const {\n     \
    \   static_assert(!is_directed);\n        graph ret(N);\n        std::vector<edge<WEIGHT>>\
    \ tmp(edges());\n        std::sort(tmp.begin(), tmp.end());\n        for (auto\
    \ &e : tmp)\n            if (!ret.are_connected(e.from, e.to))\n             \
    \   ret.add_edge(e);\n        return ret;\n    }\n\n    void print() const {\n\
    \        std::cout << this->N << \" \" << this->E.size() << std::endl;\n     \
    \   for (const edge<WEIGHT> &e : this->E)\n            std::cout << e << std::endl;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <assert.h>\n#include <queue>\n\
    #include <stack>\n#include <tuple>\n#include <vector>\n\n#include \"../data_structure/union_find.hpp\"\
    \n#include \"../math/matrix.hpp\"\n#include \"edge.hpp\"\n\n/**\n * @brief \u30B0\
    \u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002\n * @tparam\
    \ WEIGHT int \u306A\u3089\u91CD\u307F\u306A\u3057\u3001\u305D\u3046\u3067\u306A\
    \u3044\u306A\u3089\u91CD\u307F\u3064\u304D\u30B0\u30E9\u30D5\n * @tparam is_directed\
    \ \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3068\u3046\u304B\n */\ntemplate <typename\
    \ WEIGHT, bool is_directed> class graph {\n  private:\n    int N;\n    std::vector<std::vector<edge<WEIGHT>>>\
    \ G;\n    std::vector<edge<WEIGHT>> E;\n    union_find uf;\n    WEIGHT W = 0;\n\
    \n    mutable std::vector<bool> visited; // dfs / bfs \u306E\u305F\u3081\u306E\
    \u9818\u57DF\n    bool forest_flag = true;\n\n  public:\n    graph() : N(0){};\n\
    \    graph(int n) : N(n), G(n), uf(n), visited(n){};\n\n    /**\n     * @brief\
    \ \u30CE\u30FC\u30C9\u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\u3059\n\
    \     * @param n \u30B5\u30A4\u30BA\n     * @attention \u4ECA\u306E\u30CE\u30FC\
    \u30C9\u6570\u3088\u308A\u5C0F\u3055\u3044\u6570\u3092\u6E21\u3057\u305F\u3068\
    \u304D\u3001\u5909\u5316\u306A\u3057\n     */\n    void expand(int n) {\n    \
    \    if (n <= N)\n            return;\n        N = n;\n        G.resize(n);\n\
    \        uf.expand(n);\n        visited.resize(n);\n    }\n\n    /**\n     * @return\
    \ \u30CE\u30FC\u30C9\u306E\u6570\n     */\n    int count_nodes() const { return\
    \ N; }\n\n    /**\n     * @return \u8FBA\u306E\u6570\n     */\n    int count_edges()\
    \ const { return E.size(); }\n\n    /**\n     * @param n \u30CE\u30FC\u30C9\u756A\
    \u53F7\n     * @return \u30CE\u30FC\u30C9 n \u304B\u3089\u306E\u96A3\u63A5\u9802\
    \u70B9\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\n     */\n    const std::vector<edge<WEIGHT>>\
    \ &operator[](int n) const { return G[n]; }\n\n    /**\n     * @return \u30B0\u30E9\
    \u30D5\u5168\u4F53\u306E\u8FBA\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\
    \n     */\n    const std::vector<edge<WEIGHT>> &edges() const { return E; }\n\n\
    \    /**\n     * @param x \u30CE\u30FC\u30C9\u756A\u53F7\n     * @param y \u30CE\
    \u30FC\u30C9\u756A\u53F7\n     * @return x, y \u304C\u9023\u7D50\u304B\u3069\u3046\
    \u304B\n     */\n    bool are_connected(int x, int y) const { return uf.same(x,\
    \ y); }\n\n    /**\n     * @return \u9023\u7D50\u6210\u5206\u306E\u6570\n    \
    \ */\n    int count_connected_components() const { return uf.count_groups(); }\n\
    \n    /**\n     * @return \u9023\u7D50\u6210\u5206\u306E\u30EA\u30B9\u30C8\u306E\
    \u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>> weakly_connected_components()\
    \ const {\n        return uf.all_groups();\n    }\n\n    /**\n     * @return \u6728\
    \u304B\n     */\n    bool is_tree() const { return forest_flag && uf.count_groups()\
    \ == 1; }\n\n    /**\n     * @return \u68EE\u304B\n     */\n    bool is_forest()\
    \ const { return forest_flag; }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\u306E\
    \u91CD\u307F\n     */\n    WEIGHT weight() const { return W; }\n\n    /**\n  \
    \   * @param e \u8FBA\n     * @attention \u6E21\u3057\u305F\u8FBA\u306E id \u306F\
    \u4FDD\u6301\u3055\u308C\u308B\n     */\n    void add_edge(edge<WEIGHT> e) {\n\
    \        forest_flag &= uf.merge(e.from, e.to);\n        E.emplace_back(e);\n\
    \        G[e.from].emplace_back(e);\n        if (!is_directed && e.from != e.to)\
    \ {\n            std::swap(e.from, e.to);\n            G[e.from].emplace_back(e);\n\
    \        }\n        W += e.cost;\n    }\n\n    /**\n     * @attention \u8FBA\u306E\
    \ id \u306F\u3001(\u73FE\u5728\u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\
    \u632F\u3089\u308C\u308B\n     * @attention WEIGHT \u304C int \u3060\u3068\u30A8\
    \u30E9\u30FC\n     */\n    void add_edge(int from, int to, WEIGHT cost) {\n  \
    \      static_assert(!std::is_same<WEIGHT, int>::value);\n        if constexpr\
    \ (!is_directed)\n            if (from > to)\n                std::swap(from,\
    \ to);\n        add_edge(edge<WEIGHT>(from, to, cost, E.size()));\n    }\n\n \
    \   /**\n     * @attention \u8FBA\u306E id \u306F\u3001(\u73FE\u5728\u306E\u8FBA\
    \u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\u3089\u308C\u308B\n     * @attention\
    \ WEIGHT \u304C int \u4EE5\u5916\u3060\u3068\u30A8\u30E9\u30FC\n     */\n    void\
    \ add_edge(int from, int to) {\n        static_assert(std::is_same<WEIGHT, int>::value);\n\
    \        if constexpr (!is_directed)\n            if (from > to)\n           \
    \     std::swap(from, to);\n        add_edge(edge<int>(from, to, E.size()));\n\
    \    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\u7D50\u306A\u30B0\
    \u30E9\u30D5\u306B\u5206\u3051\u3066\u30EA\u30B9\u30C8\u306B\u3057\u3066\u8FD4\
    \u3059\n     * @example auto[Gs, gr, nd] = G.decompose();\n     * @returns\n \
    \    * 1.\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\n     * 2.\u5404\u30CE\u30FC\
    \u30C9\u304C\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\u306E\u4F55\u756A\u76EE\
    \u306B\u5C5E\u3059\u308B\u304B\n     * 3.\u5404\u30CE\u30FC\u30C9\u304C\u30B0\u30E9\
    \u30D5\u306E\u3069\u306E\u30CE\u30FC\u30C9\u306B\u306A\u3063\u3066\u3044\u308B\
    \u304B\n     */\n    std::tuple<std::vector<graph>, std::vector<int>, std::vector<int>>\n\
    \    decompose() const {\n        std::vector<graph> Gs(uf.count_groups());\n\
    \        std::vector<std::vector<int>> groups(uf.all_groups());\n        std::vector<int>\
    \ group_id(N), node_id(N);\n        for (int i = 0; i < (int)groups.size(); i++)\
    \ {\n            Gs[i].expand(groups[i].size());\n            for (int j = 0;\
    \ j < (int)groups[i].size(); j++) {\n                group_id[groups[i][j]] =\
    \ i;\n                node_id[groups[i][j]] = j;\n            }\n        }\n \
    \       for (auto e : E) {\n            int id = group_id[e.from];\n         \
    \   e.from = node_id[e.from];\n            e.to = node_id[e.to];\n           \
    \ Gs[id].add_edge(e);\n        }\n        return std::make_tuple(Gs, group_id,\
    \ node_id);\n    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u96A3\u63A5\
    \u884C\u5217\u306B\u5909\u63DB\n     * @param invalid \u8FBA\u306E\u306A\u3044\
    \u3068\u304D\u306E\u5024\n     * @attention G \u306B\u81EA\u5DF1\u30EB\u30FC\u30D7\
    \u304C\u542B\u307E\u308C\u3066\u3044\u306A\u3044\u9650\u308A\u3001\u5BFE\u89D2\
    \u6210\u5206\u306F 0\n     */\n    matrix<WEIGHT> to_adjajency(WEIGHT invalid\
    \ = 0) const {\n        matrix<WEIGHT> ret(N, N, invalid);\n        for (int i\
    \ = 0; i < N; i++)\n            ret[i][i] = 0;\n        for (int i = 0; i < N;\
    \ i++)\n            for (auto &e : G[i])\n                ret[i][e.to] = e.cost;\n\
    \        return ret;\n    }\n\n    /**\n     * @brief \u884C\u304D\u304C\u3051\
    \u9806\u306B bfs\n     */\n    std::vector<int> preorder(int start) const {\n\
    \        std::vector<int> result;\n        std::stack<std::pair<int, int>> stk;\n\
    \        for (int x : uf.contained_group(start))\n            visited[x] = false;\n\
    \        visited[start] = true;\n        stk.push({start, 0});\n\n        while\
    \ (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n            if (idx\
    \ == 0)\n                result.push_back(cu);\n            if (idx == G[cu].size())\
    \ {\n                stk.pop();\n            } else {\n                int to\
    \ = G[cu][idx++];\n                if (!visited[to]) {\n                    visited[to]\
    \ = true;\n                    stk.push({to, 0});\n                }\n       \
    \     }\n        }\n        return result;\n    }\n\n    /**\n     * @brief \u901A\
    \u308A\u304C\u3051\u9806\u306B bfs\n     */\n    std::vector<int> inorder(int\
    \ start) const {\n        std::vector<int> result;\n        std::stack<std::pair<int,\
    \ int>> stk;\n        for (int x : uf.contained_group(start))\n            visited[x]\
    \ = false;\n        visited[start] = true;\n        stk.push({start, 0});\n\n\
    \        while (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n  \
    \          if (idx == G[cu].size()) {\n                stk.pop();\n          \
    \      result.push_back(cu);\n            } else {\n                int to = G[cu][idx++];\n\
    \                if (!visited[to]) {\n                    visited[to] = true;\n\
    \                    stk.push({to, 0});\n                    result.push_back(cu);\n\
    \                }\n            }\n        }\n        return result;\n    }\n\n\
    \    /**\n     * @brief \u5E30\u308A\u304C\u3051\u9806\u306B bfs\n     */\n  \
    \  std::vector<int> postorder(int start) const {\n        std::vector<int> result;\n\
    \        std::stack<std::pair<int, int>> stk;\n        for (int x : uf.contained_group(start))\n\
    \            visited[x] = false;\n        visited[start] = true;\n        stk.push({start,\
    \ 0});\n\n        while (!stk.empty()) {\n            auto &[cu, idx] = stk.top();\n\
    \            if (idx == G[cu].size()) {\n                stk.pop();\n        \
    \        result.push_back(cu);\n            } else {\n                int to =\
    \ G[cu][idx++];\n                if (!visited[to]) {\n                    visited[to]\
    \ = true;\n                    stk.push({to, 0});\n                }\n       \
    \     }\n        }\n        return result;\n    }\n\n  private:\n    using PAIR\
    \ = std::pair<WEIGHT, int>;\n    using Dijkstra_queue =\n        std::priority_queue<PAIR,\
    \ std::vector<PAIR>, std::greater<PAIR>>;\n\n    void run_bfs(std::vector<int>\
    \ &dist, std::queue<int> &q) const {\n        while (!q.empty()) {\n         \
    \   int cu = q.front();\n            q.pop();\n            for (auto &e : G[cu])\
    \ {\n                if (dist[e.to] != std::numeric_limits<WEIGHT>::max())\n \
    \                   continue;\n                dist[e.to] = dist[cu] + 1;\n  \
    \              q.push(e.to);\n            }\n        }\n    }\n\n    void run_Dijkstra(std::vector<WEIGHT>\
    \ &dist, Dijkstra_queue &q) const {\n        while (!q.empty()) {\n          \
    \  WEIGHT cur_dist = q.top().first;\n            int cu = q.top().second;\n  \
    \          q.pop();\n\n            if (visited[cu])\n                continue;\n\
    \            visited[cu] = true;\n\n            for (auto &e : G[cu]) {\n    \
    \            WEIGHT alt = cur_dist + e.cost;\n                if (dist[e.to] <=\
    \ alt)\n                    continue;\n                dist[e.to] = alt;\n   \
    \             q.push({alt, e.to});\n            }\n        }\n    }\n\n  public:\n\
    \    /**\n     * @brief \u6700\u77ED\u8DDD\u96E2\u3092\u8A08\u7B97\u3059\u308B\
    \n     * @param start_node \u59CB\u70B9\n     * @param invalid \u5230\u9054\u4E0D\
    \u80FD\u306A\u9802\u70B9\u306B\u683C\u7D0D\u3055\u308C\u308B\u5024\n     * @return\
    \ \u5404\u30CE\u30FC\u30C9\u307E\u3067\u306E\u6700\u77ED\u8DDD\u96E2\u306E\u30EA\
    \u30B9\u30C8\n     */\n    std::vector<WEIGHT> calculate_shortest_distances(int\
    \ start_node,\n                                                     WEIGHT invalid)\
    \ const {\n        std::vector<WEIGHT> dist(N, std::numeric_limits<WEIGHT>::max());\n\
    \        dist[start_node] = 0;\n\n        if constexpr (std::is_same<WEIGHT, int>::value)\
    \ {\n            // BFS algorithm\n            std::queue<int> q;\n          \
    \  q.push(start_node);\n            run_bfs(dist, q);\n        } else {\n    \
    \        // Dijkstra's algorithm\n            Dijkstra_queue q;\n            q.push({0,\
    \ start_node});\n            for (int x : uf.contained_group(start_node))\n  \
    \              visited[x] = false;\n            run_Dijkstra(dist, q);\n     \
    \   }\n\n        for (auto &x : dist)\n            if (x == std::numeric_limits<WEIGHT>::max())\n\
    \                x = invalid;\n        return dist;\n    }\n\n    WEIGHT diameter()\
    \ const {\n        static_assert(!is_directed);\n        assert(is_tree());\n\
    \        std::vector<WEIGHT> dist(calculate_shortest_distances(0, -1));\n    \
    \    dist = calculate_shortest_distances(\n            std::max_element(dist.begin(),\
    \ dist.end()) - dist.begin(), -1);\n        return *std::max_element(dist.begin(),\
    \ dist.end());\n    }\n\n    graph reverse() const {\n        if constexpr (!is_directed)\
    \ {\n            return *this;\n        } else {\n            graph ret(N);\n\
    \            for (auto e : E) {\n                std::swap(e.from, e.to);\n  \
    \              ret.add_edge(e);\n            }\n            return ret;\n    \
    \    }\n    }\n\n    std::vector<int> topological_sort() {\n        static_assert(is_directed);\n\
    \        std::vector<int> indeg(N, 0), sorted;\n        for (int to : E)\n   \
    \         indeg[to]++;\n\n        std::queue<int> q;\n        for (int i = 0;\
    \ i < N; i++)\n            if (!indeg[i])\n                q.push(i);\n      \
    \  while (!q.empty()) {\n            int cu = q.front();\n            q.pop();\n\
    \            for (int to : G[cu]) {\n                if (!--indeg[to])\n     \
    \               q.push(to);\n            }\n            sorted.push_back(cu);\n\
    \        }\n        return sorted;\n    }\n\n    /**\n     * @return \u6700\u5C0F\
    \u5168\u57DF\u68EE\n     */\n    graph minimum_spanning_tree() const {\n     \
    \   static_assert(!is_directed);\n        graph ret(N);\n        std::vector<edge<WEIGHT>>\
    \ tmp(edges());\n        std::sort(tmp.begin(), tmp.end());\n        for (auto\
    \ &e : tmp)\n            if (!ret.are_connected(e.from, e.to))\n             \
    \   ret.add_edge(e);\n        return ret;\n    }\n\n    void print() const {\n\
    \        std::cout << this->N << \" \" << this->E.size() << std::endl;\n     \
    \   for (const edge<WEIGHT> &e : this->E)\n            std::cout << e << std::endl;\n\
    \    }\n};\n"
  dependsOn:
  - data_structure/union_find.hpp
  - math/matrix.hpp
  - graph/edge.hpp
  isVerificationFile: false
  path: graph/graph.hpp
  requiredBy:
  - other/random.hpp
  - graph/lowlink.hpp
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/lowest_common_ancestor.hpp
  - graph/traveling_salesman.hpp
  - graph/doubling.hpp
  - graph/is_isomorphic.hpp
  timestamp: '2023-07-12 15:11:45+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/jsc2021-g.test.cpp
  - test/grl-5-c.test.cpp
  - test/grl-2-a.test.cpp
  - test/grl-3-a.test.cpp
  - test/manhattan-mst.test.cpp
  - test/grl-1-a.test.cpp
  - test/grl-1-c.test.cpp
  - test/grl-3-b.test.cpp
  - test/grl-5-a.test.cpp
documentation_of: graph/graph.hpp
layout: document
redirect_from:
- /library/graph/graph.hpp
- /library/graph/graph.hpp.html
title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
---
