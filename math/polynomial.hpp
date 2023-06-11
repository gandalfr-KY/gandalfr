#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <vector>
#include <string>
#include <algorithm>

/**
 * @deprecated 積がO(n^2)でおそい。強い人のライブラリを使おう。
 */
template<class coef>
class polynomial{
  private:
    std::vector<coef> p;
    std::string variable_name = "x";

    const friend polynomial operator+(const polynomial &a){
        return a;
    }

    const friend polynomial operator-(const polynomial &a){
        polynomial<coef> ret(a);
        for(coef &c : ret) c *= -1;
        return ret;
    }

    friend const polynomial operator+(const polynomial &a, const polynomial &b){
        int siz = std::max(a.p.size(), b.p.size());
        int siz1 = a.p.size(), siz2 = b.p.size();
        polynomial ret;
        ret.p.resize(siz);
        for(int i=0; i<siz; i++){
            ret.p[i] = (i < siz1 ? a.p[i] : 0) + (i < siz2 ? b.p[i] : 0);
        }
        while(ret.p.back() == 0 && ret.p.size() != 1) ret.p.pop_back();
        return ret;
    }

    friend const polynomial operator-(const polynomial &a, const polynomial &b){
        int siz = std::max(a.p.size(), b.p.size());
        int siz1 = a.p.size(), siz2 = b.p.size();
        polynomial ret;
        ret.p.resize(siz);
        for(int i=0; i<siz; i++){
            ret.p[i] = (i < siz1 ? a.p[i] : 0) - (i < siz2 ? b.p[i] : 0);
        }
        while(ret.p.back() == 0 && ret.p.size() != 1) ret.p.pop_back();
        return ret;
    }

    friend const polynomial operator*(const polynomial &a, const polynomial &b){
        int siz1 = a.p.size(), siz2 = b.p.size();
        polynomial ret;
        ret.p.resize(siz1 + siz2 - 1);
        for(int i=0; i<siz1; i++) for(int j=0; j<siz2; j++) ret.p[i + j] += a.p[i] * b.p[j];
        return ret;
    }

    friend const polynomial operator/(const polynomial &a, const polynomial &b){
        int siz1 = a.p.size(), siz2 = b.p.size();
        if(siz1 < siz2) return {0};
        polynomial ret, remain(a);
        ret.p.resize(siz1 - siz2 + 1, 0);
        for(int i=siz1-siz2; i>=0; i--){
            ret.p[i] = remain.p.back() / b.p.back();
            for(int j=1; j<siz2; j++){
                remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];
            }
            remain.p.pop_back();
        }
        return ret;
    }

    friend const polynomial operator%(const polynomial &a, const polynomial &b){
        int siz1 = a.p.size(), siz2 = b.p.size();
        if(siz1 < siz2) return {0};
        polynomial ret, remain(a);
        ret.p.resize(siz1 - siz2 + 1, 0);
        for(int i=siz1-siz2; i>=0; i--){
            ret.p[i] = remain.p.back() / b.p.back();
            for(int j=1; j<siz2; j++){
                remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];
            }
            remain.p.pop_back();
        }
        return remain;
    }

    friend int compare(const polynomial &a, const polynomial &b){
        int siz1 = a.p.size();
        int siz2 = b.p.size();
        if(siz1 > siz2) return +1;
        if(siz1 < siz2) return -1;
        for(int i=siz1-1; i>=0; i--) {
            if(a.p[i] > b.p[i]) return +1;
            if(a.p[i] < b.p[i]) return -1;
        }
        return 0;
    }

    friend bool operator==(const polynomial &a, const polynomial &b){
        return (compare(a, b) == 0);
    }

    friend bool operator!=(const polynomial &a, const polynomial &b){
        return (compare(a, b) != 0);
    }

    friend bool operator<(const polynomial &a, const polynomial &b){
        return (compare(a, b) < 0);
    }

    friend bool operator<=(const polynomial &a, const polynomial &b){
        return (compare(a, b) <= 0);
    }

    friend bool operator>(const polynomial &a, const polynomial &b){
        return (compare(a, b) > 0);
    }

    friend bool operator>=(const polynomial &a, const polynomial &b){
        return (compare(a, b) >= 0);
    }

  public:
    polynomial(const std::vector<coef> &vec) : p(vec) {
        while(p.back() == 0 && p.size() != 1) p.pop_back();
    }
    polynomial(const coef &n = 0)  : polynomial(std::vector<coef>{n}) {}

    int max_order() const {
        return p.size() - 1;
    }
    
    coef get_coef(int n) const {
        assert(0 <= n);
        return (n < p.size() ? p[n] : 0);
    }

    void set_coef(int n, const coef &x){
        assert(0 <= n);
        if(n >= p.size()) p.resize(n + 1, 0);
        p[n] = x;
        while(p.back() == 0 && p.size() != 1) p.pop_back();
    }

    polynomial &operator=(const polynomial &a){
        p = a.p;
        return *this;
    }

    void operator+=(const polynomial &a){
        *this = operator+(*this, a);
    }

    void operator-=(const polynomial &a){
        *this = operator-(*this, a);
    }

    void operator*=(const polynomial &a){
        *this = operator*(*this, a);
    }

    void operator/=(const polynomial &a){
        *this = operator/(*this, a);
    }

    void operator%=(const polynomial &a){
        *this = operator%(*this, a);
    }

    coef operator[](int n) const{
        return get_coef(n);
    }
    
    coef operator()(const coef &x) const{
        coef ret = 0;
        coef pwr = 1;
        for(int i=0; i<p.size(); i++){
            ret += p[i] * pwr;
            pwr *= x;
        }
        return ret;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const polynomial &a) {
        if(a.p.size() == 1 && a.p[0] == 0) os << "0";
        else for(int i=a.p.size()-1; i>=0; i--){
            if(a.p[i] == 0) continue;
            std::string sign;
            if(i != a.p.size()-1 && a.p[i] > 0) sign = "+ ";
            if(a.p[i] < 0) sign = "- ";
            os << sign << (a.p[i] >= 0 ? a.p[i] : a.p[i]) << ' ' << a.variable_name << '^' << i << ' ';
        }
        return os;
    }
    
    polynomial<coef> integrate(){
        polynomial<coef> ret(*this);
        for(int i=1; i<=max_order()+1; i++){
            ret.set_coef(i, get_coef(i-1) / i);
        }
        return ret;
    }

    polynomial<coef> differentiate(){
        polynomial<coef> ret;
        for(int i=0; i<max_order(); i++){
            ret.set_coef(i, get_coef(i + 1) * (i + 1));
        }
        return ret;
    }

};

#endif