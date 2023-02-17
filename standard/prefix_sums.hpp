#ifndef PREFIX_SUMS
#define PREFIX_SUMS
#include <vector>
#include <functional>

// [l, r) で区間和を得る
template<class T>
class prefix_sums{
  private:
    int n;
    std::vector<T> acm;
    const std::function< T(T, T) > f;
    const std::function< T(T, T) > f_inv;
    T e;

  public:
    prefix_sums(const std::vector<T> &v,
                 const std::function< T(T, T) > &_f = [](T a, T b){ return a + b; },
                 const std::function< T(T, T) > &_f_inv = [](T a, T b){ return a - b; },
                 const T &_e = 0) : n(v.size()), f(_f), f_inv(_f_inv), e(_e) {
        acm.reserve(n + 1);
        acm.push_back(e);
        for(const T &x : v){
            acm.push_back(f(acm.back(), x));
        }
    }

    T get(int l, int r){
        assert(0 <= l && l < r && r <= n);
        return f_inv(acm[r], acm[l]);
    }
};

template<class T>
class prefix_sums_2d{
  public:
    int h, w;
    std::vector<std::vector<T>> acm;
    const std::function< T(T, T) > f;
    const std::function< T(T, T) > f_inv;
    T e;

  public:
    prefix_sums_2d(const std::vector<std::vector<T>> &v,
                  const std::function< T(T, T) > &_f = [](T a, T b){ return a + b; },
                  const std::function< T(T, T) > &_f_inv = [](T a, T b){ return a - b; },
                  const T &_e = 0) : h(v.size()), w(v[0].size()), f(_f), f_inv(_f_inv), e(_e), acm(h + 1, std::vector<T>(w + 1, _e)) {

        for(int i = 1; i <= h; i++){
            for(int j = 1; j <= w; j++){
                acm[i][j] = f(acm[i][j - 1], v[i - 1][j - 1]);
            }
            for(int j = 1; j <= w; j++){
                acm[i][j] = f(acm[i][j], acm[i - 1][j]);
            }
        }
    }

    T get(int h_begin, int h_end, int w_begin, int w_end){
        assert(0 <= h_begin && h_begin < h_end && h_end <= h);
        assert(0 <= w_begin && w_begin < w_end && w_end <= w);
        // acm[h_end][w_end] - acm[h_end][w_begin] - acm[h_begin][w_end] + acm[h_begin][w_begin] みたいな感じ
        return f(f_inv(f_inv(acm[h_end][w_end], acm[h_end][w_begin]), acm[h_begin][w_end]), acm[h_begin][w_begin]);
    }
};


#endif