---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/union_find.hpp
    title: "\u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059"
  - icon: ':question:'
    path: graph/Manhattan_minimum_spanning_tree.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
      \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002"
  - icon: ':question:'
    path: graph/edge.hpp
    title: graph/edge.hpp
  - icon: ':question:'
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
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
    PROBLEM: https://judge.yosupo.jp/problem/manhattanmst
    links:
    - https://judge.yosupo.jp/problem/manhattanmst
  bundledCode: "#line 1 \"test/manhattan-mst.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/manhattanmst\"\
    \n#include <bits/stdc++.h>\n#line 4 \"graph/Manhattan_minimum_spanning_tree.hpp\"\
    \n\n#line 5 \"graph/graph.hpp\"\n\n#line 3 \"data_structure/union_find.hpp\"\n\
    \n#line 6 \"data_structure/union_find.hpp\"\n\nclass union_find {\n  private:\n\
    \    int N;\n    std::vector<int> par, group_siz;\n    int group_num; // \u96C6\
    \u5408\u306E\u6570\n\n  public:\n    union_find() : N(0) {}\n    union_find(int\
    \ n) : N(n), par(n, -1), group_siz(n, 1), group_num(n) {}\n\n    /**\n     * @brief\
    \ \u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059\n     * @attention \u5C0F\
    \u3055\u304F\u306F\u3067\u304D\u306A\u3044\n     */\n    void expand(int n) {\n\
    \        if (n <= N)\n            return;\n        N = n;\n        par.resize(n,\
    \ -1);\n        group_siz.resize(n, 1);\n        group_num += n - N;\n    }\n\n\
    \    int leader(int x) {\n        if (par[x] == -1)\n            return x;\n \
    \       else\n            return par[x] = leader(par[x]);\n    }\n\n    bool same(int\
    \ x, int y) { return leader(x) == leader(y); }\n\n    bool merge(int x, int y)\
    \ {\n        x = leader(x);\n        y = leader(y);\n        if (x == y)\n   \
    \         return false;\n        // \u5C0F\u3055\u3044\u307B\u3046\u306B\u7D71\
    \u5408\n        if (group_siz[x] < group_siz[y])\n            std::swap(x, y);\n\
    \        par[y] = x;\n        group_siz[x] += group_siz[y];\n        group_num--;\n\
    \        return true;\n    }\n\n    // x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\
    \u30D7\u306E\u30B5\u30A4\u30BA\u3092\u8FD4\u3059\n    int size(int x) { return\
    \ group_siz[leader(x)]; }\n\n    int count_groups() const { return group_num;\
    \ }\n\n    std::vector<std::vector<int>> groups() {\n        std::vector<std::vector<int>>\
    \ result(N);\n        for (int i = 0; i < N; i++)\n            result[i].reserve(group_siz[i]);\n\
    \        for (int i = 0; i < N; i++)\n            result[leader(i)].push_back(i);\n\
    \        result.erase(std::remove_if(\n                         result.begin(),\
    \ result.end(),\n                         [&](const std::vector<int> &v) { return\
    \ v.empty(); }),\n                     result.end());\n        return result;\n\
    \    }\n};\n#line 3 \"math/matrix.hpp\"\n\n#line 7 \"math/matrix.hpp\"\n\ntemplate\
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
    \    int id;\n    _base_edge(int _from, int _to, WEIGHT _cost, int _id)\n    \
    \    : from(_from), to(_to), cost(_cost), id(_id) {}\n\n    friend bool operator>(const\
    \ _base_edge &e1, const _base_edge &e) {\n        return e1.compare(e) > 0;\n\
    \    }\n    friend bool operator>=(const _base_edge &e1, const _base_edge &e)\
    \ {\n        return e1.compare(e) >= 0;\n    }\n    friend bool operator<(const\
    \ _base_edge &e1, const _base_edge &e) {\n        return e1.compare(e) < 0;\n\
    \    }\n    friend bool operator<=(const _base_edge &e1, const _base_edge &e)\
    \ {\n        return e1.compare(e) <= 0;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os,\n                                    const _base_edge<DERIVED, WEIGHT>\
    \ &e) {\n        e.print(os);\n        return os;\n    }\n    _base_edge &operator=(const\
    \ _base_edge &e) = default;\n\n    virtual ~_base_edge() = default;\n\n    operator\
    \ int() const { return to; }\n\n  protected:\n    virtual void print(std::ostream\
    \ &os) const = 0;\n    virtual int compare(const _base_edge &e) const = 0;\n};\n\
    } // namespace internal\n\ntemplate <class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT> {\n    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0,\
    \ 0) {}\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n\n\
    \  protected:\n    void print(std::ostream &os) const override {\n        os <<\
    \ this->from << \" \" << this->to << \" \" << this->cost;\n    }\n    int compare(\n\
    \        const internal::_base_edge<edge<WEIGHT>, WEIGHT> &e) const override {\n\
    \        if (this->cost == e.cost) {\n            if (this->from == e.from) {\n\
    \                return this->to - e.to;\n            }\n            return this->from\
    \ - e.from;\n        }\n        return this->cost - e.cost;\n    }\n};\n\ntemplate\
    \ <> struct edge<int> : public internal::_base_edge<edge<int>, int> {\n    static\
    \ const int cost = 1;\n    edge() : internal::_base_edge<edge<int>, int>(0, 0,\
    \ 0, 0) {}\n    edge(int _from, int _to, int _id)\n        : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int> &e) const override {\n\
    \        if (this->from == e.from) {\n            return this->to - e.to;\n  \
    \      }\n        return this->from - e.from;\n    }\n};\n#line 9 \"graph/graph.hpp\"\
    \n\n/**\n * @brief \u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\
    \u30B9\u3002\n * @tparam WEIGHT int \u306A\u3089\u91CD\u307F\u306A\u3057\u3001\
    \u305D\u3046\u3067\u306A\u3044\u306A\u3089\u91CD\u307F\u3064\u304D\u30B0\u30E9\
    \u30D5\n * @tparam is_directed \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3068\u3046\
    \u304B\n */\ntemplate <typename WEIGHT, bool is_directed> class graph {\n  private:\n\
    \    int N;\n    std::vector<std::vector<edge<WEIGHT>>> G;\n    std::vector<edge<WEIGHT>>\
    \ E;\n    union_find uf;\n    WEIGHT W = 0;\n\n    void internal_add_edge(edge<WEIGHT>\
    \ e) {\n        uf.merge(e.from, e.to);\n        G[e.from].emplace_back(e);\n\
    \        if (!is_directed && e.from != e.to) {\n            std::swap(e.from,\
    \ e.to);\n            G[e.from].emplace_back(e);\n        }\n        if (!is_directed\
    \ && e.from > e.to)\n            std::swap(e.from, e.to);\n        E.emplace_back(e);\n\
    \        W += e.cost;\n    }\n\n  public:\n    graph() : N(0), G(0), uf(0){};\n\
    \    graph(int n) : N(n), G(n), uf(n){};\n\n    /**\n     * @brief \u30CE\u30FC\
    \u30C9\u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\u3059\n     * @param n\
    \ \u30B5\u30A4\u30BA\n     * @attention \u4ECA\u306E\u30CE\u30FC\u30C9\u6570\u3088\
    \u308A\u5C0F\u3055\u3044\u6570\u3092\u6E21\u3057\u305F\u3068\u304D\u3001\u5909\
    \u5316\u306A\u3057\n     */\n    void expand(int n) {\n        if (n <= N)\n \
    \           return;\n        N = n;\n        G.resize(n);\n        uf.expand(n);\n\
    \    }\n\n    /**\n     * @return \u30CE\u30FC\u30C9\u306E\u6570\n     */\n  \
    \  int count_nodes() const { return N; }\n\n    /**\n     * @return \u8FBA\u306E\
    \u6570\n     */\n    int count_edges() const { return E.size(); }\n\n    /**\n\
    \     * @param n \u30CE\u30FC\u30C9\u756A\u53F7\n     * @return \u30CE\u30FC\u30C9\
    \ n \u304B\u3089\u306E\u96A3\u63A5\u9802\u70B9\u306E\u30EA\u30B9\u30C8\u306E const\
    \ \u53C2\u7167\n     */\n    const std::vector<edge<WEIGHT>> &operator[](int n)\
    \ const { return G[n]; }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\u5168\u4F53\
    \u306E\u8FBA\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\n     */\n    const\
    \ std::vector<edge<WEIGHT>> &edges() const { return E; }\n\n    /**\n     * @param\
    \ x \u30CE\u30FC\u30C9\u756A\u53F7\n     * @param y \u30CE\u30FC\u30C9\u756A\u53F7\
    \n     * @return x, y \u304C\u9023\u7D50\u304B\u3069\u3046\u304B\n     */\n  \
    \  bool are_connected(int x, int y) { return uf.same(x, y); }\n\n    /**\n   \
    \  * @return \u9023\u7D50\u6210\u5206\u306E\u6570\n     */\n    int count_connected_components()\
    \ const { return uf.count_groups(); }\n\n    /**\n     * @return \u9023\u7D50\u6210\
    \u5206\u306E\u30EA\u30B9\u30C8\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>>\
    \ connected_components() { return uf.groups(); }\n\n    /**\n     * @return \u6728\
    \u304B\n     */\n    bool is_tree() const {\n        return (uf.count_groups()\
    \ == 1 && E.size() == N - 1);\n    }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\
    \u306E\u91CD\u307F\n     */\n    WEIGHT weight() const { return W; }\n\n    /**\n\
    \     * @param e \u8FBA\n     * @attention \u6E21\u3057\u305F\u8FBA\u306E id \u306F\
    \u4FDD\u6301\u3055\u308C\u308B\n     */\n    void add_edge(const edge<WEIGHT>\
    \ &e) { internal_add_edge(e); }\n\n    /**\n     * @attention \u8FBA\u306E id\
    \ \u306F\u3001(\u73FE\u5728\u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\
    \u3089\u308C\u308B\n     * @attention WEIGHT \u304C int \u3060\u3068\u30A8\u30E9\
    \u30FC\n     */\n    template <typename T = WEIGHT>\n    typename std::enable_if<!std::is_same<T,\
    \ int>::value>::type\n    add_edge(int from, int to, WEIGHT cost) {\n        internal_add_edge(edge<WEIGHT>(from,\
    \ to, cost, E.size()));\n    }\n\n    /**\n     * @attention \u8FBA\u306E id \u306F\
    \u3001(\u73FE\u5728\u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\u3089\
    \u308C\u308B\n     * @attention WEIGHT \u304C int \u4EE5\u5916\u3060\u3068\u30A8\
    \u30E9\u30FC\n     */\n    template <typename T = WEIGHT>\n    typename std::enable_if<std::is_same<T,\
    \ int>::value>::type\n    add_edge(int from, int to) {\n        internal_add_edge(edge<int>(from,\
    \ to, E.size()));\n    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\
    \u7D50\u306A\u30B0\u30E9\u30D5\u306B\u5206\u3051\u3066\u30EA\u30B9\u30C8\u306B\
    \u3057\u3066\u8FD4\u3059\n     * @example auto[Gs, gr, nd] = G.decompose();\n\
    \     * @returns\n     * 1.\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\n     *\
    \ 2.\u5404\u30CE\u30FC\u30C9\u304C\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\u306E\
    \u4F55\u756A\u76EE\u306B\u5C5E\u3059\u308B\u304B\n     * 3.\u5404\u30CE\u30FC\u30C9\
    \u304C\u30B0\u30E9\u30D5\u306E\u3069\u306E\u30CE\u30FC\u30C9\u306B\u306A\u3063\
    \u3066\u3044\u308B\u304B\n     */\n    std::tuple<std::vector<graph>, std::vector<int>,\
    \ std::vector<int>>\n    decompose() {\n        std::vector<graph> Gs(uf.count_groups());\n\
    \        std::vector<std::vector<int>> groups(uf.groups());\n        std::vector<int>\
    \ group_id(N), node_id(N);\n        for (int i = 0; i < groups.size(); i++) {\n\
    \            Gs[i].expand(groups[i].size());\n            for (int j = 0; j <\
    \ groups[i].size(); j++) {\n                group_id[groups[i][j]] = i;\n    \
    \            node_id[groups[i][j]] = j;\n            }\n        }\n        for\
    \ (auto &e : E) {\n            int id = group_id[e.from];\n            e.from\
    \ = node_id[e.from];\n            e.to = node_id[e.to];\n            Gs[id].add_edge(e);\n\
    \        }\n        return std::make_tuple(Gs, group_id, node_id);\n    }\n\n\
    \    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u96A3\u63A5\u884C\u5217\u306B\
    \u5909\u63DB\n     * @param invalid \u8FBA\u306E\u306A\u3044\u3068\u304D\u306E\
    \u5024\n     * @attention G \u306B\u81EA\u5DF1\u30EB\u30FC\u30D7\u304C\u542B\u307E\
    \u308C\u3066\u3044\u306A\u3044\u9650\u308A\u3001\u5BFE\u89D2\u6210\u5206\u306F\
    \ 0\n     */\n    matrix<WEIGHT> to_adjajency(WEIGHT invalid = 0) {\n        int\
    \ N = count_nodes();\n        matrix<WEIGHT> ret(N, N, invalid);\n        for\
    \ (int i = 0; i < N; i++)\n            ret[i][i] = 0;\n        for (int i = 0;\
    \ i < N; i++) {\n            for (auto &e : G[i]) {\n                ret[e.from][e.to]\
    \ = e.cost;\n            }\n        }\n        return ret;\n    }\n\n    void\
    \ print() const {\n        std::cout << this->N << \" \" << this->E.size() <<\
    \ std::endl;\n        for (const edge<WEIGHT> &e : this->E)\n            std::cout\
    \ << e << std::endl;\n    }\n};\n#line 6 \"graph/Manhattan_minimum_spanning_tree.hpp\"\
    \n\n/**\n * @see https://hitonanode.github.io/cplib-cpp/graph/manhattan_mst.hpp\n\
    \ * @brief \u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u5C0F\u91CD\
    \u307F\u5168\u57DF\u6728\u3092\u69CB\u6210\u3059\u308B\u3002\n * @param xs \u5404\
    \u30CE\u30FC\u30C9\u306E x \u5EA7\u6A19\n * @param ys \u5404\u30CE\u30FC\u30C9\
    \u306E y \u5EA7\u6A19\n */\ntemplate <typename WEIGHT> class Manhattan_minimum_spanning_tree\
    \ {\n  private:\n    graph<WEIGHT, false> mst;\n\n  public:\n    Manhattan_minimum_spanning_tree(std::vector<WEIGHT>\
    \ &xs,\n                                    std::vector<WEIGHT> &ys)\n       \
    \ : mst(xs.size()) {\n        int N = xs.size();\n        std::vector<edge<WEIGHT>>\
    \ E;\n        std::vector<int> idx(N);\n        std::iota(idx.begin(), idx.end(),\
    \ 0);\n        for (int s = 0; s < 2; s++) {\n            for (int t = 0; t <\
    \ 2; t++) {\n                std::sort(idx.begin(), idx.end(), [&](int i, int\
    \ j) {\n                    return xs[i] + ys[i] < xs[j] + ys[j];\n          \
    \      });\n                std::map<WEIGHT, int> sweep;\n                for\
    \ (int i : idx) {\n                    for (auto it = sweep.lower_bound(-ys[i]);\
    \ it != sweep.end();\n                         it = sweep.erase(it)) {\n     \
    \                   int j = it->second;\n                        if (xs[i] - xs[j]\
    \ < ys[i] - ys[j])\n                            break;\n                     \
    \   E.emplace_back(edge<WEIGHT>{i, j,\n                                      \
    \              std::abs(xs[i] - xs[j]) +\n                                   \
    \                     std::abs(ys[i] - ys[j]),\n                             \
    \                       -1});\n                    }\n                    sweep[-ys[i]]\
    \ = i;\n                }\n                std::swap(xs, ys);\n            }\n\
    \            for (auto &x : xs)\n                x = -x;\n        }\n\n      \
    \  int cnt_id = 0;\n        sort(E.begin(), E.end());\n        for (auto &e :\
    \ E)\n            if (!mst.are_connected(e.from, e.to)) {\n                e.id\
    \ = cnt_id;\n                mst.add_edge(e);\n                cnt_id++;\n   \
    \         }\n    }\n\n    const graph<WEIGHT, false> &get_tree() { return mst;\
    \ }\n};\n#line 4 \"test/manhattan-mst.test.cpp\"\nusing namespace std;\nusing\
    \ ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n\n    //input\n \n    int N;\n    cin >> N;\n    vector<ll>\
    \ X(N), Y(N);\n    rep(i,0,N){\n        cin >> X[i] >> Y[i];\n    }\n \n    //calculate\n\
    \ \n    Manhattan_minimum_spanning_tree mst(X, Y);\n \n    cout << mst.get_tree().weight()\
    \ << endl;\n    for(auto &e : mst.get_tree().edges()){\n        cout << e.from\
    \ << \" \" << e.to << endl; \n    }\n\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/manhattanmst\"\n#include\
    \ <bits/stdc++.h>\n#include \"../graph/Manhattan_minimum_spanning_tree.hpp\"\n\
    using namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j);\
    \ i < (ll)(n); i++)\n\nint main(void){\n\n    //input\n \n    int N;\n    cin\
    \ >> N;\n    vector<ll> X(N), Y(N);\n    rep(i,0,N){\n        cin >> X[i] >> Y[i];\n\
    \    }\n \n    //calculate\n \n    Manhattan_minimum_spanning_tree mst(X, Y);\n\
    \ \n    cout << mst.get_tree().weight() << endl;\n    for(auto &e : mst.get_tree().edges()){\n\
    \        cout << e.from << \" \" << e.to << endl; \n    }\n\n}"
  dependsOn:
  - graph/Manhattan_minimum_spanning_tree.hpp
  - graph/graph.hpp
  - data_structure/union_find.hpp
  - math/matrix.hpp
  - graph/edge.hpp
  isVerificationFile: true
  path: test/manhattan-mst.test.cpp
  requiredBy: []
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/manhattan-mst.test.cpp
layout: document
redirect_from:
- /verify/test/manhattan-mst.test.cpp
- /verify/test/manhattan-mst.test.cpp.html
title: test/manhattan-mst.test.cpp
---