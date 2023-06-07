#ifndef INVERSION
#define INVERSION
#include <vector>
#include "compress.hpp"
#include "../data_structure/binary_indexed_tree.hpp"

/**
 * @brief コンテナの要素を半開区間で指定し、転倒数を求める
 * @param __begin 左端のイテレータ
 * @param __end 右端のイテレータ
 */
template<typename InputIterator>
long long inversion(const InputIterator &__begin, const InputIterator &__end){
    int N = std::distance(__begin, __end);
    if(!N) return 0;
    std::vector<typename std::iterator_traits<InputIterator>::value_type> cmp(__begin, __end);  // vectorを作成
    compress(cmp.begin(), cmp.end());
    binary_indexed_tree<long long> bit(static_cast<int>(*std::max_element(cmp.begin(), cmp.end())));
    long long ret = (long long)N * (N - 1) / 2;
    for(auto &x : cmp){
        bit.add(static_cast<int>(x), 1);
        ret -= bit.get(static_cast<int>(x));
    }
    return ret;
}

#endif