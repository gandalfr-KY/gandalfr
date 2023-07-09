---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://blog.hamayanhamayan.com/entry/2017/12/09/015937
  bundledCode: "#line 2 \"data_structure/healthy_2d_segment_tree.hpp\"\n#include <assert.h>\n\
    #include <vector>\n\n/**\n * @see https://blog.hamayanhamayan.com/entry/2017/12/09/015937\n\
    \ */\ntemplate <typename V> class Healthy2DSegTree {\n  private:\n    class InternalSegTree\
    \ {\n      private:\n        int NV;\n        std::vector<V> val;\n\n      public:\n\
    \        inline static V def = 0;\n        static V comp(V &l, V &r) { return\
    \ l + r; }\n        void init(int n) {\n            NV = 1;\n            while\
    \ (NV < n)\n                NV *= 2;\n            val = std::vector<V>(NV * 2,\
    \ def);\n        }\n        V get(int x, int y, int l, int r, int k) {\n     \
    \       if (r <= x || y <= l)\n                return def;\n            if (x\
    \ <= l && r <= y)\n                return val[k];\n            auto a = get(x,\
    \ y, l, (l + r) / 2, k * 2);\n            auto b = get(x, y, (l + r) / 2, r, k\
    \ * 2 + 1);\n            return comp(a, b);\n        }\n        V get(int x, int\
    \ y) { return get(x, y, 0, NV, 1); }\n        void update(int i, V v) {\n    \
    \        i += NV;\n            val[i] = v;\n            while (i > 1)\n      \
    \          i >>= 1, val[i] = comp(val[i * 2], val[i * 2 + 1]);\n        }\n  \
    \      void add(int i, V v) { update(i, val[i + NV] + v); }\n        V operator[](int\
    \ x) { return get(x, x + 1); }\n    };\n\n    int NV;\n    std::vector<InternalSegTree>\
    \ st;\n    std::vector<std::vector<int>> index;\n    V get(int sx, int tx, int\
    \ sy, int ty, int k, int l, int r) {\n        assert(k < NV * 2);\n        assert(l\
    \ < r);\n        if (r <= sx or tx <= l)\n            return InternalSegTree::def;\n\
    \        if (sx <= l and r <= tx) {\n            int syy = lower_bound(index[k].begin(),\
    \ index[k].end(), sy) -\n                      index[k].begin();\n           \
    \ int tyy = lower_bound(index[k].begin(), index[k].end(), ty) -\n            \
    \          index[k].begin();\n            return st[k].get(syy, tyy);\n      \
    \  }\n        int md = (l + r) / 2;\n        V le = get(sx, tx, sy, ty, k * 2,\
    \ l, md);\n        V ri = get(sx, tx, sy, ty, k * 2 + 1, md, r);\n        return\
    \ InternalSegTree::comp(le, ri);\n    }\n\n  public:\n    void init(std::vector<std::vector<int>>\
    \ &v) {\n        int n = v.size();\n        NV = 1;\n        while (NV < n)\n\
    \            NV *= 2;\n        index.resize(2 * NV);\n        for (int i = 0;\
    \ i < n; ++i)\n            for (int j : v[i])\n                index[i + NV].push_back(j);\n\
    \        for (int i = NV * 2 - 1; i >= 1; --i) {\n            sort(index[i].begin(),\
    \ index[i].end());\n            index[i].erase(unique(index[i].begin(), index[i].end()),\n\
    \                           index[i].end());\n            for (auto j : index[i])\n\
    \                index[i / 2].push_back(j);\n        }\n        st.resize(2 *\
    \ NV);\n        for (int i = 1; i < NV * 2; ++i)\n            st[i].init(index[i].size());\n\
    \    }\n    void update(int x, int y, V v) {\n        assert(x < NV);\n      \
    \  x += NV;\n        while (x) {\n            int yy = lower_bound(index[x].begin(),\
    \ index[x].end(), y) -\n                     index[x].begin();\n            assert(yy\
    \ != (int)index[x].size());\n            assert(y == index[x][yy]);\n        \
    \    st[x].update(yy, v);\n            x >>= 1;\n        }\n    }\n    void add(int\
    \ x, int y, V v) {\n        assert(x < NV);\n        x += NV;\n        while (x)\
    \ {\n            int yy = lower_bound(index[x].begin(), index[x].end(), y) -\n\
    \                     index[x].begin();\n            assert(yy != (int)index[x].size());\n\
    \            assert(y == index[x][yy]);\n            st[x].add(yy, v);\n     \
    \       x >>= 1;\n        }\n    }\n    V get(int sx, int tx, int sy, int ty)\
    \ {\n        return get(sx, tx, sy, ty, 1, 0, NV);\n    }\n};\n"
  code: "#pragma once\n#include <assert.h>\n#include <vector>\n\n/**\n * @see https://blog.hamayanhamayan.com/entry/2017/12/09/015937\n\
    \ */\ntemplate <typename V> class Healthy2DSegTree {\n  private:\n    class InternalSegTree\
    \ {\n      private:\n        int NV;\n        std::vector<V> val;\n\n      public:\n\
    \        inline static V def = 0;\n        static V comp(V &l, V &r) { return\
    \ l + r; }\n        void init(int n) {\n            NV = 1;\n            while\
    \ (NV < n)\n                NV *= 2;\n            val = std::vector<V>(NV * 2,\
    \ def);\n        }\n        V get(int x, int y, int l, int r, int k) {\n     \
    \       if (r <= x || y <= l)\n                return def;\n            if (x\
    \ <= l && r <= y)\n                return val[k];\n            auto a = get(x,\
    \ y, l, (l + r) / 2, k * 2);\n            auto b = get(x, y, (l + r) / 2, r, k\
    \ * 2 + 1);\n            return comp(a, b);\n        }\n        V get(int x, int\
    \ y) { return get(x, y, 0, NV, 1); }\n        void update(int i, V v) {\n    \
    \        i += NV;\n            val[i] = v;\n            while (i > 1)\n      \
    \          i >>= 1, val[i] = comp(val[i * 2], val[i * 2 + 1]);\n        }\n  \
    \      void add(int i, V v) { update(i, val[i + NV] + v); }\n        V operator[](int\
    \ x) { return get(x, x + 1); }\n    };\n\n    int NV;\n    std::vector<InternalSegTree>\
    \ st;\n    std::vector<std::vector<int>> index;\n    V get(int sx, int tx, int\
    \ sy, int ty, int k, int l, int r) {\n        assert(k < NV * 2);\n        assert(l\
    \ < r);\n        if (r <= sx or tx <= l)\n            return InternalSegTree::def;\n\
    \        if (sx <= l and r <= tx) {\n            int syy = lower_bound(index[k].begin(),\
    \ index[k].end(), sy) -\n                      index[k].begin();\n           \
    \ int tyy = lower_bound(index[k].begin(), index[k].end(), ty) -\n            \
    \          index[k].begin();\n            return st[k].get(syy, tyy);\n      \
    \  }\n        int md = (l + r) / 2;\n        V le = get(sx, tx, sy, ty, k * 2,\
    \ l, md);\n        V ri = get(sx, tx, sy, ty, k * 2 + 1, md, r);\n        return\
    \ InternalSegTree::comp(le, ri);\n    }\n\n  public:\n    void init(std::vector<std::vector<int>>\
    \ &v) {\n        int n = v.size();\n        NV = 1;\n        while (NV < n)\n\
    \            NV *= 2;\n        index.resize(2 * NV);\n        for (int i = 0;\
    \ i < n; ++i)\n            for (int j : v[i])\n                index[i + NV].push_back(j);\n\
    \        for (int i = NV * 2 - 1; i >= 1; --i) {\n            sort(index[i].begin(),\
    \ index[i].end());\n            index[i].erase(unique(index[i].begin(), index[i].end()),\n\
    \                           index[i].end());\n            for (auto j : index[i])\n\
    \                index[i / 2].push_back(j);\n        }\n        st.resize(2 *\
    \ NV);\n        for (int i = 1; i < NV * 2; ++i)\n            st[i].init(index[i].size());\n\
    \    }\n    void update(int x, int y, V v) {\n        assert(x < NV);\n      \
    \  x += NV;\n        while (x) {\n            int yy = lower_bound(index[x].begin(),\
    \ index[x].end(), y) -\n                     index[x].begin();\n            assert(yy\
    \ != (int)index[x].size());\n            assert(y == index[x][yy]);\n        \
    \    st[x].update(yy, v);\n            x >>= 1;\n        }\n    }\n    void add(int\
    \ x, int y, V v) {\n        assert(x < NV);\n        x += NV;\n        while (x)\
    \ {\n            int yy = lower_bound(index[x].begin(), index[x].end(), y) -\n\
    \                     index[x].begin();\n            assert(yy != (int)index[x].size());\n\
    \            assert(y == index[x][yy]);\n            st[x].add(yy, v);\n     \
    \       x >>= 1;\n        }\n    }\n    V get(int sx, int tx, int sy, int ty)\
    \ {\n        return get(sx, tx, sy, ty, 1, 0, NV);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/healthy_2d_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-07-09 09:57:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/healthy_2d_segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/healthy_2d_segment_tree.hpp
- /library/data_structure/healthy_2d_segment_tree.hpp.html
title: data_structure/healthy_2d_segment_tree.hpp
---
