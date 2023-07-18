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
    /**
     * @attention O(n^3)
     * @attention 整数型では正しく計算できない。double や fraction を使うこと。
     */
    const T determinant() const {
        assert(H == W);
        matrix<T> dfm(*this);
        T ret = 1;
        for (int i = 0; i < H; i++) {
            if (dfm[i][i] == 0) {
                int piv;
                for (piv = i + 1; piv < H; piv++)
                    if (dfm[piv][i] != 0)
                        break;
                if (piv == H)
                    return 0;
                dfm[i].swap(dfm[piv]);
                ret *= -1;
            }
            for (int j = i + 1; j < H; j++)
                dfm[j] -= dfm[i] * (dfm[j][i] / dfm[i][i]);
            ret *= dfm[i][i];
        }
        return ret;
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
