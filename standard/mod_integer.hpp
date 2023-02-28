#ifndef MOD_INTEGER
#define MOD_INTEGER
#include <iostream>
#include "gandalfr/math/integer/mod_inverse.hpp"

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
        return -a.val + mod;
    }

    friend const mod_integer operator+(const mod_integer &a, const mod_integer &b){
        return (a.val + b.val) % mod; 
    }

    friend const mod_integer operator-(const mod_integer &a, const mod_integer &b){
        long long ret = a.val - b.val;
        if(ret < 0) ret += mod;
        return ret;
    }

    friend const mod_integer operator*(const mod_integer &a, const mod_integer &b){
        return a.val * b.val % mod;
    }

    friend const mod_integer operator/(const mod_integer &a, const mod_integer &b){
        return a.val * mod_inverse<long long>(b.val, mod) % mod;
    }

    friend bool operator==(const mod_integer &a, const mod_integer &b){ return a.val == b.val; }
    friend bool operator!=(const mod_integer &a, const mod_integer &b){ return a.val != b.val; }
    
    // map にのせたいので便宜的に定義してます
    friend bool operator>(const mod_integer &a, const mod_integer &b){ return a.val > b.val; }
    friend bool operator>=(const mod_integer &a, const mod_integer &b){ return a.val >= b.val; }
    friend bool operator<(const mod_integer &a, const mod_integer &b){ return a.val < b.val; }
    friend bool operator<=(const mod_integer &a, const mod_integer &b){ return a.val <= b.val; }

  public:
    mod_integer(long long n) {
        n %= mod;
        if(n < 0) n += mod;
        val = n;
    }
    mod_integer(const mod_integer &a) : val(a.val) {}
    mod_integer() : val(0) {}
    // 値を返す
    long long value() const{ return val; }

    mod_integer &operator=(const mod_integer &a){
        val = a.val;
        return *this;
    }

    void operator+=(const mod_integer &a){
        val = (val + a.val) % mod;
    }

    void operator-=(const mod_integer &a){
        val = (val - a.val) % mod;
        if(val < 0) val += mod;
    }

    void operator*=(const mod_integer &a){
        val = val * a.val % mod;
    }

    void operator/=(const mod_integer &a){
        val = val * mod_inverse<long long>(a.val, mod) % mod;
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