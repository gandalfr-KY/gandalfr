#include <iostream>
#include <vector>

template <class T, int dim> struct vector_nd {
    T v[dim];

    vector_nd() = default;

    double norm() const {
        double sum = 0.0;
        for (int i = 0; i < dim; ++i) {
            double value = static_cast<double>(v[i]);
            sum += value * value;
        }
        return std::sqrt(sum);
    }

    T norm2() const {
        T sum = 0;
        for (int i = 0; i < dim; ++i) {
            sum += v[i] * v[i];
        }
        return sum;
    }

    vector_nd &operator+=(const vector_nd &other) {
        for (int i = 0; i < dim; ++i) {
            v[i] += other.v[i];
        }
        return *this;
    }
    vector_nd &operator-=(const vector_nd &other) {
        for (int i = 0; i < dim; ++i) {
            v[i] -= other.v[i];
        }
        return *this;
    }
    vector_nd &operator*=(const T scalar) {
        for (int i = 0; i < dim; ++i) {
            v[i] *= scalar;
        }
        return *this;
    }
    vector_nd &operator/=(const T scalar) {
        for (int i = 0; i < dim; ++i) {
            v[i] /= scalar;
        }
        return *this;
    }
    vector_nd operator+(const vector_nd &other) const {
        return (vector_nd) * this += other;
    }
    vector_nd operator-(const vector_nd &other) const {
        return (vector_nd) * this -= other;
    }
    vector_nd operator*(const T scalar) const {
        return (vector_nd) * this *= scalar;
    }
    vector_nd operator/(const T scalar) const {
        return (vector_nd) * this /= scalar;
    }

    T dot(const vector_nd &other) const {
        T sum = T();
        for (int i = 0; i < dim; ++i) {
            sum += v[i] * other.v[i];
        }
        return sum;
    }

    bool operator==(const vector_nd &other) const {
        for (int i = 0; i < dim; ++i) {
            if (v[i] != other.v[i])
                return false;
        }
        return true;
    }
    bool operator!=(const vector_nd &other) const {
        return std::rel_ops::operator!=(*this, other);
    }

    friend std::ostream &operator<<(std::ostream &os, const vector_nd &c) {
        for (int i = 0; i < dim; ++i) {
            os << c.v[i] << (i < dim - 1 ? " " : "");
        }
        return os;
    }
    friend std::istream &operator>>(std::istream &is, vector_nd &c) {
        for (int i = 0; i < dim; ++i) {
            is >> c.v[i];
        }
        return is;
    }
};

template <class T> using v2d = vector_nd<T, 2>;
template <class T> using v3d = vector_nd<T, 3>;
