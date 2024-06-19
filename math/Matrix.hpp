#pragma once
#include <assert.h>

#include <iostream>
#include <utility>
#include <valarray>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

class InvalidOperationException : public std::exception {
  private:
    std::string message;

  public:
    InvalidOperationException() = default;
    InvalidOperationException(const std::string &msg) : message(msg) {}

    virtual const char *what() const noexcept override {
        return message.c_str();
    }

    virtual ~InvalidOperationException() noexcept {}
};

template <class T> class Matrix {
  private:
    using vArr = std::valarray<T>;
    i32 H, W;
    std::valarray<vArr> table;

    enum RowtransOpName { SCALE, SWAP, ADD };
    struct RowtransOp {
        i32 op, tar, res;
        T scl;
    };

  public:
    static Matrix nullMatrix() { return Matrix(0, 0); }
    bool isNull() { return *this == Matrix(0, 0); }
    static Matrix E(i32 N) {
        Matrix ret(N, N);
        for (i32 i = 0; i < N; i++)
            ret.table[i][i] = 1;
        return ret;
    }

    bool isZeroRow(i32 i) const {
        for (i32 j = 0; j < W; ++j) {
            if (table[i][j] != 0) {
                return false;
            }
        }
        return true;
    }

    Matrix() = default;
    Matrix(i32 _H, i32 _W, T val = 0)
        : H(_H), W(_W), table(vArr(val, _W), _H) {}
    Matrix(const std::vector<std::vector<T>> &vv)
        : H(vv.size()), W(vv[0].size()), table(vArr(W), H) {
        for (i32 i = 0; i < H; i++)
            for (i32 j = 0; j < W; j++)
                table[i][j] = vv[i][j];
    }
    Matrix(const std::valarray<vArr> &vv)
        : H(vv.size()), W(vv[0].size()), table(vv) {}

    /**
     * @brief 行列をリサイズする。
     * @param val 拡張部分の値
     */
    void resize(i32 _H, i32 _W, T val = 0) {
        H = _H, W = _W;
        table.resize(_H, vArr(val, _H));
    }
    i32 sizeH() const { return H; }
    i32 sizeW() const { return W; }
    void transpose() {
        Matrix ret(W, H);
        for (i32 i = 0; i < H; i++)
            for (i32 j = 0; j < W; j++)
                ret.table[j][i] = table[i][j];
        *this = ret;
    }

    vArr &operator[](i32 h) { return table[h]; }
    const vArr &operator[](i32 h) const { return table[h]; }

    /**
     * @brief 第 i 行, 第 j 行を入れ替える
     */
    void rowSwap(i32 i, i32 j) { table[i].swap(table[j]); }

    /**
     * @attention O(n^3)
     */
    std::vector<RowtransOp> sweepMethod() {
        std::vector<RowtransOp> hist;
        i32 h = 0, w = 0;
        while (h < H && w < W) {
            i32 piv = h;
            while (piv < H && table[piv][w] == 0) {
                ++piv;
            }
            if (piv < H) {
                if (h != piv) {
                    hist.emplace_back(RowtransOp{SWAP, h, piv, 0});
                    rowSwap(h, piv);
                }
                T inv = 1 / table[h][w];
                hist.emplace_back(RowtransOp{SCALE, -1, h, inv});
                table[h] *= inv;
                for (i32 i = 0; i < H; i++) {
                    if (i != h) {
                        hist.emplace_back(RowtransOp{ADD, h, i, -table[i][w]});
                        table[i] -= table[h] * table[i][w];
                    }
                }
                ++h;
            }
            ++w;
        }
        return hist;
    }

    i32 rank() const {
        Matrix U(*this);
        U.sweepMethod();
        i32 i = 0, j = 0;
        while (i < H) {
            while (j < W && U[i][j] != 1) {
                ++j;
            }
            if (j == W)
                break;
            ++i;
            ++j;
        }
        return i;
    }

    T det() const {
        if (H != W) {
            throw InvalidOperationException();
        }
        Matrix U(*this);
        T d = 1;
        auto hist = U.sweepMethod();
        if (U.table[H - 1][W - 1] == 0) {
            return 0;
        }
        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                d /= scl;
                break;
            case SWAP:
                d *= -1;
                break;
            }
        }
        return d;
    }

    Matrix inv() const {
        if (H != W) {
            throw InvalidOperationException();
        }
        Matrix INV(Matrix::E(H)), U(*this);
        auto hist = U.sweepMethod();
        if (U.table[H - 1][H - 1] == 0) {
            return nullMatrix();
        }

        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                INV.table[res] *= scl;
                break;
            case SWAP:
                std::swap(INV.table[tar], INV.table[res]);
                break;
            case ADD:
                INV.table[res] += INV.table[tar] * scl;
                break;
            }
        }

        return INV;
    }

    /**
     * 等式 Ax=eq を満たすxの解の一つを求める。
     * 存在しなければ空の配列を返す。
     */
    std::vector<T> solveLinearEquation(std::vector<T> eq) const {
        if (H != (i32)eq.size()) {
            throw InvalidOperationException();
        }

        Matrix U(*this);
        auto hist = U.sweepMethod();
        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                eq[res] *= scl;
                break;
            case SWAP:
                std::swap(eq[tar], eq[res]);
                break;
            case ADD:
                eq[res] += eq[tar] * scl;
                break;
            }
        }

        i32 rnk = 0, w = 0;
        std::vector<T> X(W, 0);
        while (rnk < H) {
            while (w < W && U[rnk][w] != 1) {
                ++w;
            }
            if (w == W)
                break;
            X[w] = eq[rnk];
            ++rnk;
            ++w;
        }

        for (i32 i = rnk; i < H; ++i) {
            if (eq[i] != 0) {
                return {};
            }
        }
        return X;
    }

    void print() const {
        for (i32 i = 0; i < H; i++) {
            for (i32 j = 0; j < W; j++) {
                std::cout << table[i][j] << (j == W - 1 ? "\n" : " ");
            }
        }
    }

    Matrix &operator+=(const Matrix &a) {
        if (H != a.H || W != a.W)
            [[unlikely]] { throw InvalidOperationException(); }
        this->table += a.table;
        return *this;
    }
    Matrix &operator-=(const Matrix &a) {
        if (H != a.H || W != a.W)
            [[unlikely]] { throw InvalidOperationException(); }
        this->table -= a.table;
        return *this;
    }
    Matrix &operator*=(const T &a) {
        this->table *= a;
        return *this;
    }
    Matrix &operator*=(const Matrix &a) {
        if (W != a.H)
            [[unlikely]] { throw InvalidOperationException(); }
        Matrix a_t(a), ret(H, a.W);
        a_t.transpose();
        for (i32 i = 0; i < H; i++) {
            for (i32 j = 0; j < a_t.H; j++) {
                ret.table[i][j] = (table[i] * a_t.table[j]).sum();
            }
        }
        return *this = ret;
    }
    Matrix &operator/=(const T &a) {
        this->table /= a;
        return *this;
    }

    Matrix operator+() const { return *this; }
    Matrix operator-() const { return Matrix(*this) *= -1; }
    Matrix operator+(const Matrix &a) const { return Matrix(*this) += a; }
    Matrix operator-(const Matrix &a) const { return Matrix(*this) -= a; }
    Matrix operator*(const T &a) { return Matrix(*this) *= a; }
    Matrix operator*(const Matrix &a) const { return Matrix(*this) *= a; }
    Matrix operator/(const T &a) const { return Matrix(*this) /= a; }

    Matrix power(i64 n) const {
        if (H != W)
            [[unlikely]] { throw InvalidOperationException(); }
        Matrix ret(E(H)), x(*this);
        while (n > 0) {
            if (n & 1)
                ret *= x;
            x *= x;
            n >>= 1;
        }
        return ret;
    }

    friend std::istream &operator>>(std::istream &is, Matrix &mt) {
        for (auto &arr : mt.table) {
            for (auto &x : arr) {
                is >> x;
            }
        }
        return is;
    }

    bool operator==(const Matrix &other) {
        if (H != other.H || W != other.W)
            return false;
        for (i32 h = 0; h < H; ++h) {
            for (i32 w = 0; w < W; ++w) {
                if (table[h][w] != other.table[h][w]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix &other) { return !operator==(other); }
};
} // namespace gandalfr
