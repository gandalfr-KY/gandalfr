#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

namespace internal {

template <class Derived, class T, i32 _dim> struct BaseArray {
    ENSURE_ARITHMETIC_TYPE(T)

    BaseArray() = default;
    BaseArray(std::initializer_list<T> init) {
        assert(init.size() <= _dim);
        std::copy(init.begin(), init.end(), v);
    }

    static constexpr i32 dim() { return _dim; }

    T v[_dim];

    std::vector<T> to_stdvec() { return {std::begin(v), std::end(v)}; }

    void load(const std::vector<T> &src) {
        std::copy(src.begin(), src.end(), v);
    }

    T &operator[](i32 index) { return v[index]; }
    const T &operator[](i32 index) const { return v[index]; }

    friend std::ostream &operator<<(std::ostream &os, const Derived &c) {
        for (i32 i = 0; i < _dim; ++i) {
            os << c.v[i] << (i < _dim - 1 ? " " : "");
        }
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Derived &c) {
        for (i32 i = 0; i < _dim; ++i) {
            is >> c.v[i];
        }
        return is;
    }
};
} // namespace internal

template <class T, i32 _dim>
struct GeoVector : public internal::BaseArray<GeoVector<T, _dim>, T, _dim> {
    using internal::BaseArray<GeoVector<T, _dim>, T, _dim>::BaseArray;

    double norm() const { return std::sqrt(normSq()); }

    T normSq() const {
        T sum = 0;
        for (i32 i = 0; i < _dim; ++i) {
            sum += this->v[i] * this->v[i];
        }
        return sum;
    }

    T dot(const GeoVector &other) const {
        T sum = T();
        for (i32 i = 0; i < _dim; ++i) {
            sum += this->v[i] * other.v[i];
        }
        return sum;
    }

    GeoVector operator+() const { return *this; }
    GeoVector operator-() const {
        GeoVector gv(*this);
        for (i32 i = 0; i < _dim; ++i)
            gv.v[i] *= -1;
        return gv;
    }
    GeoVector &operator+=(const GeoVector &other) {
        for (i32 i = 0; i < _dim; ++i) {
            this->v[i] += other.v[i];
        }
        return *this;
    }
    GeoVector &operator-=(const GeoVector &other) {
        for (i32 i = 0; i < _dim; ++i) {
            this->v[i] -= other.v[i];
        }
        return *this;
    }
    GeoVector &operator*=(const T scalar) {
        for (i32 i = 0; i < _dim; ++i) {
            this->v[i] *= scalar;
        }
        return *this;
    }
    GeoVector &operator/=(const T scalar) {
        for (i32 i = 0; i < _dim; ++i) {
            this->v[i] /= scalar;
        }
        return *this;
    }
    GeoVector operator+(const GeoVector &other) const {
        return static_cast<GeoVector>(*this) += other;
    }
    GeoVector operator-(const GeoVector &other) const {
        return static_cast<GeoVector>(*this) -= other;
    }
    GeoVector operator*(const T scalar) const {
        return static_cast<GeoVector>(*this) *= scalar;
    }
    GeoVector operator/(const T scalar) const {
        return static_cast<GeoVector>(*this) /= scalar;
    }

    bool operator==(const GeoVector &other) const {
        for (i32 i = 0; i < _dim; ++i)
            if (this->v[i] != other.v[i])
                return false;
        return true;
    }
    bool operator!=(const GeoVector &other) const { return !operator==(other); }
};

using Point2d = GeoVector<double, 2>;
using Point3d = GeoVector<double, 3>;

struct PointGrid : public internal::BaseArray<PointGrid, i64, 2> {
    using internal::BaseArray<PointGrid, i64, 2>::BaseArray;

    static inline i64 _H, _W;
    static void set_size(i64 H, i64 W) {
        _H = H;
        _W = W;
    }

    i64 &h() { return this->v[0]; }
    const i64 &h() const { return this->v[0]; }

    i64 &w() { return this->v[1]; }
    const i64 &w() const { return this->v[1]; }

    i64 toIdx() { return h() * _W + w(); }

    bool isValid() const {
        return (0 <= h() && h() < _H && 0 <= w() && w() < _W);
    }

    bool goUp() {
        PointGrid nxt = *this + PointGrid{-1, 0};
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goDown() {
        PointGrid nxt = *this + PointGrid{1, 0};
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goLeft() {
        PointGrid nxt = *this + PointGrid{-1, 0};
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goRight() {
        PointGrid nxt = *this + PointGrid{1, 0};
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }

    PointGrid operator+() const { return *this; }
    PointGrid operator-() const { return {-this->v[0], -this->v[1]}; }
    PointGrid &operator+=(const PointGrid &other) {
        this->v[0] += other.v[0];
        this->v[1] += other.v[1];
        return *this;
    }
    PointGrid &operator-=(const PointGrid &other) {
        this->v[0] -= other.v[0];
        this->v[1] -= other.v[1];
        return *this;
    }
    PointGrid &operator*=(const i64 scalar) {
        this->v[0] *= scalar;
        this->v[1] *= scalar;
        return *this;
    }
    PointGrid &operator/=(const i64 scalar) {
        this->v[0] /= scalar;
        this->v[1] /= scalar;
        return *this;
    }
    PointGrid operator+(const PointGrid &other) const {
        return static_cast<PointGrid>(*this) += other;
    }
    PointGrid operator-(const PointGrid &other) const {
        return static_cast<PointGrid>(*this) -= other;
    }
    PointGrid operator*(const i64 scalar) const {
        return static_cast<PointGrid>(*this) *= scalar;
    }
    PointGrid operator/(const i64 scalar) const {
        return static_cast<PointGrid>(*this) /= scalar;
    }

    bool operator==(const PointGrid &other) const {
        return (v[0] == other.v[0] && v[1] == other.v[1]);
    }
    bool operator!=(const PointGrid &other) const { return !operator==(other); }
};

PointGrid toPointGrid(i64 id) {
    auto [h, w] = std::lldiv(id, PointGrid::_W);
    return {h, w};
}

/*
 * | 8 4 5 |
 * | 3 0 1 |
 * | 7 2 6 |
 */
const std::vector<PointGrid> GAROUND = {{0, 0},  {0, 1},   {1, 0},
                                        {0, -1}, {-1, 0},  {-1, 1},
                                        {1, 1},  {-1, -1}, {1, -1}};
} // namespace gandalfr
