#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <iterator>

#include "../types.hpp"

namespace gandalfr {

template <class T, f32 _dim> struct vector_nd {
    ENSURE_ARITHMETIC_TYPE(T)

    static constexpr f32 dim() {
        return _dim;
    }

    T v[_dim];

    double norm() const {
        return std::sqrt(norm_sq());
    }

    T norm_sq() const {
        T sum = 0;
        for (f32 i = 0; i < _dim; ++i) {
            sum += v[i] * v[i];
        }
        return sum;
    }

    T dot(const vector_nd &other) const {
        T sum = T();
        for (f32 i = 0; i < _dim; ++i) {
            sum += v[i] * other.v[i];
        }
        return sum;
    }

    std::vector<T> to_stdvec() {
        return {std::begin(v), std::end(v)};
    }

    void load(const std::vector<T>& src) {
        std::copy(src.begin(), src.end(), v);
    }

    vector_nd operator+() const {
        return *this;
    }
    vector_nd operator-() const {
        vector_nd v(*this);
        for (f32 i = 0; i < _dim; ++i) v[i] *= -1;
        return v;
    }
    vector_nd &operator+=(const vector_nd &other) {
        for (f32 i = 0; i < _dim; ++i) {
            v[i] += other.v[i];
        }
        return *this;
    }
    vector_nd &operator-=(const vector_nd &other) {
        for (f32 i = 0; i < _dim; ++i) {
            v[i] -= other.v[i];
        }
        return *this;
    }
    vector_nd &operator*=(const T scalar) {
        for (f32 i = 0; i < _dim; ++i) {
            v[i] *= scalar;
        }
        return *this;
    }
    vector_nd &operator/=(const T scalar) {
        for (f32 i = 0; i < _dim; ++i) {
            v[i] /= scalar;
        }
        return *this;
    }
    vector_nd operator+(const vector_nd &other) const {
        return static_cast<vector_nd>(*this) += other;
    }
    vector_nd operator-(const vector_nd &other) const {
        return static_cast<vector_nd>(*this) -= other;
    }
    vector_nd operator*(const T scalar) const {
        return static_cast<vector_nd>(*this) *= scalar;
    }
    vector_nd operator/(const T scalar) const {
        return static_cast<vector_nd>(*this) /= scalar;
    }

    bool operator==(const vector_nd &other) const {
        for (f32 i = 0; i < _dim; ++i) {
            if (v[i] != other.v[i])
                return false;
        }
        return true;
    }
    bool operator!=(const vector_nd &other) const {
        return std::rel_ops::operator!=(*this, other);
    }

    T& operator[](f32 index) {
        return v[index];
    }
    const T& operator[](f32 index) const {
        return v[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const vector_nd &c) {
        for (f32 i = 0; i < _dim; ++i) {
            os << c.v[i] << (i < _dim - 1 ? " " : "");
        }
        return os;
    }
    friend std::istream &operator>>(std::istream &is, vector_nd &c) {
        for (f32 i = 0; i < _dim; ++i) {
            is >> c.v[i];
        }
        return is;
    }

};

using point2d = vector_nd<double, 2>;
using point3d = vector_nd<double, 3>;

}
