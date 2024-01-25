#pragma once
#include <array>
#include <vector>

#include "../standard/Mint.hpp"
#include "../types.hpp"

namespace gandalfr {

template <class T> T power(T x, long long n) {
    T ret = static_cast<T>(1);
    while (n > 0) {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

template <i32 m> struct Factorial {
    Factorial() = delete;
    ~Factorial() = delete;

    static inline std::vector<Mint<m>> fact{1};

    static Mint<m> get(i32 n) {
        while (n >= (i32)fact.size()) {
            fact.push_back(fact.back() * fact.size());
        }
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

// template <i32 m, int N = 1000000>
// struct Factorial {
//     Factorial() = delete;
//     ~Factorial() = delete;

//     static inline constexpr std::array<i32, N + 1> make_array() {
//         std::array<i32, N + 1> a{1};
//         for (int i = 1; i <= N; i++) {
//             a[i] = static_cast<i64>(a[i - 1]) * i % m;
//         }
//         return a;
//     }
//     static inline std::array<int, N + 1> fact = make_array();

//     static Mint<m> get(i32 n) {
//         assert(0 <= n && n <= N);
//         return fact[n];
//     }

//     static Mint<m> permutation(i32 n, i32 k) {
//         assert(0 <= k && k <= n);
//         return get(n) / get(n - k);
//     }

//     static Mint<m> combnation(i32 n, i32 k) {
//         assert(0 <= k && k <= n);
//         return get(n) / (get(k) * get(n - k));
//     }
// };
Mint107 (*fact107)(i32) = Factorial<MOD107>::get;
Mint998 (*fact998)(i32) = Factorial<MOD998>::get;
Mint107 (*perm107)(i32, i32) = Factorial<MOD107>::permutation;
Mint998 (*perm998)(i32, i32) = Factorial<MOD998>::permutation;
Mint107 (*comb107)(i32, i32) = Factorial<MOD107>::combnation;
Mint998 (*comb998)(i32, i32) = Factorial<MOD998>::combnation;
template <i32 m> Mint<m> (*fact)(i32) = Factorial<m>::get;
template <i32 m> Mint<m> (*perm)(i32, i32) = Factorial<m>::permutation;
template <i32 m> Mint<m> (*comb)(i32, i32) = Factorial<m>::combnation;

template <i32 m, i32 b> struct ModPowers {
    ModPowers() = delete;
    ~ModPowers() = delete;

    static inline std::vector<Mint<m>> pows{1};

    static Mint<m> get(i32 n) {
        while (n >= (i32)pows.size()) {
            pows.push_back(pows.back() * b);
        }
        return pows[n];
    }
};
template <i32 m, i32 b> Mint<m> (*modpows)(i32) = ModPowers<m, b>::get;

} // namespace gandalfr
