#ifndef BINOMIAL_COEFFICIENTS
#define BINOMIAL_COEFFICIENTS
#include <vector>

template<int mod>
class binomial_coefficients{
  private:
    std::vector<std::vector<long long>> pascal = {{1}};

  public:
    binomial_coefficients(){}

    long long operator()(int n, int k){
        assert(0 <= k && k <= n);
		k = std::min(k, n - k);
        if(n >= pascal.size()){
			pascal.reserve(n + 1);
            for(int i=pascal.size(); i<=n; i++){
                pascal.emplace_back(std::vector<long long>(i / 2 + 1));
                for(int j=0; j<=i/2; j++){
					int index1 = std::min(j - 1, i - 1 - (j - 1));
					int index2 = std::min(j, i - 1 - (j));
                    pascal[i][j] = (index1 >= 0 ? pascal[i-1][index1] : 0) + (index2 >= 0 ? pascal[i-1][index2] : 0);
                    pascal[i][j] %= mod;
                }
            }
        }
        return pascal[n][k];
    }
};

#endif