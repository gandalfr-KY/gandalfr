#ifndef BINARY_INDEXED_TREE
#define BINARY_INDEXED_TREE
#include <vector>

/**
 * @brief 一点加算、区間和の取得
 * @attention 0-indexed
 */
template <class T> struct binary_indexed_tree {
  private:
    int N;
    std::vector<T> bit;

  public:
    binary_indexed_tree(int siz) : N(siz), bit(N, 0) {}

    /**
     * @return a の位置に w を加算
     */
    void add(int a, T w) {
        for (int x = a + 1; x <= N; x += x & -x)
            bit[x - 1] += w;
    }

    /**
     * @return [0, a) の総和
     */
    T get(int a) {
        T ret = 0;
        for (int x = a; x > 0; x -= x & -x)
            ret += bit[x - 1];
        return ret;
    }
};

#endif
