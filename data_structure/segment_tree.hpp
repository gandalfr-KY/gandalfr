#ifndef SEGMENT_TREE
#define SEGMENT_TREE
#include <vector>
#include <functional>
#include <assert.h>
#include <iostream>
#include <numeric>

template<class T>
class segment_tree{
  private:
    int n, vec_size;
    const T e;
    const std::function< T(T, T) > op;
    std::vector<T> v;

  public:
    // 要素の配列 vec で初期化
    segment_tree(const std::vector<T> &vec, const std::function< T(T, T) > &f, T _e) : vec_size(vec.size()), op(f), e(_e) {
        int siz = vec.size();
        n = 1;
        while(n < siz) n <<= 1;
        v.resize(2 * n - 1, e);
        
        for(int i = 0; i < siz; i++) v[i + n - 1] = vec[i];
        for(int i = n - 2; i >= 0; i--) v[i] = op(v[2 * i + 1], v[2 * i + 2]);
    }

    // 長さ siz の単位元の配列で初期化
    segment_tree(int siz, const std::function< T(T, T) > &f, T _e) : vec_size(siz), op(f), e(_e) {
        n = 1;
        while(n < siz) n *= 2;
        v.resize(2 * n - 1, e);
    }

    // pos 番目の値を val に更新
    void update(int pos, T val){
        pos += n - 1;
        v[pos] = val;
        while(pos > 0){
            pos = (pos - 1) / 2;
            v[pos] = op(v[2 * pos + 1], v[2 * pos + 2]);
        }
    }

    // [l, r) の演算結果を得る 
    // l == r のとき e を返す
    T get(int l, int r){
        assert(0 <= l && l <= r && r <= vec_size);
        T vl = e, vr = e;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) vl = op(vl, v[l - 1]), l++;
            if(r & 1) r--, vr = op(v[r - 1], vr);
        }
        return op(vl, vr);
    }

    // pos 番目の値を得る 
    T get(int pos){
        assert(0 <= pos && pos < vec_size);
        return v[pos + n - 1];
    }

    void print(){
        int prv = 0;
        for(int sz = 1; ; sz *= 2){
            for(int i = 0; i < sz; i++){
                std::cout << v[i + prv] << " ";
            }
            std::cout << std::endl;
            prv += sz;
            if(prv >= 2 * n - 1) break;
        }
    }

};


template<class T>
struct RSQ_segment_tree : public segment_tree<T>{
    RSQ_segment_tree(int size) : RSQ_segment_tree<T>::segment_tree(size, [](T a, T b){ return a + b; }, 0) {};
    RSQ_segment_tree(const std::vector<T> &vec) : RSQ_segment_tree<T>::segment_tree(vec, [](T a, T b){ return a + b; }, 0) {};
};

template<class T>
struct RmQ_segment_tree : public segment_tree<T>{
    RmQ_segment_tree(int size) : RmQ_segment_tree<T>::segment_tree(size, [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};
    RmQ_segment_tree(const std::vector<T> &vec) : RmQ_segment_tree<T>::segment_tree(vec, [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};
};

template<class T>
struct RMQ_segment_tree : public segment_tree<T>{
    RMQ_segment_tree(int size) : RMQ_segment_tree<T>::segment_tree(size, [](T a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};
    RMQ_segment_tree(const std::vector<T> &vec) : RMQ_segment_tree<T>::segment_tree(vec, [](T a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};
};

#endif