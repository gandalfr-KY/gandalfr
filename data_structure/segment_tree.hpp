#ifndef SEGMENT_TREE
#define SEGMENT_TREE
#include <vector>
#include <functional>

template<class T>
struct segment_tree{
  private:
    int n;
    const T e;
    const std::function< T(T, T) > op;
    std::vector<T> node;

  public:
    segment_tree(std::function< T(T, T) > f, T _e) : op(f), e(_e) {}
    
    // 要素の配列 vec で初期化
    void init(const std::vector<T> &vec){
        node.clear();

        int siz = vec.size();
        n = 1; while(n < siz) n *= 2;
        node.resize(2*n-1,e);
        
        for(int i=0; i<siz; i++) node[i+n-1] = vec[i];
        for(int i=n-2; i>=0; i--) node[i] = op(node[2*i+1], node[2*i+2]);
    }

    // 長さ n の単位元の配列で初期化
    void init(int n){ init(std::vector<T>(n, e)); }

    // pos 番目の値を val に更新
    void update(int pos, T val){
        pos += n - 1;
        node[pos] = val;
        while(pos > 0){
            pos = (pos - 1) / 2;
            node[pos] = op(node[2*pos+1], node[2*pos+2]);
        }
    }

    // [a, b) の演算結果を得る 
    // a >= b のとき未定義
    T get(int a, int b, int k=0, int l = 0, int r = -1){
        if(r < 0) r = n;
        if(r <= a || b <= l) return e;
        if(a <= l && r <= b) return node[k];
        T vl = get(a, b, 2*k+1, l, (l+r)/2);
        T vr = get(a, b, 2*k+2, (l+r)/2, r);
        return op(vl, vr);
    }
};

#endif