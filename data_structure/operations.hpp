#pragma once
#include <limits>
#include <algorithm>

#include "../math/matrix.hpp"

/**
 * @brief モノイド
 * @tparam T(*op)(T, T) 結合律を満たす T について閉じた二項演算
 * @tparam Id 二項演算の単位元
 */
template <typename T, T(*Op)(T, T), T (*Id)()>
struct Monoid {
    static T op(T a, T b) {
        return Op(a, b);
    }
    static constexpr T id() {
        return Id();
    }
};

/**
 * @brief 群
 * @tparam T(*Rev)(T) 逆元を求める単項演算（例: 加法なら、-1 をかける操作）
 */
template <typename T, T(*Op)(T, T), T(*Rev)(T), T (*Id)()>
struct Group : public Monoid<T, Op, Id> {
    static T rev(T a) {
        return Rev(a);
    }
};

namespace internal{
template <typename T> constexpr T zero() {
    return 0;
}
template <typename T> constexpr T one() {
    return 1;
}
template <typename T> constexpr T maximum() {
    return std::numeric_limits<T>::max();
}
template <typename T> constexpr T minimum() {
    return std::numeric_limits<T>::lowest();
}
template <typename T> constexpr T all_bits_set() {
    return ~T(0);
}
template <typename T> constexpr T empty_matrix() {
    return T::E(0);
}

template <typename T> T plus(T a, T b) {
    return a + b;
}
template <typename T> T plus_rev(T a) {
    return -a;
}

template <typename T> T matrix_plus(T a, T b) {
    if (a == internal::empty_matrix<T>()) return b;
    if (b == internal::empty_matrix<T>()) return a;
    return a + b;
}
template <typename T> T matrix_plus_rev(T a) {
    return -a;
}

template <typename T> T mult(T a, T b) {
    return a * b;
}
template <typename T> T mult_rev(T a) {
    return internal::one<T>() / a;
}

template <typename T> T matrix_mult(T a, T b) {
    if (a == internal::empty_matrix<T>()) return b;
    if (b == internal::empty_matrix<T>()) return a;
    return a * b;
}

template <typename T> T min(T a, T b) {
    return std::min(a, b);
}

template <typename T> T max(T a, T b) {
    return std::max(a, b);
}

template <typename T> T gcd(T a, T b) {
    if (a == internal::maximum<T>()) return b; 
    if (b == internal::maximum<T>()) return a; 
    return std::gcd(a, b);
}

template <typename T> T lcm(T a, T b) {
    return std::lcm(a, b);
}

template <typename T> T _xor(T a, T b) {
    return a ^ b;
}
template <typename T> T _xor_rev(T a) {
    return a;
}

template <typename T> T _and(T a, T b) {
    return a & b;
}

template <typename T> T _or(T a, T b) {
    return a | b;
}

}

namespace monoid {
template <typename T> using Plus = Monoid<T, internal::plus<T>, internal::zero<T>>;
template <typename T> using Mult = Monoid<T, internal::mult<T>, internal::one<T>>;
template <typename T> using Min = Monoid<T, internal::min<T>, internal::maximum<T>>;
template <typename T> using Max = Monoid<T, internal::max<T>, internal::minimum<T>>;
template <typename T> using Gcd = Monoid<T, internal::gcd<T>, internal::maximum<T>>;
template <typename T> using Lcm = Monoid<T, internal::lcm<T>, internal::one<T>>;
template <typename T> using Xor = Monoid<T, internal::_xor<T>, internal::zero<T>>;
template <typename T> using And = Monoid<T, internal::_and<T>, internal::all_bits_set<T>>;
template <typename T> using Or = Monoid<T, internal::_or<T>, internal::zero<T>>;

template <typename Matrix> using MatrixPlus = Monoid<Matrix, internal::matrix_plus<Matrix>, internal::empty_matrix<Matrix>>;
template <typename Matrix> using MatrixMult = Monoid<Matrix, internal::matrix_mult<Matrix>, internal::empty_matrix<Matrix>>;

}

namespace group {
template <typename T> using Plus = Group<T, internal::plus<T>, internal::plus_rev<T>, internal::zero<T>>;
template <typename T> using Mult = Group<T, internal::mult<T>, internal::mult_rev<T>, internal::one<T>>;
template <typename T> using Xor = Group<T, internal::_xor<T>, internal::_xor_rev<T>, internal::zero<T>>;

template <typename Matrix> using MatrixPlus = Group<Matrix, internal::matrix_plus<Matrix>, internal::matrix_plus_rev<Matrix>, internal::empty_matrix<Matrix>>;

}
