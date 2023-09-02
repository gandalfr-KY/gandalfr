#pragma once
#include <algorithm>
#include <set>
#include <type_traits>
#include <vector>

/**
 * @brief コンテナの要素を半開区間で指定し、最長部分増加列のの長さを求める
 * @attention 区間長が 0 ならば 0
 * @tparam strict true ? 狭義増加 : 広義増加
 */
template <typename InputIterator, bool strict = false>
int longest_increasing_subsequence(const InputIterator &__begin,
                                   const InputIterator &__end) {
    std::vector<typename std::iterator_traits<InputIterator>::value_type> dp;
    auto dp_it = dp.begin();
    for (auto arg_it = __begin; arg_it != __end; ++arg_it) {
        if constexpr (strict)
            dp_it = std::lower_bound(dp.begin(), dp.end(), *arg_it);
        else
            dp_it = std::upper_bound(dp.begin(), dp.end(), *arg_it);
        if (dp_it != dp.end())
            *dp_it = *arg_it;
        else
            dp.push_back(*arg_it);
    }
    return dp.size();
}
