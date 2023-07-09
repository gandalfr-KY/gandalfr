#pragma once
#include <assert.h>
#include <vector>

/**
 * @see https://blog.hamayanhamayan.com/entry/2017/12/09/015937
 */
template <typename V> class Healthy2DSegTree {
  private:
    class InternalSegTree {
      private:
        int NV;
        std::vector<V> val;

      public:
        inline static V def = 0;
        static V comp(V &l, V &r) { return l + r; }
        void init(int n) {
            NV = 1;
            while (NV < n)
                NV *= 2;
            val = std::vector<V>(NV * 2, def);
        }
        V get(int x, int y, int l, int r, int k) {
            if (r <= x || y <= l)
                return def;
            if (x <= l && r <= y)
                return val[k];
            auto a = get(x, y, l, (l + r) / 2, k * 2);
            auto b = get(x, y, (l + r) / 2, r, k * 2 + 1);
            return comp(a, b);
        }
        V get(int x, int y) { return get(x, y, 0, NV, 1); }
        void update(int i, V v) {
            i += NV;
            val[i] = v;
            while (i > 1)
                i >>= 1, val[i] = comp(val[i * 2], val[i * 2 + 1]);
        }
        void add(int i, V v) { update(i, val[i + NV] + v); }
        V operator[](int x) { return get(x, x + 1); }
    };

    int NV;
    std::vector<InternalSegTree> st;
    std::vector<std::vector<int>> index;
    V get(int sx, int tx, int sy, int ty, int k, int l, int r) {
        assert(k < NV * 2);
        assert(l < r);
        if (r <= sx or tx <= l)
            return InternalSegTree::def;
        if (sx <= l and r <= tx) {
            int syy = lower_bound(index[k].begin(), index[k].end(), sy) -
                      index[k].begin();
            int tyy = lower_bound(index[k].begin(), index[k].end(), ty) -
                      index[k].begin();
            return st[k].get(syy, tyy);
        }
        int md = (l + r) / 2;
        V le = get(sx, tx, sy, ty, k * 2, l, md);
        V ri = get(sx, tx, sy, ty, k * 2 + 1, md, r);
        return InternalSegTree::comp(le, ri);
    }

  public:
    void init(std::vector<std::vector<int>> &v) {
        int n = v.size();
        NV = 1;
        while (NV < n)
            NV *= 2;
        index.resize(2 * NV);
        for (int i = 0; i < n; ++i)
            for (int j : v[i])
                index[i + NV].push_back(j);
        for (int i = NV * 2 - 1; i >= 1; --i) {
            sort(index[i].begin(), index[i].end());
            index[i].erase(unique(index[i].begin(), index[i].end()),
                           index[i].end());
            for (auto j : index[i])
                index[i / 2].push_back(j);
        }
        st.resize(2 * NV);
        for (int i = 1; i < NV * 2; ++i)
            st[i].init(index[i].size());
    }
    void update(int x, int y, V v) {
        assert(x < NV);
        x += NV;
        while (x) {
            int yy = lower_bound(index[x].begin(), index[x].end(), y) -
                     index[x].begin();
            assert(yy != (int)index[x].size());
            assert(y == index[x][yy]);
            st[x].update(yy, v);
            x >>= 1;
        }
    }
    void add(int x, int y, V v) {
        assert(x < NV);
        x += NV;
        while (x) {
            int yy = lower_bound(index[x].begin(), index[x].end(), y) -
                     index[x].begin();
            assert(yy != (int)index[x].size());
            assert(y == index[x][yy]);
            st[x].add(yy, v);
            x >>= 1;
        }
    }
    V get(int sx, int tx, int sy, int ty) {
        return get(sx, tx, sy, ty, 1, 0, NV);
    }
};
