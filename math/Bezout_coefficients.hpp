#pragma once
#include <cstdlib>
#include <utility>

namespace internal {
long long extgcd(long long a, long long b, long long &s, long long &t) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    } else {
        auto d = std::lldiv(a, b);
        long long tmp = extgcd(b, d.rem, t, s);
        t -= d.quot * s;
        return tmp;
    }
}
} // namespace internal

std::pair<long long, long long> Bezout_coefficients(long long a, long long b) {
    long long s, t;
    internal::extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);
    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};
}
