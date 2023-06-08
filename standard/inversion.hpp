#ifndef INVERSION
#define INVERSION
#include <vector>
#include <type_traits>
#include "compress.hpp"
#include "../data_structure/binary_indexed_tree.hpp"

/**
 * @brief コンテナの要素を半開区間で指定し、転倒数を求める
 * @attention 区間長が 0 ならば 0
 */
template<typename InputIterator>
long long inversion(const InputIterator &__begin, const InputIterator &__end){
    int N = std::distance(__begin, __end);
    if(!N) return 0;
    std::vector<int> cmp = compress(__begin, __end);
    binary_indexed_tree<long long> bit(static_cast<int>(*std::max_element(cmp.begin(), cmp.end())) + 1);
    long long ret = (long long)N * (N + 1) / 2;
    for(auto &x : cmp){
        bit.add(x, 1);
        ret -= bit.get(x + 1);
    }
    return ret;
}

/**
 * @brief 要素の集合が等しいコンテナを半開区間で2つ指定するとき、一方をもう一方と同じように並べ替えるための swap のコスト
 * @attention 要素の集合が不一致ならば -1、区間長が 0 ならば 0
 */
template<typename InputIterator>
long long inversion(const InputIterator &__begin1, const InputIterator &__end1,
                    const InputIterator &__begin2, const InputIterator &__end2){
    int N = std::distance(__begin1, __end1);
    if(N != std::distance(__begin2, __end2)) return -1;
    if(N == 0) return 0;
    std::multiset<typename std::iterator_traits<InputIterator>::value_type>
        st1(__begin1, __end1), st2(__begin2, __end2);
    if(st1 != st2) return -1;

    std::vector<int> cmp1 = compress(__begin1, __end1), cmp2 = compress(__begin2, __end2);
    std::vector<std::vector<int>> ord(*std::max_element(cmp2.begin(), cmp2.end()) + 1);
    int i = 0;
    for(int x : cmp2) ord[x].push_back(i++);
    for(auto &v : ord) std::reverse(v.begin(), v.end());

    for(auto &x : cmp1){
        int tmp = ord[x].back();
        ord[x].pop_back();
        x = tmp;
    }
    return inversion(cmp1.begin(), cmp1.end());
}

#endif