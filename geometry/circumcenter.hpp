#pragma once

#include "gandalfr/geometry/Vector.hpp"

namespace gandalfr {

inline Vector2d circumcenter(const Vector2d &a, const Vector2d &b,
                             const Vector2d &c) {
    double nrm_ac = c.normSq() - a.normSq();
    double nrm_ab = b.normSq() - a.normSq();
    Vector2d ret = {(a[1] - b[1]) * nrm_ac - (a[1] - c[1]) * nrm_ab,
                    (a[0] - c[0]) * nrm_ab - (a[0] - b[0]) * nrm_ac};
    double d = (a[0] - b[0]) * (a[1] - c[1]) - (a[0] - c[0]) * (a[1] - b[1]);
    if (std::abs(d) < eps) {
        return Vector2d::invalid();
    }
    return ret / (2 * d);
}

}; // namespace gandalfr
