#ifndef BERNOULLI_NUMBER
#define BERNOULLI_NUMBER
#include "gandalfr/standard/power.hpp"
#include "gandalfr/math/integer/binomial_coefficients.hpp"
#include "gandalfr/math/integer/mod_inverse.hpp"

/* Bernoulli_number<value_type> B;
 * B(n) := ベルヌーイ数の第n項
 */
template<class T>
class Bernoulli_number {
  private:
    static std::vector<T> B;

    static void expand(int n){
        for(int m = B.size(); m < n; m++){
            if(B.empty()){
                B.emplace_back(1);
            }
            else if(B.size() == 1){
                B.emplace_back((T)1 / 2);
            }
            else if(m % 2 == 1){
                B.push_back(0);
            }
            else{
                T res = 0;
                for(int i = 0; i < n; i++){
                    T tmp = 0;
                    for(int j = i; j < n; j++) tmp += binomial_coefficients<T>::get(j, i) / (j + 1);
                    if(i % 2 == 0) res += tmp * power<T>(i, n - 1);
                    else           res -= tmp * power<T>(i, n - 1);
                }
                B.push_back(res);
            }   
        }
    }

  public:
    Bernoulli_number() = delete;
    ~Bernoulli_number() = delete;

	static void resize(int siz){
		if(B.size() > siz){
			while(B.size() - siz > 0){
				B.pop_back();
			}
		}
		else{
			expand(siz);
		}
	}

    static T get(int n){
        if(n >= B.size()) expand(n + 1);
        return B[n];
    }

    static const std::vector<T> &list(){ return B; }

};
template<class T>
std::vector<T> Bernoulli_number<T>::B;

#endif