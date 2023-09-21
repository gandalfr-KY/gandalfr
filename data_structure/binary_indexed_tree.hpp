#pragma once
#include <vector>

/**
 * @brief 一点加算、区間和の取得
 * @attention 0-indexed
 */
template <class T> struct binary_indexed_tree {
  private:
    int N;
    std::vector<T> bit;

    /**
     * @return a の位置に w を加算
     */
    void add(int a, T w) {
        for (int x = a + 1; x <= N; x += x & -x)
            bit[x - 1] += w;
    }

    class RefWrapper {
      private:
        binary_indexed_tree &base;
        int pos;

      public:
        RefWrapper(binary_indexed_tree &s, int p) : base(s), pos(p) {}
        RefWrapper operator=(const T &value) {
            base.add(pos, value - *this);
            return *this;
        }
        operator T() const { return base(pos, pos + 1); }
    };

  public:
    binary_indexed_tree(int siz) : N(siz), bit(siz, 0) {}
    binary_indexed_tree(const std::vector<T> &vec)
        : N(vec.size()), bit(vec.size(), 0) {
        for (int x = 0; x < N; ++x)
            bit[x] = vec[x];
        for (int x = 1; x < N; ++x) {
            int idx = x + (x & -x) - 1;
            if (idx < N)
                bit[idx] += bit[x - 1];
        }
    }

    /**
     * @return [l, r) の総和
     */
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= N);
        T ret = 0;
        for (int x = r; x > 0; x -= x & -x)
            ret += bit[x - 1];
        for (int x = l; x > 0; x -= x & -x)
            ret -= bit[x - 1];
        return ret;
    }

    // pos 番目の値を更新
    // 代入操作のみ受理
    RefWrapper operator[](int pos) {
        assert(0 <= pos && pos < N);
        return RefWrapper(*this, pos);
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const binary_indexed_tree &a) {
        for (int i = 0; i < a.N; i++)
            os << a(i, i + 1) << (i + 1 != (int)a.N ? " " : "");
        return os;
    }
};
