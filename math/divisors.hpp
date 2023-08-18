#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief 約数昇順列挙
 * @attention O(√N)
 */
std::vector<long long> divisors(long long N) {
    std::vector<long long> ret;
    for (long long i = 1; i * i <= N; i++) {
        if (N % i == 0) {
            ret.push_back(i);
            if (N / i != i)
                ret.push_back(N / i);
        }
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}
