#pragma once
#include <algorithm>
#include <limits>

#include "../math/matrix.hpp"
#include "../math/enumeration_utility.hpp"

/**
 * @brief モノイド
 * @tparam Op 結合律を満たす T について閉じた二項演算
 * @tparam Id 二項演算の単位元
 */
template <typename T, T (*Op)(T, T), T (*Id)()> struct Monoid {
    using VType = T;
    static T op(T a, T b) { return Op(a, b); }
    static constexpr T id() { return Id(); }
};

/**
 * @brief 群
 * @tparam Rev 逆元を求める単項演算（例: 加法なら、-1 をかける操作）
 */
template <typename T, T (*Op)(T, T), T (*Rev)(T), T (*Id)()>
struct Group : public Monoid<T, Op, Id> {
    static T rev(T a) { return Rev(a); }
};

/**
 * @brief 作用素
 * @tparam S 要素に対して作用する値の型
 * @tparam Op 結合律を満たす S について閉じた二項演算
 * @tparam Id モノイドの単位元 作用素 F(x, Id) == x を満たすことが要件
 * @tparam T 作用される要素の型
 * @tparam F ある要素に対する作用素
 */
template <typename S, S(*Op)(S, S), S (*Id)(), typename T, T (*F)(T, S)> struct MonoidAction :
public Monoid<S, Op, Id> {
    using VType = T;
    using AType = S;
    static T f(T x, S y) { return F(x, y); }
};

namespace internal {
template <typename T> constexpr T zero() { return 0; }
template <typename T> constexpr T one() { return 1; }
template <typename T> constexpr T maximum() {
    return std::numeric_limits<T>::max();
}
template <typename T> constexpr T minimum() {
    return std::numeric_limits<T>::lowest();
}
template <typename T> constexpr T all_bits_set() { return ~T(0); }
template <typename T> constexpr T empty_matrix() { return T::E(0); }

template <typename T> T plus(T a, T b) { return a + b; }
template <typename T> T plus_rev(T a) { return -a; }

template <typename T> T matrix_plus(T a, T b) {
    if (a == internal::empty_matrix<T>())
        return b;
    if (b == internal::empty_matrix<T>())
        return a;
    return a + b;
}
template <typename T> T matrix_plus_rev(T a) { return -a; }

template <typename T> T mult(T a, T b) { return a * b; }
template <typename T> T mult_rev(T a) { return internal::one<T>() / a; }

template <typename T> T matrix_mult(T a, T b) {
    if (a == internal::empty_matrix<T>())
        return b;
    if (b == internal::empty_matrix<T>())
        return a;
    return b * a;
}

template <typename T> T min(T a, T b) { return std::min(a, b); }

template <typename T> T max(T a, T b) { return std::max(a, b); }

template <typename T> T gcd(T a, T b) {
    if (a == internal::maximum<T>())
        return b;
    if (b == internal::maximum<T>())
        return a;
    return std::gcd(a, b);
}

template <typename T> T lcm(T a, T b) { return std::lcm(a, b); }

template <typename T> T _xor(T a, T b) { return a ^ b; }

template <typename T> T _and(T a, T b) { return a & b; }

template <typename T> T _or(T a, T b) { return a | b; }

template <typename T> T id_f(T a) { return a; }

} // namespace internal

namespace monoid {
template <typename T>
using Plus = Monoid<T, internal::plus<T>, internal::zero<T>>;
template <typename T>
using Mult = Monoid<T, internal::mult<T>, internal::one<T>>;
template <typename T>
using Min = Monoid<T, internal::min<T>, internal::maximum<T>>;
template <typename T>
using Max = Monoid<T, internal::max<T>, internal::minimum<T>>;
template <typename T>
using Gcd = Monoid<T, internal::gcd<T>, internal::maximum<T>>;
template <typename T> using Lcm = Monoid<T, internal::lcm<T>, internal::one<T>>;
template <typename T>
using Xor = Monoid<T, internal::_xor<T>, internal::zero<T>>;
template <typename T>
using And = Monoid<T, internal::_and<T>, internal::all_bits_set<T>>;
template <typename T> using Or = Monoid<T, internal::_or<T>, internal::zero<T>>;

template <typename Matrix>
using MatrixPlus = Monoid<Matrix, internal::matrix_plus<Matrix>,
                          internal::empty_matrix<Matrix>>;
template <typename Matrix>
using MatrixMult = Monoid<Matrix, internal::matrix_mult<Matrix>,
                          internal::empty_matrix<Matrix>>;

} // namespace monoid

namespace group {
template <typename T>
using Plus =
    Group<T, internal::plus<T>, internal::plus_rev<T>, internal::zero<T>>;
template <typename T>
using Mult =
    Group<T, internal::mult<T>, internal::mult_rev<T>, internal::one<T>>;
template <typename T>
using Xor =
    Group<T, internal::_xor<T>, internal::id_f<T>, internal::zero<T>>;

template <typename Matrix>
using MatrixPlus =
    Group<Matrix, internal::matrix_plus<Matrix>,
          internal::matrix_plus_rev<Matrix>, internal::empty_matrix<Matrix>>;

} // namespace group

namespace monoid_action {
template <typename T>
using Chmin = MonoidAction<T, internal::min<T>, internal::maximum<T>, T, internal::min<T>>;
template <typename T>
using Chmax = MonoidAction<T, internal::max<T>, internal::minimum<T>, T, internal::max<T>>;
template <typename T>
using Mult = MonoidAction<T, internal::mult<T>, internal::one<T>, T, internal::mult<T>>;
template <typename T>
using Plus = MonoidAction<T, internal::plus<T>, internal::zero<T>, T, internal::plus<T>>;
template <typename T>
using Pow = MonoidAction<long long, internal::mult<long long>, internal::one<long long>, T, power<T>>;
template <typename Matrix>
using MatrixPult = MonoidAction<Matrix, internal::matrix_plus<Matrix>,
                          internal::empty_matrix<Matrix>, Matrix, internal::matrix_plus<Matrix>>;
template <typename Matrix>
using MatrixMult = MonoidAction<Matrix, internal::matrix_mult<Matrix>,
                          internal::empty_matrix<Matrix>, Matrix, internal::matrix_mult<Matrix>>;
};
