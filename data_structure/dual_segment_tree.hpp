#ifndef DUAL_SEGMENT_TREE
#define DUAL_SEGMENT_TREE
#include <vector>
#include <functional>
#include <assert.h>
#include <iostream>
#include <optional>

/*
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627486#1
 */
template<class T>
class dual_segment_tree{
  private:
    int n, vec_size;
    const T e;
    const std::function< T(T, T) > op;
    std::vector<T> v;

  public:
    // 要素の配列 vec で初期化
    dual_segment_tree(const std::vector<T> &vec, const std::function< T(T, T) > &f, T _e) : vec_size(vec.size()), op(f), e(_e) {
        int siz = vec.size();
        n = 1;
        while(n < siz) n *= 2;
        v.resize(2 * n - 1, e);
        for(int i = 0; i < siz; i++) v[i + n - 1] = vec[i];
    }

    // 長さ siz の単位元の配列で初期化
    dual_segment_tree(int siz, const std::function< T(T, T) > &f, T _e) : vec_size(siz), op(f), e(_e) {
        n = 1;
        while(n < siz) n *= 2;
        v.resize(2 * n - 1, e);
    }

    // pos 番目の値を得る
    T get(int pos){
        pos += n - 1;
        T ret = v[pos];
        while(pos > 0){
            pos = (pos - 1) / 2;
            ret = op(ret, v[pos]);
        }
        return ret;
    }

    // [l, r) に action を作用する 
    void act(int l, int r, T action){
        assert(0 <= l && l <= r && r <= vec_size);
        if(l == r) return;
        act(l, r, 0, 0, n, action);
    }

    void print(){
        for(int i = 0; i < vec_size; i++){
            std::cout << get(i) << (i == vec_size - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

  private:
    void act(int a, int b, int k, int l, int r, T action){
        if(r <= a || b <= l) return;
        if(a <= l && r <= b){
            v[k] = op(v[k], action);
            return;
        }
        act(a, b, 2 * k + 1, l, (l + r) / 2, action);
        act(a, b, 2 * k + 2, (l + r) / 2, r, action);
    }
};

template<class T>
struct RAQ_dual_segment_tree : public dual_segment_tree<T>{
    RAQ_dual_segment_tree(int size) : RAQ_dual_segment_tree<T>::dual_segment_tree(size, [](T a, T b){ return a + b; }, 0) {};
    RAQ_dual_segment_tree(const std::vector<T> &vec) : RAQ_dual_segment_tree<T>::dual_segment_tree(vec, [](T a, T b){ return a + b; }, 0) {};
};

/* 
 * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627473#1
 */
template<class T>
class RUQ_dual_segment_tree{
  private:
    int n, tm = 0, vec_size;
    std::vector<std::pair<int, T>> v;

  public:
    // 要素の配列 vec で初期化
    RUQ_dual_segment_tree(const std::vector<T> &vec) : vec_size(vec.size()) {
        int siz = vec.size();
        n = 1;
        while(n < siz) n *= 2;
        v.resize(2 * n - 1);
        for(auto &x : v) x.first = -1;
        for(int i = 0; i < siz; i++) v[i + n - 1].second = vec[i];
    }

    // 長さ siz の単位元の配列で初期化
    RUQ_dual_segment_tree(int siz) : vec_size(siz) {
        n = 1;
        while(n < siz) n *= 2;
        v.resize(2 * n - 1);
        for(auto &x : v) x.first = -1;
    }

    // pos 番目の値を得る
    T get(int pos){
        pos += n - 1;
        std::pair<int, T> ret = v[pos];
        while(pos > 0){
            pos = (pos - 1) / 2;
            ret = std::max(ret, v[pos]);
        }
        return ret.second;
    }

    // [l, r) に action を作用する 
    void act(int l, int r, T action){
        assert(0 <= l && l <= r && r <= vec_size);
        if(l == r) return;
        act(l, r, 0, 0, n, {tm, action});
        tm++;
    }

    void print(){
        for(int i = 0; i < vec_size; i++){
            std::cout << get(i) << (i == vec_size - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

  private:
    void act(int a, int b, int k, int l, int r, std::pair<int, T> action){
        if(r <= a || b <= l) return;
        if(a <= l && r <= b){
            v[k] = std::max(v[k], action);
            return;
        }
        act(a, b, 2 * k + 1, l, (l + r) / 2, action);
        act(a, b, 2 * k + 2, (l + r) / 2, r, action);
    }
};




#endif