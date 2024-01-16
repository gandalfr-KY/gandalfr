#pragma once

#include "vector_nd.hpp"

namespace gandalfr {

struct gpoint : public vector_nd<f64, 2> {
    static inline f64 _H, _W;
    static void set_size(f64 H, f64 W) {
        _H = H;
        _W = W;
    }

    gpoint() = default;
    gpoint(f64 _h, f64 _w) {
        h() = _h;
        w() = _w;
    }
    gpoint(const vector_nd<f64, 2>& other) {
        h() = other.v[0];
        w() = other.v[1];
    }

    f64& h() {
        return v[0];
    }
    const f64& h() const {
        return v[0];
    }

    f64& w() {
        return v[1];
    }
    const f64& w() const {
        return v[1];
    }

    f64 to_idx() {
        return h() * _W + w();
    }

    bool is_valid() const {
        return (0 <= h() && h() < _H && 0 <= w() && w() < _W);
    }
};

gpoint to_gpoint(f64 id) {
    auto [h, w] = std::ldiv(id, gpoint::_W);
    return gpoint(h, w);
}

/*
* | 8 4 5 |
* | 3 0 1 |
* | 7 2 6 |
*/
const std::vector<gpoint> GAROUND = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0},
                                    {-1, 1}, {1, 1}, {-1, -1}, {1, -1}};
}
