#pragma once
#include <iostream>
#include <queue>
#include <utility>

#include "../math/mod_inverse.hpp"

// mod_integer<P> a := Pを法とするときの整数型;
template <int mod> class mod_integer {
  private:
    long long val; // 値は必ず 0 <= val < mod に保たれる
    static inline std::deque<std::pair<int, int>> modinv_cache; // 逆元のキャッシュ
    static inline const int cache_size = 8;
    friend mod_integer operator+(const mod_integer &a) { return a; }
    friend mod_integer operator-(const mod_integer &a) { return -a.val; }
    friend mod_integer operator+(const mod_integer &a, const mod_integer &b) {
        return mod_integer(a.val + b.val);
    }
    friend mod_integer operator-(const mod_integer &a, const mod_integer &b) {
        return mod_integer(a.val - b.val);
    }
    friend mod_integer operator*(const mod_integer &a, const mod_integer &b) {
        return mod_integer(a.val * b.val);
    }
    friend mod_integer operator/(const mod_integer &a, const mod_integer &b) {
        return mod_integer(a.val * mod_inverse(b.val, mod));
    }

    friend bool operator==(const mod_integer &a, const mod_integer &b) {
        return a.val == b.val;
    }
    friend bool operator!=(const mod_integer &a, const mod_integer &b) {
        return a.val != b.val;
    }

    // map とかに乗せたいので、便宜的に定義
    friend bool operator<(const mod_integer &a, const mod_integer &b) {
        return a.val < b.val;
    }

  public:
    mod_integer(long long n) : val(n) {
        val %= mod;
        if (val < 0)
            val += mod;
    }
    mod_integer() : val(0) {}
    int value() const { return (int)val; }

    mod_integer &operator=(const mod_integer &a) = default;
    mod_integer &operator+=(const mod_integer &a) {
        val += a.val;
        if (val >= mod)
            val -= mod;
        return *this;
    }
    mod_integer &operator-=(const mod_integer &a) {
        val -= a.val;
        if (val < 0)
            val += mod;
        return *this;
    }
    mod_integer &operator*=(const mod_integer &a) {
        (val *= a.val) %= mod;
        return *this;
    }
    mod_integer &operator/=(const mod_integer &a) {
        bool found = false;
        for(auto& [k, v] : modinv_cache) if(k == a.val) {
            found = true;
            (val *= v) %= mod;
            break;
        }
        if(!found) {
            int inv = mod_inverse(a.val, mod);
            (val *= inv) %= mod;
            modinv_cache.push_back({a.val, inv});
            if ((int)modinv_cache.size() > cache_size)
                modinv_cache.pop_front();
        }
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, mod_integer &a) {
        is >> a.val;
        a.val %= mod;
        if (a.val < 0)
            a.val += mod;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const mod_integer &a) {
        os << a.val;
        return os;
    }
};

using mint = mod_integer<1000000007>;
using _mint = mod_integer<998244353>;
