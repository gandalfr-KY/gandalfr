#pragma once
#include "enumeration_utility.hpp"
#include "prime_number_utility.hpp"

/**
 * @brief オイラーのトーシェント関数
 */
long long totient(long long n) {
    auto facs = prime_number_utility::factorize(n);
    long long ret = 1;
    for (auto &p : facs)
        ret *= power(p.first, p.second - 1) * (p.first - 1);
    return ret;
}
