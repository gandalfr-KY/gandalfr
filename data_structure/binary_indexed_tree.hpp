#ifndef BINARY_INDEXED_TREE
#define BINARY_INDEXED_TREE
#include <vector>

template<class T>
struct binary_indexed_tree{
  private:
    int N;
    std::vector<T> bit;

  public:
    binary_indexed_tree(std::size_t siz) : bit(siz + 1, 0), N(siz) {}

    void add(int a, T w){
        for(int x = a; x <= N; x += x & -x) bit[x] += w;
    }

    T sum(int a){
        T ret = 0;
        for(int x = a; x > 0; x -= x & -x) ret += bit[x];
        return ret;
    }
};

#endif