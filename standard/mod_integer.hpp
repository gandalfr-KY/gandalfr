#ifndef MOD_INTEGER
#define MOD_INTEGER
#include <iostream>
#include "../math/integer/mod_inverse.hpp"

// mod_integer<P> a := Pを法とするときの整数型;
template<int mod>
class mod_integer{
  private:
    // 値は必ず 0 <= val < mod に保たれる
    long long val;
    friend const mod_integer operator+(const mod_integer &a){
        return a;
    }
    friend const mod_integer operator-(const mod_integer &a){
        return -a.val;
    }
    friend const mod_integer operator+(const mod_integer &a, const mod_integer &b){
        return a.val + b.val; 
    }
    friend const mod_integer operator-(const mod_integer &a, const mod_integer &b){
        return a.val - b.val;
    }
    friend const mod_integer operator*(const mod_integer &a, const mod_integer &b){
        return a.val * b.val;
    }
    friend const mod_integer operator/(const mod_integer &a, const mod_integer &b){
        return a.val * mod_inverse(b.val, mod);
    }

    friend bool operator==(const mod_integer &a, const mod_integer &b){ return a.val == b.val; }
    friend bool operator!=(const mod_integer &a, const mod_integer &b){ return a.val != b.val; }
    
    // map にのせたいので便宜的に定義してます
    friend bool operator>(const mod_integer &a, const mod_integer &b){ return a.val > b.val; }
    friend bool operator>=(const mod_integer &a, const mod_integer &b){ return a.val >= b.val; }
    friend bool operator<(const mod_integer &a, const mod_integer &b){ return a.val < b.val; }
    friend bool operator<=(const mod_integer &a, const mod_integer &b){ return a.val <= b.val; }

  public:
    mod_integer(long long n) : val(n) {
        val %= mod;
        if(val < 0) val += mod;
    }
    mod_integer() : val(0) {}
    int value() const{ return (int)val; }

    const mod_integer &operator=(const mod_integer &a){
        val = a.val;
        return *this;
    }
    const mod_integer &operator+=(const mod_integer &a){
        val += a.val;
        if(val >= mod) val -= mod;
        return *this;
    }
    const mod_integer &operator-=(const mod_integer &a){
        val -= a.val;
        if(val < 0) val += mod;
        return *this;
    }
    const mod_integer &operator*=(const mod_integer &a){
        (val *= a.val) %= mod;
        return *this;
    }
    const mod_integer &operator/=(const mod_integer &a){
        (val *= mod_inverse(a.val, mod)) %= mod;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, mod_integer &a){
        is >> a.val;
        a.val %= mod;
        if(a.val < 0) a.val += mod;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const mod_integer &a) {
        os << a.val;
        return os;
    }
};

#endif