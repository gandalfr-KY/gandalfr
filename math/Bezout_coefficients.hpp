#pragma once
#include <tuple>
#include <utility>

namespace internal {

long long extgcd(long long a, long long b, long long &x, long long &y) {
    x = 1, y = 0;
    long long nx = 0, ny = 1;
    while (b) {
        long long q = a / b;
        std::tie(a, b) = std::make_pair(b, a % b);
        std::tie(x, nx) = std::make_pair(nx, x - nx * q);
        std::tie(y, ny) = std::make_pair(ny, y - ny * q);
    }
    return a;
}
} // namespace internal

std::pair<long long, long long> Bezout_coefficients(long long a, long long b) {
    long long s, t;
    internal::extgcd((a >= 0 ? a : -a), (b >= 0 ? b : -b), s, t);
    return {(a >= 0 ? s : -s), (b >= 0 ? t : -t)};
}
