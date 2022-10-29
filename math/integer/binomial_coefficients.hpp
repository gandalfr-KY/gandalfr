#ifndef BINOMIAL_COEFFICIENTS
#define BINOMIAL_COEFFICIENTS
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

template<class T>
class binomial_coefficients{
  private:
    std::vector<std::vector<T>> pascal = {{1}};
    long long MOD;

  public:
    binomial_coefficients() {}

    T operator()(int n, int k){
        assert(0 <= k && k <= n);
		k = std::min(k, n - k);
        if(n >= pascal.size()){
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
        return pascal[n][k];
    }
};

static binomial_coefficients<boost::multiprecision::cpp_int> nCk_bint;
static binomial_coefficients<long long> nCk;

#endif