#ifndef INVERSION
#define INVERSION
#include <set>
#include <type_traits>
#include <vector>

#include "../data_structure/binary_indexed_tree.hpp"
#include "compress.hpp"

/**
 * @brief コンテナの要素を半開区間で指定し、転倒数を求める
 * @attention 区間長が 0 ならば 0
 */
template <typename InputIterator>
long long inversion(const InputIterator &__begin, const InputIterator &__end) {
    int N = std::distance(__begin, __end);
    if (!N)
        return 0;
    std::vector<int> cmp = compress(__begin, __end);
    binary_indexed_tree<long long> bit(
        *std::max_element(cmp.begin(), cmp.end()) + 1);
    long long ret = (long long)N * (N + 1) / 2;
    for (auto &x : cmp) {
        bit.add(x, 1);
        ret -= bit.get(x + 1);
    }
    return ret;
}

/**
 * @brief
 * 要素の集合が等しい半開区間を2つ指定。一方をもう一方と同じように並べ替えるための
 * swap のコスト
 * @attention 要素の集合が不一致ならば -1、区間長が 0 ならば 0
 * @see <a
 * href="https://atcoder.jp/contests/arc120/submissions/42083168">verify</a>
 */
template <typename InputIterator>
long long inversion(const InputIterator &__begin1, const InputIterator &__end1,
                    const InputIterator &__begin2,
                    const InputIterator &__end2) {
    int N = std::distance(__begin1, __end1);
    if (N != std::distance(__begin2, __end2))
        return -1;
    if (N == 0)
        return 0;
    std::multiset<typename std::iterator_traits<InputIterator>::value_type> st1(
        __begin1, __end1),
        st2(__begin2, __end2);
    if (st1 != st2)
        return -1;

    std::vector<int> cmp1 = compress(__begin1, __end1),
                     cmp2 = compress(__begin2, __end2);
    std::vector<std::vector<int>> ord(
        *std::max_element(cmp2.begin(), cmp2.end()) + 1);
    for (int i = 0; i < N; i++)
        ord[cmp2[i]].push_back(i);
    for (int i = N - 1; i >= 0; i--) {
        int tmp = ord[cmp1[i]].back();
        ord[cmp1[i]].pop_back();
        cmp1[i] = tmp;
    }
    return inversion(cmp1.begin(), cmp1.end());
}

#endif
