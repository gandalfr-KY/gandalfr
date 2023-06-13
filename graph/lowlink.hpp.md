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
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/grl-3-a.test.cpp
    title: test/grl-3-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/grl-3-b.test.cpp
    title: test/grl-3-b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5358\u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\u70B9\
      \u30FB\u6A4B\u3092\u6C42\u3081\u308B"
    links: []
  bundledCode: "#line 1 \"graph/lowlink.hpp\"\n\n\n#include <utility>\n#line 1 \"\
    graph/graph.hpp\"\n\n\n#include <vector>\n#include <algorithm>\n#include <tuple>\n\
    #line 1 \"graph/edge.hpp\"\n\n\n#include <iostream>\n\nnamespace internal{\n \
    \   template<class DERIVED, class WEIGHT>\n    struct _base_edge{\n        int\
    \ from;\n        int to;\n        WEIGHT cost;\n        int id;\n        _base_edge(int\
    \ _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to), cost(_cost),\
    \ id(_id) {}\n\n        friend bool operator>(const _base_edge &e1, const _base_edge\
    \ &e){\n            return e1.compare(e) > 0;\n        }\n        friend bool\
    \ operator>=(const _base_edge &e1, const _base_edge &e){\n            return e1.compare(e)\
    \ >= 0;\n        }\n        friend bool operator<(const _base_edge &e1, const\
    \ _base_edge &e){\n            return e1.compare(e) < 0;\n        }\n        friend\
    \ bool operator<=(const _base_edge &e1, const _base_edge &e){\n            return\
    \ e1.compare(e) <= 0;\n        }\n        friend std::ostream &operator<<(std::ostream\
    \ &os, const _base_edge<DERIVED, WEIGHT> &e) {\n            e.print(os);\n   \
    \         return os;\n        }\n        _base_edge &operator=(const _base_edge\
    \ &e) = default;\n\n        virtual ~_base_edge() = default; \n\n        operator\
    \ int() const { return to; }\n\n      protected:\n        virtual void print(std::ostream\
    \ &os) const = 0;\n        virtual int compare(const _base_edge &e) const = 0;\n\
    \    };\n}\n\ntemplate<class WEIGHT>\nstruct edge : public internal::_base_edge<edge<WEIGHT>,\
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
    \ result;\n    }\n};\n\n\n#line 8 \"graph/graph.hpp\"\n\n/**\n * @brief \u30B0\
    \u30E9\u30D5\u3092\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\u3002\n * @tparam\
    \ WEIGHT int \u306A\u3089\u91CD\u307F\u306A\u3057\u3001\u305D\u3046\u3067\u306A\
    \u3044\u306A\u3089\u91CD\u307F\u3064\u304D\u30B0\u30E9\u30D5\n * @tparam is_directed\
    \ \u6709\u5411\u30B0\u30E9\u30D5\u304B\u3068\u3046\u304B\n */\ntemplate <typename\
    \ WEIGHT, bool is_directed>\nclass graph{\nprivate:\n    int N;\n    std::vector<std::vector<edge<WEIGHT>>>\
    \ G;\n    std::vector<edge<WEIGHT>> E;\n    union_find uf;\n    WEIGHT W = 0;\n\
    \n    void internal_add_edge(edge<WEIGHT> e) {\n        uf.merge(e.from, e.to);\n\
    \        G[e.from].emplace_back(e);\n        if (!is_directed && e.from != e.to)\
    \ {\n            std::swap(e.from, e.to);\n            G[e.from].emplace_back(e);\n\
    \        }\n        if (!is_directed && e.from > e.to) std::swap(e.from, e.to);\n\
    \        E.emplace_back(e);\n        W += e.cost;\n    }\n\npublic:\n    graph():\
    \ N(0), G(0), uf(0) {};\n    graph(int n): N(n), G(n), uf(n) {};\n\n    /**\n\
    \     * @brief \u30CE\u30FC\u30C9\u306E\u6570\u3092n\u500B\u307E\u3067\u5897\u3084\
    \u3059\n     * @param n \u30B5\u30A4\u30BA\n     * @attention \u4ECA\u306E\u30CE\
    \u30FC\u30C9\u6570\u3088\u308A\u5C0F\u3055\u3044\u6570\u3092\u6E21\u3057\u305F\
    \u3068\u304D\u3001\u5909\u5316\u306A\u3057\n     */ \n    void expand(int n) {\n\
    \        if(n <= N) return;\n        N = n;\n        G.resize(n);\n        uf.expand(n);\n\
    \    }\n\n    /**\n     * @return \u30CE\u30FC\u30C9\u306E\u6570\n     */\n  \
    \  int count_nodes() const { return N; }\n\n    /**\n     * @return \u8FBA\u306E\
    \u6570\n     */\n    int count_edges() const { return E.size(); }\n\n    /** \n\
    \     * @param n \u30CE\u30FC\u30C9\u756A\u53F7\n     * @return \u30CE\u30FC\u30C9\
    \ n \u304B\u3089\u306E\u96A3\u63A5\u9802\u70B9\u306E\u30EA\u30B9\u30C8\u306E const\
    \ \u53C2\u7167\n     */\n    const std::vector<edge<WEIGHT>> &operator[](int n)\
    \ const { return G[n]; }\n\n    /** \n     * @return \u30B0\u30E9\u30D5\u5168\u4F53\
    \u306E\u8FBA\u306E\u30EA\u30B9\u30C8\u306E const \u53C2\u7167\n     */\n    const\
    \ std::vector<edge<WEIGHT>> &edges() const { return E; }\n\n    /**\n     * @param\
    \ x \u30CE\u30FC\u30C9\u756A\u53F7\n     * @param y \u30CE\u30FC\u30C9\u756A\u53F7\
    \n     * @return x, y \u304C\u9023\u7D50\u304B\u3069\u3046\u304B\n     */\n  \
    \  bool are_connected(int x, int y) { return uf.same(x, y); }\n\n    /**\n   \
    \  * @return \u9023\u7D50\u6210\u5206\u306E\u6570\n     */\n    int count_connected_components()\
    \ const { return uf.count_groups(); }\n\n    /**\n     * @return \u9023\u7D50\u6210\
    \u5206\u306E\u30EA\u30B9\u30C8\u306E\u30EA\u30B9\u30C8\n     */\n    std::vector<std::vector<int>>\
    \ connected_components() { return uf.groups(); }\n\n    /**\n     * @return \u6728\
    \u304B\n     */\n    bool is_tree() const { return (uf.count_groups() == 1 &&\
    \ E.size() == N - 1); }\n\n    /**\n     * @return \u30B0\u30E9\u30D5\u306E\u91CD\
    \u307F\n     */\n    WEIGHT weight() const { return W; }\n\n    /**\n     * @param\
    \ e \u8FBA\n     * @attention \u6E21\u3057\u305F\u8FBA\u306E id \u306F\u4FDD\u6301\
    \u3055\u308C\u308B \n     */\n    void add_edge(const edge<WEIGHT> &e){\n    \
    \    internal_add_edge(e);\n    }\n\n    /**\n     * @attention \u8FBA\u306E id\
    \ \u306F\u3001(\u73FE\u5728\u306E\u8FBA\u306E\u672C\u6570)\u756A\u76EE \u304C\u632F\
    \u3089\u308C\u308B \n     * @attention WEIGHT \u304C int \u3060\u3068\u30A8\u30E9\
    \u30FC\n     */\n    template<typename T = WEIGHT>\n    typename std::enable_if<!std::is_same<T,\
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
    \    void print() const {\n        std::cout << this->N << \" \" << this->E.size()\
    \ << std::endl;\n        for(const edge<WEIGHT> &e : this->E) std::cout << e <<\
    \ std::endl;\n    }\n};\n\n\n#line 5 \"graph/lowlink.hpp\"\n\n/**\n * @brief \u5358\
    \u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\u70B9\u30FB\u6A4B\u3092\
    \u6C42\u3081\u308B\n * @attention \u9023\u7D50\u3067\u306A\u3044\u3068\u304D\u306E\
    \ verify \u304C\u3067\u304D\u3066\u306A\u3044\u3002\u591A\u5206\u3042\u3063\u3066\
    \u308B\u3051\u3069...\n */\ntemplate<typename WEIGHT>\nclass lowlink{\nprivate:\n\
    \    std::vector<int> ord, low, apts;\n    std::vector<edge<WEIGHT>> brids;\n\
    \    \n    void dfs(const graph<WEIGHT, false> &g, int cu, int pa, int &cnt, const\
    \ std::vector<int> &id,\n             std::vector<bool> &is_apt, std::vector<bool>\
    \ &is_bridge){\n        ord[cu] = low[cu] = cnt++;\n        for(auto &e : g[cu]){\n\
    \            if(e.to == pa) continue;\n            if(ord[e.to] == -1){\n    \
    \            dfs(g, e.to, cu, cnt, id, is_apt, is_bridge);\n                if(low[cu]\
    \ > low[e.to]) low[cu] = low[e.to];\n                if(ord[cu] < low[e.to]) is_bridge[e.id]\
    \ = true;\n                if(pa != -1 && ord[cu] <= low[e.to]) is_apt[id[cu]]\
    \ = true;\n            }\n            else if(low[cu] > ord[e.to]) low[cu] = ord[e.to];\n\
    \        }\n    }\n\npublic:\n    lowlink(graph<WEIGHT, false> &G) : ord(G.count_nodes(),\
    \ -1), low(G.count_nodes(), -1) {\n        \n        int C = G.count_connected_components(),\
    \ N = G.count_nodes(), M = G.count_edges();\n        std::vector<bool> is_apt(N,\
    \ false), is_bridge(M, false);\n        auto [decomposed, gr_id, nd_id] = G.decompose();\n\
    \        std::vector<std::vector<int>> id(N); // i \u756A\u76EE\u306E\u30B0\u30E9\
    \u30D5\u306E\u30CE\u30FC\u30C9 j \u306E\u3001\u3082\u3068\u306E\u30B0\u30E9\u30D5\
    \u306E\u30CE\u30FC\u30C9\u306E\u756A\u53F7\n        for(int c = 0; c < C; c++)\
    \ id[c].resize(decomposed[c].count_nodes());\n        for(int i = 0; i < N; i++)\
    \ id[gr_id[i]][nd_id[i]] = i;\n\n        std::vector<std::pair<int, int>> st(C,\
    \ {0x7fffffff, -1}); // <\u6B21\u6570, id>\n        for(int c = 0; c < C; c++)\
    \ {\n            // \u6B21\u6570\u304C\u6700\u5C0F\u306E\u30CE\u30FC\u30C9\u306F\
    \u5FC5\u305A\u95A2\u7BC0\u70B9\u3067\u306A\u3044\n            // \u305D\u3053\u304B\
    \u3089DFS\u3059\u308C\u3070\u3001\u6839\u30CE\u30FC\u30C9\u306E\u95A2\u7BC0\u70B9\
    \u5224\u5B9A\u3092\u884C\u308F\u306A\u304F\u3066\u3088\u3044\n            for(int\
    \ i = 0; i < decomposed[c].count_nodes(); i++) {\n                st[c] = std::min(st[c],\
    \ {(int)decomposed[c][i].size(), i});\n            }\n        }\n\n        for(int\
    \ c = 0; c < C; c++) {\n            int cnt = 0;\n            dfs(decomposed[c],\
    \ st[c].second, -1, cnt, id[c], is_apt, is_bridge);\n        }\n        for(int\
    \ i = 0; i < N; i++) if(is_apt[i]) apts.push_back(i); \n        for(int i = 0;\
    \ i < M; i++) if(is_bridge[i]) brids.emplace_back(G.edges()[i]); \n    }\n\n \
    \   // unsorted \u3067\u3042\u308B\u3053\u3068\u306B\u6CE8\u610F\n    const std::vector<int>\
    \ &articulation_points(){ return apts; }\n    const std::vector<edge<WEIGHT>>\
    \ &bridges(){ return brids; }\n\n};\n\n\n\n"
  code: "#ifndef LOWLINK\n#define LOWLINK\n#include <utility>\n#include \"graph.hpp\"\
    \n\n/**\n * @brief \u5358\u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\
    \u70B9\u30FB\u6A4B\u3092\u6C42\u3081\u308B\n * @attention \u9023\u7D50\u3067\u306A\
    \u3044\u3068\u304D\u306E verify \u304C\u3067\u304D\u3066\u306A\u3044\u3002\u591A\
    \u5206\u3042\u3063\u3066\u308B\u3051\u3069...\n */\ntemplate<typename WEIGHT>\n\
    class lowlink{\nprivate:\n    std::vector<int> ord, low, apts;\n    std::vector<edge<WEIGHT>>\
    \ brids;\n    \n    void dfs(const graph<WEIGHT, false> &g, int cu, int pa, int\
    \ &cnt, const std::vector<int> &id,\n             std::vector<bool> &is_apt, std::vector<bool>\
    \ &is_bridge){\n        ord[cu] = low[cu] = cnt++;\n        for(auto &e : g[cu]){\n\
    \            if(e.to == pa) continue;\n            if(ord[e.to] == -1){\n    \
    \            dfs(g, e.to, cu, cnt, id, is_apt, is_bridge);\n                if(low[cu]\
    \ > low[e.to]) low[cu] = low[e.to];\n                if(ord[cu] < low[e.to]) is_bridge[e.id]\
    \ = true;\n                if(pa != -1 && ord[cu] <= low[e.to]) is_apt[id[cu]]\
    \ = true;\n            }\n            else if(low[cu] > ord[e.to]) low[cu] = ord[e.to];\n\
    \        }\n    }\n\npublic:\n    lowlink(graph<WEIGHT, false> &G) : ord(G.count_nodes(),\
    \ -1), low(G.count_nodes(), -1) {\n        \n        int C = G.count_connected_components(),\
    \ N = G.count_nodes(), M = G.count_edges();\n        std::vector<bool> is_apt(N,\
    \ false), is_bridge(M, false);\n        auto [decomposed, gr_id, nd_id] = G.decompose();\n\
    \        std::vector<std::vector<int>> id(N); // i \u756A\u76EE\u306E\u30B0\u30E9\
    \u30D5\u306E\u30CE\u30FC\u30C9 j \u306E\u3001\u3082\u3068\u306E\u30B0\u30E9\u30D5\
    \u306E\u30CE\u30FC\u30C9\u306E\u756A\u53F7\n        for(int c = 0; c < C; c++)\
    \ id[c].resize(decomposed[c].count_nodes());\n        for(int i = 0; i < N; i++)\
    \ id[gr_id[i]][nd_id[i]] = i;\n\n        std::vector<std::pair<int, int>> st(C,\
    \ {0x7fffffff, -1}); // <\u6B21\u6570, id>\n        for(int c = 0; c < C; c++)\
    \ {\n            // \u6B21\u6570\u304C\u6700\u5C0F\u306E\u30CE\u30FC\u30C9\u306F\
    \u5FC5\u305A\u95A2\u7BC0\u70B9\u3067\u306A\u3044\n            // \u305D\u3053\u304B\
    \u3089DFS\u3059\u308C\u3070\u3001\u6839\u30CE\u30FC\u30C9\u306E\u95A2\u7BC0\u70B9\
    \u5224\u5B9A\u3092\u884C\u308F\u306A\u304F\u3066\u3088\u3044\n            for(int\
    \ i = 0; i < decomposed[c].count_nodes(); i++) {\n                st[c] = std::min(st[c],\
    \ {(int)decomposed[c][i].size(), i});\n            }\n        }\n\n        for(int\
    \ c = 0; c < C; c++) {\n            int cnt = 0;\n            dfs(decomposed[c],\
    \ st[c].second, -1, cnt, id[c], is_apt, is_bridge);\n        }\n        for(int\
    \ i = 0; i < N; i++) if(is_apt[i]) apts.push_back(i); \n        for(int i = 0;\
    \ i < M; i++) if(is_bridge[i]) brids.emplace_back(G.edges()[i]); \n    }\n\n \
    \   // unsorted \u3067\u3042\u308B\u3053\u3068\u306B\u6CE8\u610F\n    const std::vector<int>\
    \ &articulation_points(){ return apts; }\n    const std::vector<edge<WEIGHT>>\
    \ &bridges(){ return brids; }\n\n};\n\n\n#endif"
  dependsOn:
  - graph/graph.hpp
  - graph/edge.hpp
  - data_structure/union_find.hpp
  isVerificationFile: false
  path: graph/lowlink.hpp
  requiredBy: []
  timestamp: '2023-06-13 13:16:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/grl-3-a.test.cpp
  - test/grl-3-b.test.cpp
documentation_of: graph/lowlink.hpp
layout: document
redirect_from:
- /library/graph/lowlink.hpp
- /library/graph/lowlink.hpp.html
title: "\u5358\u7D14\u7121\u5411\u30B0\u30E9\u30D5\u306E\u95A2\u7BC0\u70B9\u30FB\u6A4B\
  \u3092\u6C42\u3081\u308B"
---