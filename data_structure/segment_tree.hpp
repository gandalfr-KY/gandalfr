#ifndef SEGMENT_TREE
#define SEGMENT_TREE
#include <vector>
#include <functional>

template<class T>
class segment_tree{
  private:
    int n;
    const T e;
    const std::function< T(T, T) > op;
    std::vector<T> dat;

  public:
    segment_tree(const std::function< T(T, T) > &f, T _e) : op(f), e(_e) {}
    
    // 要素の配列 vec で初期化
    void init(const std::vector<T> &vec){
        dat.clear();

        int siz = vec.size();
        n = 1;
        while(n < siz) n *= 2;
        dat.resize(2 * n - 1, e);
        
        for(int i =0; i < siz; i++) dat[i + n - 1] = vec[i];
        for(int i = n - 2; i >= 0; i--) dat[i] = op(dat[2 * i + 1], dat[2 * i + 2]);
    }

    // 長さ n の単位元の配列で初期化
    void init(int n){ init(std::vector<T>(n, e)); }

    // pos 番目の値を val に更新
    void update(int pos, T val){
        pos += n - 1;
        dat[pos] = val;
        while(pos > 0){
            pos = (pos - 1) / 2;
            dat[pos] = op(dat[2 * pos + 1], dat[2 * pos + 2]);
        }
    }

    // [a, b) の演算結果を得る 
    // a >= b のとき未定義
    T get(int l, int r){ return get(l, r, 0, 0, n); }

  private:
    T get(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return e;
        if(a <= l && r <= b) return dat[k];
        T vl = get(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = get(a, b, 2 * k + 2, (l + r) / 2, r);
        return op(vl, vr, 0, 0, -1);
    }

};

#endif