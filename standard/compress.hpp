#ifndef COMPRESS
#define COMPRESS
#include <algorithm>
#include <iterator>
#include <type_traits>

/**
 * @brief コンテナの要素を半開区間で指定し、座標圧縮する
 * @param __begin 座圧する左端のイテレータ
 * @param __end 右端のイテレータ
 * @attention 0 はじまりで圧縮する。
 */
template <typename InputIterator>
std::vector<int> compress(const InputIterator &__begin,
                          const InputIterator &__end) {
    std::vector<int> ret;
    ret.reserve(std::distance(__begin, __end));
    std::vector<typename std::iterator_traits<InputIterator>::value_type> w(
        __begin, __end);
    std::sort(w.begin(), w.end());
    w.erase(std::unique(w.begin(), w.end()), w.end());
    for (auto it = __begin; it != __end; it++)
        ret.push_back(std::lower_bound(w.begin(), w.end(), *it) - w.begin());
    return ret;
}

#endif
