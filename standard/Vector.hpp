#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

#include "gandalfr/types.hpp"

namespace gandalfr {

template <class T, i32 dim> struct Vector {
    Vector() = default;
    Vector(std::initializer_list<T> init) {
        assert(init.size() <= dim);
        std::copy(init.begin(), init.end(), v);
    }

    std::vector<T> toStdvec() { return {std::begin(v), std::end(v)}; }

    void load(const std::vector<T> &src) {
        std::copy(src.begin(), src.end(), v);
    }

    double norm() const { return std::sqrt(normSq()); }

    T normSq() const {
        T sum = 0;
        for (i32 i = 0; i < dim; ++i) {
            sum += this->v[i] * this->v[i];
        }
        return sum;
    }

    // 内積
    T dot(const Vector &other) const {
        T sum = T();
        for (i32 i = 0; i < dim; ++i) {
            sum += this->v[i] * other.v[i];
        }
        return sum;
    }

    Vector operator+() const { return *this; }
    Vector operator-() const {
        Vector gv(*this);
        for (i32 i = 0; i < dim; ++i)
            gv.v[i] *= -1;
        return gv;
    }
    Vector &operator+=(const Vector &other) {
        for (i32 i = 0; i < dim; ++i) {
            this->v[i] += other.v[i];
        }
        return *this;
    }
    Vector &operator-=(const Vector &other) {
        for (i32 i = 0; i < dim; ++i) {
            this->v[i] -= other.v[i];
        }
        return *this;
    }
    Vector &operator*=(const T scalar) {
        for (i32 i = 0; i < dim; ++i) {
            this->v[i] *= scalar;
        }
        return *this;
    }
    Vector &operator/=(const T scalar) {
        for (i32 i = 0; i < dim; ++i) {
            this->v[i] /= scalar;
        }
        return *this;
    }
    Vector operator+(const Vector &other) const {
        return static_cast<Vector>(*this) += other;
    }
    Vector operator-(const Vector &other) const {
        return static_cast<Vector>(*this) -= other;
    }
    Vector operator*(const T scalar) const {
        return static_cast<Vector>(*this) *= scalar;
    }
    Vector operator/(const T scalar) const {
        return static_cast<Vector>(*this) /= scalar;
    }

    bool operator==(const Vector &other) const {
        for (i32 i = 0; i < dim; ++i)
            if (this->v[i] != other.v[i])
                return false;
        return true;
    }
    bool operator!=(const Vector &other) const { return !operator==(other); }

    T &operator[](i32 index) { return v[index]; }
    const T &operator[](i32 index) const { return v[index]; }

    friend std::ostream &operator<<(std::ostream &os, const Vector &a) {
        for (i32 i = 0; i < dim; ++i) {
            os << a.v[i] << (i < dim - 1 ? " " : "");
        }
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Vector &a) {
        for (i32 i = 0; i < dim; ++i) {
            is >> a.v[i];
        }
        return is;
    }

  private:
    T v[dim];
};

using Vector2d = Vector<double, 2>;
using Vector3d = Vector<double, 3>;

} // namespace gandalfr
