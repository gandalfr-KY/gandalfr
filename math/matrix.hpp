#pragma once
#include <assert.h>

#include <iostream>
#include <utility>
#include <valarray>
#include <vector>

template <class T> class matrix {
  private:
    int H, W;
    std::valarray<std::valarray<T>> table;

    enum rowtrans_operation_name { SCALE, SWAP, ADD };
    struct rowtrans_operation {
        int op, tar, res;
        T scl;
    };
    using operations_history = std::vector<rowtrans_operation>;

  public:
    matrix() = default;
    matrix(int _H, int _W, T val = 0)
        : H(_H), W(_W), table(std::valarray<T>(val, _W), _H) {}
    matrix(const std::vector<std::vector<T>> &vv)
        : H(vv.size()), W(vv[0].size()), table(std::valarray<T>(W), H) {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                table[i][j] = vv[i][j];
    }
    matrix(const std::valarray<std::valarray<T>> &vv)
        : H(vv.size()), W(vv[0].size()), table(vv) {}

    /**
     * @brief 行列をリサイズする。
     * @param val 拡張部分の値
     */
    void resize(int _H, int _W, T val = 0) {
        H = _H, W = _W;
        table.resize(_H, std::valarray<T>(val, _H));
    }
    int size_H() const { return H; }
    int size_W() const { return W; }
    void transpose() {
        matrix<T> ret(W, H);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                ret.table[j][i] = table[i][j];
        *this = ret;
    }

    /**
     * @brief 第 i 行に対して行単位で代入を行う
     * @example A.row_assign(3, {1,2,3});
     */
    void row_assign(int i, const std::valarray<T> &row) {
        assert(0 <= i && i < H);
        assert(W == (int)row.size());
        table[i] = row;
    }

    /**
     * @brief 第 i 行, 第 j 行を入れ替える
     */
    void row_swap(int i, int j) {
        assert(0 <= i && i < H);
        assert(0 <= j && j < H);
        table[i].swap(table[j]);
    }

    /**
     * @attention O(n^3)
     * @attention 整数型では正しく計算できない。double や fraction を使うこと。
     * @attention 枢軸選びをしていないので double では誤差が出るかも。
     */
    operations_history sweep_method() {
        operations_history hist;
        T ret = 1;
        for (int h = 0, w = 0; h < H && w < W; w++) {
            if (table[h][w] == 0) {
                for (int piv = h + 1; piv < H; piv++) {
                    if (table[piv][w] != 0) {
                        hist.push_back({SWAP, h, piv, 0});
                        row_swap(h, piv);
                        break;
                    }
                }
                if (table[h][w] == 0) {
                    continue;
                }
            }
            T inv = 1 / table[h][w];
            hist.push_back({SCALE, -1, w, inv});
            table[h] *= inv;
            for (int j = h + 1; j < H; j++) {
                hist.push_back({ADD, h, j, -table[j][w]});
                table[j] -= table[h] * table[j][w];
            }
            h++;
        }
        return hist;
    }

    int rank() const {
        auto U(*this);
        U.sweep_method();
        int r = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = i; j < W; ++j) {
                if (U.table[i][j] != 0) {
                    r++;
                    break;
                }
            }
        }
        return r;
    }

    T determinant() const {
        assert(H == W);
        matrix<T> U(*this);
        T det = 1;
        auto hist = U.sweep_method();
        if (U.table[H - 1][H - 1] == 0)
            return 0;
        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                det /= scl;
                break;
            case SWAP:
                det *= -1;
                break;
            }
        }
        return det;
    }

    std::vector<T> solve_system_of_equations(const std::vector<T> &y) {
        assert(H == W);
        std::vector<T> x(y);
        matrix<T> U(*this);
        auto hist = U.sweep_method();
        if (U.table[H - 1][H - 1] == 0)
            return {};

        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                x[res] *= scl;
                break;
            case SWAP:
                std::swap(x[tar], x[res]);
                break;
            case ADD:
                x[res] += x[tar] * scl;
                break;
            }
        }

        for (int i = H - 1; i >= 0; --i) {
            for (int j = 0; j < i; ++j) {
                x[j] -= U.table[j][i] * x[i];
            }
        }
        return x;
    }

    matrix<T> inverse() const {
        assert(H == W);
        matrix<T> INV(matrix<T>::E(H)), U(*this);
        auto hist = U.sweep_method();
        if (U.table[H - 1][H - 1] == 0)
            return matrix<T>(0, 0);

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

        for (int i = H - 1; i >= 0; --i) {
            for (int j = 0; j < i; ++j) {
                INV.table[j] -= INV.table[i] * U.table[j][i];
            }
        }
        return INV;
    }

    void print() const {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                std::cout << table[i][j] << (j == W - 1 ? "" : " ");
            }
            std::cout << std::endl;
        }
    }

    matrix<T> &operator+=(const matrix<T> &a) {
        this->table += a.table;
        return *this;
    }
    matrix<T> &operator-=(const matrix<T> &a) {
        this->table -= a.table;
        return *this;
    }
    matrix<T> &operator*=(const T &a) {
        this->table *= a;
        return *this;
    }
    matrix<T> &operator*=(const matrix<T> &a) {
        assert(W == a.H);
        matrix<T> a_t(a), ret(H, a.W);
        a_t.transpose();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < a_t.H; j++) {
                ret.table[i][j] = (table[i] * a_t.table[j]).sum();
            }
        }
        return *this = ret;
    }
    matrix<T> &operator/=(const T &a) {
        this->table /= a;
        return *this;
    }
    /**
     * @brief 行列の冪乗。
     * @param n 指数
     * @attention n が 0 なら単位行列。
     * @attention 演算子の優先度に注意。
     */
    matrix<T> operator^=(long long n) {
        assert(H == W);
        if (n == 0)
            return *this = E(H);
        n--;
        matrix<T> x(*this);
        while (n) {
            if (n & 1)
                *this *= x;
            x *= x;
            n >>= 1;
        }
        return *this;
    }

    matrix<T> operator+() const { return *this; }
    matrix<T> operator-() const { return matrix<T>(*this) *= -1; }
    matrix<T> operator+(const matrix<T> &a) const {
        return matrix<T>(*this) += a;
    }
    matrix<T> operator-(const matrix<T> &a) const {
        return matrix<T>(*this) -= a;
    }
    matrix<T> operator*(const T &a) { return matrix<T>(*this) *= a; }
    matrix<T> operator*(const matrix<T> &a) const {
        return matrix<T>(*this) *= a;
    }
    matrix<T> operator/(const T &a) const { return matrix<T>(*this) /= a; }
    matrix<T> operator^(long long n) const { return matrix<T>(*this) ^= n; }
    friend std::istream &operator>>(std::istream &is, matrix<T> &mt) {
        for (auto &arr : mt.table)
            for (auto &x : arr)
                is >> x;
        return is;
    }
    const T &operator()(int h, int w) const {
        assert(0 <= h && h < H && 0 <= w && w <= W);
        return table[h][w];
    }
    T &operator()(int h, int w) {
        assert(0 <= h && h < H && 0 <= w && w <= W);
        return table[h][w];
    }

    template <typename S> bool operator==(const matrix<S> &other) {
        if (size_H() != other.size_H() || size_W() != other.size_W())
            return false;
        for (int h = 0; h < H; ++h) {
            for (int w = 0; w < W; ++w) {
                if (table[h][w] != other.table[h][w])
                    return false;
            }
        }
        return true;
    }
    template <typename S> bool operator!=(const matrix<S> &other) {
        return !operator==(other);
    }

    /**
     * @brief サイズ n の単位行列。
     */
    static matrix<T> E(int N) {
        matrix<T> ret(N, N);
        for (int i = 0; i < N; i++)
            ret.table[i][i] = 1;
        return ret;
    }
};
