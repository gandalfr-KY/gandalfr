#ifndef BINOMIAL_COEFFICIENTS
#define BINOMIAL_COEFFICIENTS
#include <vector>

template<class T>
class binomial_coefficients{
  private:
    std::vector<std::vector<T>> pascal = {{1}};

    // テーブルを n+1 行まで拡張 ( = pascal[n][k] にアクセスできるようにする)
    void expand(int n){
        pascal.reserve(n + 1);
        for(int i=pascal.size(); i<=n; i++){
            pascal.emplace_back(std::vector<T>(i / 2 + 1));
            for(int j=0; j<=i/2; j++){
                int index1 = std::min(j - 1, i - 1 - (j - 1));
                int index2 = std::min(j, i - 1 - (j));
                pascal[i][j] = (index1 >= 0 ? pascal[i-1][index1] : 0) + (index2 >= 0 ? pascal[i-1][index2] : 0);
            }
        }
    }

  protected:
    T get(int n, int k){
        if(n >= pascal.size()) expand(n);
        return pascal[n][std::min(k, (2 * k < n ? k : n - k))];
    }

  public:
    T operator()(int n, int k){
        assert(0 <= k && k <= n);
		return get(n, k);
    }
};

#endif