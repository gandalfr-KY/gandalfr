#include <array>
#include <iostream>
#include "atcoder/modint.hpp"

using i32 = int32_t;
using i64 = int64_t;

template <int m> using Mint = atcoder::static_modint<m>;

constexpr i64 MOD998 = 998244353;
constexpr i64 MOD107 = 1000000007;

template <i32 m, i32 N = 1000000>
struct Factorial {
    Factorial() = delete;
    ~Factorial() = delete;

    static inline constexpr std::array<i32, N + 1> make_array() {
        std::array<i32, N + 1> a{};
        a[0] = 1;
        for (i32 i = 1; i <= N; i++) {
            a[i] = static_cast<i64>(a[i - 1]) * i % m;
        }
        return a;
    }
    static inline std::array<i32, N + 1> fact = make_array();

    static Mint<m> get(i32 n) {
        assert(0 <= n && n <= N);
        return fact[n];
    }

    static Mint<m> permutation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return get(n) / get(n - k);
    }

    static Mint<m> combnation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return get(n) / (get(k) * get(n - k));
    }
};

Mint107 (*fact107)(i32) = Factorial<MOD107>::get;
Mint998 (*fact998)(i32) = Factorial<MOD998>::get;
Mint107 (*perm107)(i32, i32) = Factorial<MOD107>::permutation;
Mint998 (*perm998)(i32, i32) = Factorial<MOD998>::permutation;
Mint107 (*comb107)(i32, i32) = Factorial<MOD107>::combnation;
Mint998 (*comb998)(i32, i32) = Factorial<MOD998>::combnation;
template <i32 m> Mint<m> (*fact)(i32) = Factorial<m>::get;
template <i32 m> Mint<m> (*perm)(i32, i32) = Factorial<m>::permutation;
template <i32 m> Mint<m> (*comb)(i32, i32) = Factorial<m>::combnation;


int main(void) {
    
    std::cout << fact998(99999).val() <<std::endl;
    std::cout << comb998(90000, 32845).val() <<std::endl; 
    std::cout << perm998(99245, 49283).val() <<std::endl; 
}

