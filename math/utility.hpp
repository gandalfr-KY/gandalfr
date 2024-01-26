#pragma once
#include <array>
#include <vector>

#include "../standard/Mint.hpp"
#include "../types.hpp"

namespace gandalfr {

template <i32 m> struct CombinatoricsUtility {
  private:
    static inline std::vector<Mint<m>> fact{1, 1}, invmod{0, 1}, invfact{0, 1};
    template <i32 b> static inline std::vector<Mint<m>> pows{1};

    static std::tuple<Mint<m>, Mint<m>, Mint<m>> get(i32 n) {
        while (n >= (i32)fact.size()) {
            i32 s = fact.size();
            auto [dv, md] = std::div(m, s);
            fact.push_back(fact[s - 1] * s);
            invmod.push_back(-invmod[md] * dv);
            invfact.push_back(invfact[s - 1] * invmod[s]);
        }
        return std::make_tuple(fact[n], invmod[n], invfact[n]);
    }

  public:
    CombinatoricsUtility() = delete;
    ~CombinatoricsUtility() = delete;

    static Mint<m> factorial(i32 n) { return std::get<0>(get(n)); }

    static Mint<m> invMod(i32 n) { return std::get<1>(get(n)); }

    static Mint<m> invFactorial(i32 n) { return std::get<2>(get(n)); }

    static Mint<m> permutation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return factorial(n) * invFactorial(n - k);
    }

    static Mint<m> combnation(i32 n, i32 k) {
        assert(0 <= k && k <= n);
        return factorial(n) * invFactorial(k) * invFactorial(n - k);
    }

    // n 種から重複を許して k 個選ぶ
    static Mint<m> homogeneous(i32 n, i32 k) {
        return combnation(n + k - 1, k);
    }

    template <i32 b> static Mint<m> powMod(i32 n) {
        while (n >= (i32)pows<b>.size()) {
            pows<b>.push_back(pows<b>.back() * b);
        }
        return pows<b>[n];
    }
};

Mint107 (*fact107)(i32) = CombinatoricsUtility<MOD107>::factorial;
Mint998 (*fact998)(i32) = CombinatoricsUtility<MOD998>::factorial;
Mint107 (*invFact107)(i32) = CombinatoricsUtility<MOD107>::invFactorial;
Mint998 (*invFact998)(i32) = CombinatoricsUtility<MOD998>::invFactorial;
Mint107 (*perm107)(i32, i32) = CombinatoricsUtility<MOD107>::permutation;
Mint998 (*perm998)(i32, i32) = CombinatoricsUtility<MOD998>::permutation;
Mint107 (*comb107)(i32, i32) = CombinatoricsUtility<MOD107>::combnation;
Mint998 (*comb998)(i32, i32) = CombinatoricsUtility<MOD998>::combnation;
Mint107 (*homo107)(i32, i32) = CombinatoricsUtility<MOD107>::homogeneous;
Mint998 (*homo998)(i32, i32) = CombinatoricsUtility<MOD998>::homogeneous;
Mint107 (*inv107)(i32) = CombinatoricsUtility<MOD107>::invMod;
Mint998 (*inv998)(i32) = CombinatoricsUtility<MOD998>::invMod;
template <i32 b>
Mint998 (*powMod998)(i32) = CombinatoricsUtility<MOD998>::powMod<b>;
template <i32 b>
Mint107 (*powMod107)(i32) = CombinatoricsUtility<MOD107>::powMod<b>;
template <i32 m> Mint<m> (*fact)(i32) = CombinatoricsUtility<m>::factorial;
template <i32 m>
Mint<m> (*invFact)(i32) = CombinatoricsUtility<m>::invFactorial;
template <i32 m>
Mint<m> (*perm)(i32, i32) = CombinatoricsUtility<m>::permutation;
template <i32 m>
Mint<m> (*comb)(i32, i32) = CombinatoricsUtility<m>::combnation;
template <i32 m>
Mint<m> (*homo)(i32, i32) = CombinatoricsUtility<m>::homogeneous;
template <i32 m> Mint<m> (*inv)(i32) = CombinatoricsUtility<m>::invMod;
template <i32 m, i32 b>
Mint<m> (*powMod)(i32) = CombinatoricsUtility<m>::template powMod<b>;
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

} // namespace gandalfr
