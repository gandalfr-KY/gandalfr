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
    matrix<T> transpose() const {
        matrix<T> ret(W, H);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                ret[j][i] = table[i][j];
        return ret;
    }

    void row_swap(int i, int j) {
        assert(0 <= i && i < H);
        assert(0 <= j && j < H);
        table[i].swap(table[j]);
    }
    
    /**
     * @attention O(n^3)
     * @attention 整数型では正しく計算できない。double や fraction を使うこと。
     */
    operations_history sweep_method() {
        operations_history hist;
        T ret = 1;
        for (int h = 0, w = 0; h < H && w < W; w++) {
            for (int piv = h + 1; piv < H; piv++) {
                if (table[h][w] < table[piv][w]) {
                    hist.push_back({SWAP, h, piv, 0});
                    row_swap(h, piv);
                    
                }
            }
            if (table[h][w] == 0) {
                continue;
            }

            T inv = 1 / table[h][w];
            hist.push_back({SCALE, -1, w, inv});
            table[h] *= inv;
            for (int j = h + 1; j < H; j++) {
                hist.push_back({ADD, h, j, - table[j][w]});
                table[j] -= table[h] * table[j][w];
            }
            h++;
        }
        return hist;
    }

    int rank() {
        auto U(*this);
        U.sweep_method();
        int r = 0; // rank
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (U[i][j] != 0) {
                    r++;
                    break;
                }
            }
        }
        return r;
    }

    T determinant() const {
        assert(H == W);
        auto U(*this);
        T det = 1;
        auto hist = U.sweep_method();
        if (U[H-1][H-1] == 0) return 0;
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
        auto U(*this);
        auto hist = U.sweep_method();
        if (U[H-1][H-1] == 0) return {};

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
                x[j] -= U[j][i] * x[i];
            }
        }
        return x;
    }

    matrix<T> inverse() {
        assert(H == W);
        auto INV(matrix<T>::E(H));
        auto U(*this);
        auto hist = U.sweep_method();
        if (U[H-1][H-1] == 0) return matrix<T>(0, 0);

        for (auto &[op, tar, res, scl] : hist) {
            switch (op) {
            case SCALE:
                INV[res] *= scl;
                break;
            case SWAP:
                std::swap(INV[tar], INV[res]);
                break;
            case ADD:
                INV[res] += INV[tar] * scl;
                break;
            }
        }
        
        for (int i = H - 1; i >= 0; --i) {
            for (int j = 0; j < i; ++j) {
                INV[j] -= INV[i] * U[j][i];
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
        matrix<T> a_t(a.transpose()), ret(H, a.W);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < a.W; j++) {
                ret[i][j] = (this->table[i] * a_t.table[j]).sum();
            }
        }
        *this = std::move(ret);
        return *this;
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

    matrix<T> operator+() { return *this; }
    matrix<T> operator-() { return matrix<T>(*this) *= -1; }
    matrix<T> operator+(const matrix<T> &a) { return matrix<T>(*this) += a; }
    matrix<T> operator-(const matrix<T> &a) { return matrix<T>(*this) -= a; }
    template <typename S> matrix<T> operator*(const S &a) {
        return matrix<T>(*this) *= a;
    }
    matrix<T> operator/(const T &a) { return matrix<T>(*this) /= a; }
    matrix<T> operator^(long long n) { return matrix<T>(*this) ^= n; }
    std::valarray<T> &operator[](int h) { return table[h]; }
    friend std::istream &operator>>(std::istream &is, matrix<T> &mt) {
        for (auto &arr : mt.table)
            for (auto &x : arr)
                is >> x;
        return is;
    }

    /**
     * @brief サイズ n の単位行列。
     */
    static matrix<T> E(int N) {
        matrix<T> ret(N, N);
        for (int i = 0; i < N; i++)
            ret[i][i] = 1;
        return ret;
    }
};
