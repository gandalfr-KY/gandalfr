#pragma once
#include <cmath>
#include <functional>
#include <map>

#include "../types.hpp"

namespace gandalfr {
/**
 * find the minimum of n s.t. b^n(x) = y
 * bは周期的で、周期は高々fでなければならない
 * g(x) := b^m(x)
 */
template <typename S> class Bsgs {
  private:
    std::function<S(S)> baby, giant;
    S x, y;
    i64 t, m;

  public:
    Bsgs(S X, S Y, i64 T) : x(X), y(Y), t(T), m(std::ceil(std::sqrt(T))) {}
    i64 getStepWidth() const { return m; }
    void setFunction(std::function<S(S)> b, std::function<S(S)> g) {
        baby = b;
        giant = g;
    }
    i64 findMinimum() const {
        if (x == y)
            return 0;
        i64 _x = x, _y = y;
        std::map<S, i64> babies;
        for (i64 i = 0; i < m; ++i) {
            babies[_y] = i;
            _y = baby(_y);
        }
        for (i64 i = 1; i <= (t + m - 1) / m; ++i) {
            _x = giant(_x);
            if (babies.contains(_x)) {
                return i * m - babies[_x];
            }
        }
        return -1;
    }
};
} // namespace gandalfr
