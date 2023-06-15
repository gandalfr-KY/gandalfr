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
    path: graph/graph.hpp
    title: "\u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002"
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: graph/shortest_path.hpp
  - icon: ':question:'
    path: math/matrix.hpp
    title: "\u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\u308B\u3002"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-5-a.test.cpp
    title: test/grl-5-a.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u306E\u76F4\u5F84"
    links: []
  bundledCode: "#line 1 \"graph/diameter.hpp\"\n\n\n#line 1 \"graph/shortest_path.hpp\"\
    \n\n\n#include <queue>\n#line 1 \"graph/graph.hpp\"\n\n\n#include <vector>\n#include\
    \ <algorithm>\n#include <tuple>\n#line 1 \"graph/edge.hpp\"\n\n\n#include <iostream>\n\
    \nnamespace internal{\n    template<class DERIVED, class WEIGHT>\n    struct _base_edge{\n\
    \        int from;\n        int to;\n        WEIGHT cost;\n        int id;\n \
    \       _base_edge(int _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to),\
    \ cost(_cost), id(_id) {}\n\n        friend bool operator>(const _base_edge &e1,\
    \ const _base_edge &e){\n            return e1.compare(e) > 0;\n        }\n  \
    \      friend bool operator>=(const _base_edge &e1, const _base_edge &e){\n  \
    \          return e1.compare(e) >= 0;\n        }\n        friend bool operator<(const\
    \ _base_edge &e1, const _base_edge &e){\n            return e1.compare(e) < 0;\n\
    \        }\n        friend bool operator<=(const _base_edge &e1, const _base_edge\
    \ &e){\n            return e1.compare(e) <= 0;\n        }\n        friend std::ostream\
    \ &operator<<(std::ostream &os, const _base_edge<DERIVED, WEIGHT> &e) {\n    \
    \        e.print(os);\n            return os;\n        }\n        _base_edge &operator=(const\
    \ _base_edge &e) = default;\n\n        virtual ~_base_edge() = default; \n\n \
    \       operator int() const { return to; }\n\n      protected:\n        virtual\
    \ void print(std::ostream &os) const = 0;\n        virtual int compare(const _base_edge\
    \ &e) const = 0;\n    };\n}\n\ntemplate<class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT>{\n    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0, 0)\
    \ {}\n    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;\n  protected:\n\
    \    void print(std::ostream &os) const override {\n        os << this->from <<\
    \ \" \" << this->to << \" \" << this->cost;\n    }  \n    int compare(const internal::_base_edge<edge<WEIGHT>,\
    \ WEIGHT>& e) const override {\n        if(this->cost == e.cost){\n          \
    \  if(this->from == e.from){\n                return this->to - e.to;\n      \
    \      }\n            return this->from - e.from;\n        }\n        return this->cost\
    \ - e.cost;\n    }\n};\n\ntemplate<>\nstruct edge<int> : public internal::_base_edge<edge<int>,\
    \ int>{\n    static const int cost = 1;\n    edge() : internal::_base_edge<edge<int>,\
    \ int>(0, 0, 0, 0) {}\n    edge(int _from, int _to, int _id) : _base_edge<edge<int>,\
    \ int>(_from, _to, 0, _id) {}\n  protected:\n    void print(std::ostream &os)\
    \ const override {\n        os << this->from << \" \" << this->to;\n    }\n  \
    \  int compare(const internal::_base_edge<edge<int>, int>& e) const override {\n\
    \        if(this->from == e.from){\n            return this->to - e.to;\n    \
    \    }\n        return this->from - e.from;\n    }\n};\n\n\n#line 1 \"data_structure/union_find.hpp\"\
    \n\n\n#line 5 \"data_structure/union_find.hpp\"\n#include <assert.h>\n\nclass\
    \ union_find{\n  private:\n    int N;\n    std::vector<int> par, group_siz;\n\
    \    int group_num; // \u96C6\u5408\u306E\u6570\n\n  public:\n    union_find()\
    \ : N(0) {}\n    union_find(int n) : N(n), par(n, -1), group_siz(n, 1), group_num(n)\
    \ {}\n\n    /**\n     * @brief \u9802\u70B9\u3092 n \u500B\u306B\u5897\u3084\u3059\
    \n     * @attention \u5C0F\u3055\u304F\u306F\u3067\u304D\u306A\u3044\n     */\n\
    \    void expand(int n){\n        if(n <= N) return;\n        N = n;\n       \
    \ par.resize(n, -1);\n        group_siz.resize(n, 1);\n        group_num += n\
    \ - N;\n    }\n\n    int leader(int x){\n        if(par[x] == -1) return x;\n\
    \        else return par[x] = leader(par[x]);\n    }\n \n    bool same(int x,\
    \ int y){\n        return leader(x) == leader(y);\n    }\n \n    bool merge(int\
    \ x, int y){\n        x = leader(x); y = leader(y);\n        if(x == y) return\
    \ false;\n        // \u5C0F\u3055\u3044\u307B\u3046\u306B\u7D71\u5408\n      \
    \  if(group_siz[x] < group_siz[y]) std::swap(x, y);\n        par[y] = x;\n   \
    \     group_siz[x] += group_siz[y];\n        group_num--;\n        return true;\n\
    \    }\n\n    // x \u306E\u5C5E\u3059\u308B\u30B0\u30EB\u30FC\u30D7\u306E\u30B5\
    \u30A4\u30BA\u3092\u8FD4\u3059\n    int size(int x){\n        return group_siz[leader(x)];\n\
    \    }\n\n    int count_groups() const {\n        return group_num;\n    }\n\n\
    \    std::vector<std::vector<int>> groups(){\n        std::vector<std::vector<int>>\
    \ result(N);\n        for(int i = 0; i < N; i++) result[i].reserve(group_siz[i]);\n\
    \        for(int i = 0; i < N; i++) result[leader(i)].push_back(i);\n        result.erase(\n\
    \            std::remove_if(result.begin(), result.end(),\n            [&](const\
    \ std::vector<int>& v) { return v.empty(); }), result.end());\n        return\
    \ result;\n    }\n};\n\n\n#line 1 \"math/matrix.hpp\"\n\n\n#include <valarray>\n\
    #line 7 \"math/matrix.hpp\"\n\ntemplate<class T>\nclass matrix{\n  private:\n\
    \    int H, W;\n    std::valarray<std::valarray<T>> table;\n\n  public:\n    matrix()\
    \ = default;\n    matrix(int _H, int _W, T val = 0) : H(_H), W(_W), table(std::valarray<T>(val,\
    \ _W), _H) {}\n    matrix(const std::vector<std::vector<T>> &vv) : H(vv.size()),\
    \ W(vv[0].size()), table(std::valarray<T>(W), H) {\n        for(int i=0; i<H;\
    \ i++) for(int j=0; j<W; j++) table[i][j] = vv[i][j];\n    }\n    matrix(const\
    \ std::valarray<std::valarray<T>> &vv) : H(vv.size()), W(vv[0].size()), table(vv)\
    \ {}\n\n    /**\n     * @brief \u884C\u5217\u3092\u30EA\u30B5\u30A4\u30BA\u3059\
    \u308B\u3002\n     * @param val \u62E1\u5F35\u90E8\u5206\u306E\u5024\n     */\n\
    \    void resize(int _H, int _W, T val = 0){\n        H = _H, W = _W;\n      \
    \  table.resize(_H, std::valarray<T>(val, _H));\n    }\n    int size_H() const\
    \ { return H; }\n    int size_W() const { return W; }\n    matrix<T> transpose()\
    \ const {\n        matrix<T> ret(W, H);\n        for(int i=0; i<H; i++) for(int\
    \ j=0; j<W; j++) ret[j][i] = table[i][j];\n        return ret;\n    }\n    /**\n\
    \     * @attention O(n^3)\n     * @attention \u6574\u6570\u578B\u3067\u306F\u6B63\
    \u3057\u304F\u8A08\u7B97\u3067\u304D\u306A\u3044\u3002double \u3084 fraction \u3092\
    \u4F7F\u3046\u3053\u3068\u3002\n     */\n    const T determinant() const {\n \
    \       assert(H == W);\n        matrix<T> dfm(*this);\n        T ret = 1;\n \
    \       for(int i=0; i<H; i++){\n            if(dfm[i][i] == 0){\n           \
    \     int piv;\n                for(piv=i+1; piv<H; piv++) if(dfm[piv][i] != 0)\
    \ break;\n                if(piv == H) return 0;\n                dfm[i].swap(dfm[piv]);\n\
    \                ret *= -1;\n            }            \n            for(int j=i+1;\
    \ j<H; j++) dfm[j] -= dfm[i] * (dfm[j][i] / dfm[i][i]);\n            ret *= dfm[i][i];\n\
    \        }\n        return ret;\n    }\n\n    void print() const {\n        for(int\
    \ i=0; i<H; i++){\n            for(int j=0; j<W; j++){\n                std::cout\
    \ << table[i][j] << (j == W - 1 ? \"\" : \" \");\n            }\n            std::cout\
    \ << std::endl;\n        }\n    }\n\n    matrix<T> &operator+=(const matrix<T>\
    \ &a){\n        this->table += a.table;\n        return *this;\n    }\n    matrix<T>\
    \ &operator-=(const matrix<T> &a){\n        this->table -= a.table;\n        return\
    \ *this;\n    }\n    matrix<T> &operator*=(const T &a){\n        this->table *=\
    \ a;\n        return *this;\n    }\n    matrix<T> &operator*=(const matrix<T>\
    \ &a){\n        assert(W == a.H);\n        matrix<T> a_t(a.transpose()), ret(H,\
    \ a.W);\n        for(int i=0; i<H; i++){\n            for(int j=0; j<a.W; j++){\n\
    \                ret[i][j] = (this->table[i] * a_t.table[j]).sum();\n        \
    \    }\n        }\n        return *this = ret;\n    }\n    matrix<T> &operator/=(const\
    \ T &a){\n        this->table /= a;\n        return *this;\n    }\n    /**\n \
    \    * @brief \u884C\u5217\u306E\u51AA\u4E57\u3002\n     * @param n \u6307\u6570\
    \n     * @attention n \u304C 0 \u306A\u3089\u5358\u4F4D\u884C\u5217\u3002\n  \
    \   * @attention \u6F14\u7B97\u5B50\u306E\u512A\u5148\u5EA6\u306B\u6CE8\u610F\u3002\
    \n     */\n    matrix<T> operator^=(long long n) {\n        assert(H == W);\n\
    \        if(n == 0) return *this = E(H);\n        n--;\n        matrix<T> x(*this);\n\
    \        while (n) {\n            if (n & 1) *this *= x;\n            x *= x;\n\
    \            n >>= 1;\n        }\n        return *this;\n    }\n\n    matrix<T>\
    \ operator+(){ return *this; }\n    matrix<T> operator-(){ return matrix<T>(*this)\
    \ *= -1; }\n    matrix<T> operator+(const matrix<T> &a){ return matrix<T>(*this)\
    \ += a; }\n    matrix<T> operator-(const matrix<T> &a){ return matrix<T>(*this)\
    \ -= a; }\n    template<typename S> matrix<T> operator*(const S &a){ return matrix<T>(*this)\
    \ *= a; }\n    matrix<T> operator/(const T &a){ return matrix<T>(*this) /= a;\
    \ }\n    matrix<T> operator^(long long n) { return matrix<T>(*this) ^= n; }\n\
    \    std::valarray<T> &operator[](int h){ return table[h]; }\n    friend std::istream\
    \ &operator>>(std::istream &is, matrix<T> &mt){\n        for(auto &arr : mt.table)\
    \ for(auto &x : arr) is >> x;\n        return is;\n    }\n    /**\n     * @brief\
    \ \u30B5\u30A4\u30BA n \u306E\u5358\u4F4D\u884C\u5217\u3002\n    */\n    static\
    \ matrix<T> E(int N){\n        matrix<T> ret(N, N);\n        for(int i = 0; i\
    \ < N; i++) ret[i][i] = 1;\n        return ret;\n    }\n};\n\n\n#line 9 \"graph/graph.hpp\"\
    \n\n/**\n * @brief \u30B0\u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\
    \u30B9\u3002\n * @tparam WEIGHT int \u306A\u3089\u91CD\u307F\u306A\u3057\u3001\
    \u305D\u3046\u3067\u306A\u3044\u306A\u3089\u91CD\u307F\u3064\u304D\u30B0\u30E9\
    \u30D5\n * @tparam is_directed \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3068\u3046\
    \u304B\n */\ntemplate <typename WEIGHT, bool is_directed>\nclass graph{\nprivate:\n\
    \    int N;\n    std::vector<std::vector<edge<WEIGHT>>> G;\n    std::vector<edge<WEIGHT>>\
    \ E;\n    union_find uf;\n    WEIGHT W = 0;\n\n    void internal_add_edge(edge<WEIGHT>\
    \ e) {\n        uf.merge(e.from, e.to);\n        G[e.from].emplace_back(e);\n\
    \        if (!is_directed && e.from != e.to) {\n            std::swap(e.from,\
    \ e.to);\n            G[e.from].emplace_back(e);\n        }\n        if (!is_directed\
    \ && e.from > e.to) std::swap(e.from, e.to);\n        E.emplace_back(e);\n   \
    \     W += e.cost;\n    }\n\npublic:\n    graph(): N(0), G(0), uf(0) {};\n   \
    \ graph(int n): N(n), G(n), uf(n) {};\n\n    /**\n     * @brief \u30CE\u30FC\u30C9\
    \u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\u3059\n     * @param n \u30B5\
    \u30A4\u30BA\n     * @attention \u4ECA\u306E\u30CE\u30FC\u30C9\u6570\u3088\u308A\
    \u5C0F\u3055\u3044\u6570\u3092\u6E21\u3057\u305F\u3068\u304D\u3001\u5909\u5316\
    \u306A\u3057\n     */ \n    void expand(int n) {\n        if(n <= N) return;\n\
    \        N = n;\n        G.resize(n);\n        uf.expand(n);\n    }\n\n    /**\n\
    \     * @return \u30CE\u30FC\u30C9\u306E\u6570\n     */\n    int count_nodes()\
    \ const { return N; }\n\n    /**\n     * @return \u8FBA\u306E\u6570\n     */\n\
    \    int count_edges() const { return E.size(); }\n\n    /** \n     * @param n\
    \ \u30CE\u30FC\u30C9\u756A\u53F7\n     * @return \u30CE\u30FC\u30C9 n \u304B\u3089\
    \u306E\u96A3\u63A5\u9802\u70B9\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\
    \n     */\n    const std::vector<edge<WEIGHT>> &operator[](int n) const { return\
    \ G[n]; }\n\n    /** \n     * @return \u30B0\u30E9\u30D5\u5168\u4F53\u306E\u8FBA\
    \u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\n     */\n    const std::vector<edge<WEIGHT>>\
    \ &edges() const { return E; }\n\n    /**\n     * @param x \u30CE\u30FC\u30C9\u756A\
    \u53F7\n     * @param y \u30CE\u30FC\u30C9\u756A\u53F7\n     * @return x, y \u304C\
    \u9023\u7D50\u304B\u3069\u3046\u304B\n     */\n    bool are_connected(int x, int\
    \ y) { return uf.same(x, y); }\n\n    /**\n     * @return \u9023\u7D50\u6210\u5206\
    \u306E\u6570\n     */\n    int count_connected_components() const { return uf.count_groups();\
    \ }\n\n    /**\n     * @return \u9023\u7D50\u6210\u5206\u306E\u30EA\u30B9\u30C8\
    \u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>> connected_components()\
    \ { return uf.groups(); }\n\n    /**\n     * @return \u6728\u304B\n     */\n \
    \   bool is_tree() const { return (uf.count_groups() == 1 && E.size() == N - 1);\
    \ }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\u306E\u91CD\u307F\n     */\n\
    \    WEIGHT weight() const { return W; }\n\n    /**\n     * @param e \u8FBA\n\
    \     * @attention \u6E21\u3057\u305F\u8FBA\u306E id \u306F\u4FDD\u6301\u3055\u308C\
    \u308B \n     */\n    void add_edge(const edge<WEIGHT> &e){\n        internal_add_edge(e);\n\
    \    }\n\n    /**\n     * @attention \u8FBA\u306E id \u306F\u3001(\u73FE\u5728\
    \u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\u3089\u308C\u308B \n\
    \     * @attention WEIGHT \u304C int \u3060\u3068\u30A8\u30E9\u30FC\n     */\n\
    \    template<typename T = WEIGHT>\n    typename std::enable_if<!std::is_same<T,\
    \ int>::value>::type \n    add_edge(int from, int to, WEIGHT cost) {\n       \
    \ internal_add_edge(edge<WEIGHT>(from, to, cost, E.size()));\n    }\n\n    /**\n\
    \     * @attention \u8FBA\u306E id \u306F\u3001(\u73FE\u5728\u306E\u8FBA\u306E\
    \u672C\u6570)\u756A\u76EE \u304C\u632F\u3089\u308C\u308B \n     * @attention WEIGHT\
    \ \u304C int \u4EE5\u5916\u3060\u3068\u30A8\u30E9\u30FC\n     */\n    template<typename\
    \ T = WEIGHT>\n    typename std::enable_if<std::is_same<T, int>::value>::type\
    \ \n    add_edge(int from, int to) {\n        internal_add_edge(edge<int>(from,\
    \ to, E.size()));\n    }\n\n    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u9023\
    \u7D50\u306A\u30B0\u30E9\u30D5\u306B\u5206\u3051\u3066\u30EA\u30B9\u30C8\u306B\
    \u3057\u3066\u8FD4\u3059\n     * @example auto[Gs, gr, nd] = G.decompose();\n\
    \     * @returns\n     * 1.\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8 \n     *\
    \ 2.\u5404\u30CE\u30FC\u30C9\u304C\u30B0\u30E9\u30D5\u306E\u30EA\u30B9\u30C8\u306E\
    \u4F55\u756A\u76EE\u306B\u5C5E\u3059\u308B\u304B \n     * 3.\u5404\u30CE\u30FC\
    \u30C9\u304C\u30B0\u30E9\u30D5\u306E\u3069\u306E\u30CE\u30FC\u30C9\u306B\u306A\
    \u3063\u3066\u3044\u308B\u304B \n    */\n    std::tuple<std::vector<graph>, std::vector<int>,\
    \ std::vector<int>> decompose() {\n        std::vector<graph> Gs(uf.count_groups());\n\
    \        std::vector<std::vector<int>> groups(uf.groups());\n        std::vector<int>\
    \ group_id(N), node_id(N);\n        for (int i = 0; i < groups.size(); i++) {\n\
    \            Gs[i].expand(groups[i].size());\n            for (int j = 0; j <\
    \ groups[i].size(); j++) {\n                group_id[groups[i][j]] = i;\n    \
    \            node_id[groups[i][j]] = j;\n            }\n        }\n        for\
    \ (auto& e : E) {\n            int id = group_id[e.from];\n            e.from\
    \ = node_id[e.from];\n            e.to = node_id[e.to];\n            Gs[id].add_edge(e);\n\
    \        }\n        return std::make_tuple(Gs, group_id, node_id);\n    }\n\n\
    \    /**\n     * @brief \u30B0\u30E9\u30D5\u3092\u96A3\u63A5\u884C\u5217\u306B\
    \u5909\u63DB\n     * @param invalid \u8FBA\u306E\u306A\u3044\u3068\u304D\u306E\
    \u5024\n     * @attention G \u306B\u81EA\u5DF1\u30EB\u30FC\u30D7\u304C\u542B\u307E\
    \u308C\u3066\u3044\u306A\u3044\u9650\u308A\u3001\u5BFE\u89D2\u6210\u5206\u306F\
    \ 0 \n     */\n    matrix<WEIGHT> to_adjajency(WEIGHT invalid = 0){\n        int\
    \ N = count_nodes();\n        matrix<WEIGHT> ret(N, N, invalid);\n        for\
    \ (int i = 0; i < N; i++) ret[i][i] = 0; \n        for (int i = 0; i < N; i++)\
    \ {\n            for (auto &e : G[i]) {\n                ret[e.from][e.to] = e.cost;\n\
    \            }\n        }\n        return ret;\n    }\n\n    void print() const\
    \ {\n        std::cout << this->N << \" \" << this->E.size() << std::endl;\n \
    \       for (const edge<WEIGHT> &e : this->E) std::cout << e << std::endl;\n \
    \   }\n};\n\n\n#line 5 \"graph/shortest_path.hpp\"\n\nnamespace internal{\n  \
    \  template<bool is_directed>\n    void bfs(const graph<int, is_directed> &G,\
    \ std::vector<int> &dist, std::queue<int> &q){\n        while(!q.empty()){\n \
    \           int cu = q.front();\n            q.pop();\n            for(auto &e\
    \ : G[cu]){\n                if(dist[e.to] != -1) continue;\n                dist[e.to]\
    \ = dist[cu] + 1;\n                q.push(e.to);\n            }\n        }\n \
    \   }\n\n    template<typename WEIGHT, bool is_directed>\n    void dijkstra(const\
    \ graph<WEIGHT, is_directed> &G, std::vector<WEIGHT> &dist, \n        std::priority_queue<std::pair<WEIGHT,\
    \ int>,\n        std::vector<std::pair<WEIGHT, int>>, \n        std::greater<std::pair<WEIGHT,\
    \ int>>> &q){\n\n        std::vector<bool> vis(G.count_nodes(), false);\n    \
    \    while(!q.empty()){\n            WEIGHT cur_dist = q.top().first;\n      \
    \      int cu = q.top().second;\n            q.pop();\n\n            if(vis[cu])\
    \ continue;\n            vis[cu] = true;\n\n            for(auto &e : G[cu]){\n\
    \                WEIGHT alt = cur_dist + e.cost;\n                if(dist[e.to]\
    \ <= alt) continue;\n                dist[e.to] = alt;\n                q.push({alt,\
    \ e.to});\n            }\n        }\n    }\n}\n\n/* \u5358\u4E00\u307E\u305F\u306F\
    \u8907\u6570\u306E\u30CE\u30FC\u30C9from\u304B\u3089\u5168\u3066\u306E\u30CE\u30FC\
    \u30C9\u306B\u5BFE\u3057\u3066\u306E\u6700\u77ED\u7D4C\u8DEF\u306E\u9577\u3055\
    \u3092\u8FD4\u3059\n * \u5230\u9054\u4E0D\u80FD\u306A\u3089\u3070\u3001-1\u3067\
    \u8FD4\u308B\n * \u91CD\u307F\u7121\u3057 : O(N)\n * \u91CD\u307F\u6709\u308A\
    \ : O(NlogN)\n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7443620\n\
    \ */\ntemplate<bool is_directed>\nstd::vector<int> shortest_path(const graph<int,\
    \ is_directed> &G, int start_point){\n    std::queue<int> q;\n    std::vector<int>\
    \ dist(G.count_nodes(), -1);\n    q.push(start_point);\n    dist[start_point]\
    \ = 0;\n    internal::bfs(G, dist, q);\n    return dist;\n}\n\ntemplate<bool is_directed>\n\
    std::vector<int> shortest_path(const graph<int, is_directed> &G, const std::vector<int>\
    \ &start_points){\n    std::queue<int> q;\n    std::vector<int> dist(G.count_nodes(),\
    \ -1);\n    for(int start_point : start_points){\n        q.push(start_point);\n\
    \        dist[start_point] = 0;\n    }\n    internal::bfs(G, dist, q);\n    return\
    \ dist;\n}\n\n\ntemplate<typename WEIGHT, bool is_directed>\nstd::vector<WEIGHT>\
    \ shortest_path(const graph<WEIGHT, is_directed> &G, int start_point){\n    //\
    \ first := current_distance, second := next\n    using PAIR = std::pair<WEIGHT,\
    \ int>;\n    WEIGHT ma = std::numeric_limits<WEIGHT>::max();\n    std::priority_queue<PAIR,\
    \ std::vector<PAIR>, std::greater<PAIR>> q;\n    std::vector<WEIGHT> dist(G.count_nodes(),\
    \ ma);\n    q.push({0, start_point});\n    dist[start_point] = 0;\n\n    internal::dijkstra(G,\
    \ dist, q);\n    for(WEIGHT &x : dist) if(x == ma) x = -1; \n    return dist;\n\
    }\n\ntemplate<typename WEIGHT, bool is_directed>\nstd::vector<WEIGHT> shortest_path(const\
    \ graph<WEIGHT, is_directed> &G, const std::vector<int> &start_points){\n    //\
    \ first := current_distance, second := next\n    using PAIR = std::pair<WEIGHT,\
    \ int>;\n    WEIGHT ma = std::numeric_limits<WEIGHT>::max();\n    std::priority_queue<PAIR,\
    \ std::vector<PAIR>, std::greater<PAIR>> q;\n    std::vector<WEIGHT> dist(G.count_nodes(),\
    \ ma);\n    for(int start_point : start_points){\n        q.push({0, start_point});\n\
    \        dist[start_point] = 0;\n    }\n\n    internal::dijkstra(G, dist, q);\n\
    \    for(WEIGHT &x : dist) if(x == ma) x = -1; \n    return dist;\n}\n\n\n#line\
    \ 6 \"graph/diameter.hpp\"\n\n/**\n * @brief \u6728\u306E\u76F4\u5F84\n */\ntemplate<typename\
    \ WEIGHT>\nWEIGHT diameter(const graph<WEIGHT, false> &G){\n    assert(G.is_tree());\n\
    \    std::vector<WEIGHT> dist = shortest_path(G, 0);\n    int farthest_node =\
    \ std::max_element(dist.begin(), dist.end()) - dist.begin();\n    dist = shortest_path(G,\
    \ farthest_node);\n    return *std::max_element(dist.begin(), dist.end());\n}\n\
    \n\n"
  code: "#ifndef DIAMETER\n#define DIAMETER\n#include \"shortest_path.hpp\" \n#include\
    \ <iostream>\n#include <assert.h>\n\n/**\n * @brief \u6728\u306E\u76F4\u5F84\n\
    \ */\ntemplate<typename WEIGHT>\nWEIGHT diameter(const graph<WEIGHT, false> &G){\n\
    \    assert(G.is_tree());\n    std::vector<WEIGHT> dist = shortest_path(G, 0);\n\
    \    int farthest_node = std::max_element(dist.begin(), dist.end()) - dist.begin();\n\
    \    dist = shortest_path(G, farthest_node);\n    return *std::max_element(dist.begin(),\
    \ dist.end());\n}\n\n#endif\n"
  dependsOn:
  - graph/shortest_path.hpp
  - graph/graph.hpp
  - graph/edge.hpp
  - data_structure/union_find.hpp
  - math/matrix.hpp
  isVerificationFile: false
  path: graph/diameter.hpp
  requiredBy: []
  timestamp: '2023-06-16 02:03:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/grl-5-a.test.cpp
documentation_of: graph/diameter.hpp
layout: document
redirect_from:
- /library/graph/diameter.hpp
- /library/graph/diameter.hpp.html
title: "\u6728\u306E\u76F4\u5F84"
---
