#ifndef POLYNOMIAL
#define POLYNOMIAL
#include "gandalfr/math/fraction/fraction.hpp"

class polynomial{
  private:
    std::vector<fraction> p;
    std::string variable_name = "x";

    const friend polynomial operator+(const polynomial &a){
        return a;
    }

    const friend polynomial operator-(const polynomial &a){
        return operator*(a, -1);
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
    polynomial(const std::vector<fraction> &vec) : p(vec) {
        while(p.back() == 0 && p.size() != 1) p.pop_back();
    }
    polynomial(const fraction &n)  : polynomial(std::vector<fraction>{n}) {}
    polynomial(long long n) : polynomial(std::vector<fraction>{n}) {}
    polynomial()            : polynomial(std::vector<fraction>{0}) {}

    int max_order(){
        return p.size() - 1;
    }
    
    fraction get(int n){
        assert(0 <= n);
        return (n < p.size() ? p[n] : 0);
    }

    void set(int n, const fraction &x){
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
    
    fraction operator()(const fraction &x){
        fraction ret = 0;
        fraction pwr = 1;
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

};

#endif