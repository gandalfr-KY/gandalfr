#ifndef MATRIX
#define MATRIX
#include <omp.h>
#include <valarray>
#include <vector>
#include <iostream>
#include <assert.h>
#include "../../graph/graph.hpp"

template<class T>
class matrix{
  private:
    int H, W;
    std::valarray<std::valarray<T>> table;

  public:
    matrix(int _H, int _W, T val = 0) : H(_H), W(_W), table(std::valarray<T>(val, _W), _H) {}
    matrix(const std::vector<std::vector<T>> &vv) : H(vv.size()), W(vv[0].size()), table(std::valarray<T>(W), H) {
        for(int i=0; i<H; i++) for(int j=0; j<W; j++) table[i][j] = vv[i][j];
    }
    matrix(const std::valarray<std::valarray<T>> &vv) : H(vv.size()), W(vv[0].size()), table(vv) {}
    // グラフ=>隣接行列
    template<bool is_directed>
    matrix(const graph<T, is_directed> &G, T invalid)
         : H(G.num_nodes()), W(G.num_nodes()), table(std::valarray<T>(invalid, W), H){
        for(auto &e : G.edge_set()){
            table[e.from][e.to] = e.cost;
            if(!is_directed) table[e.to][e.from] = e.cost;
        }
    }

    int size_H() const { return H; }
    int size_W() const { return W; }

    matrix<T> transpose() const {
        matrix<T> ret(W, H);
        for(int i=0; i<H; i++) for(int j=0; j<W; j++) ret[j][i] = table[i][j];
        return ret;
    }

    const T determinant() const {
        assert(H == W);
        matrix<T> dfm(*this);
        T ret = 1;
        for(int i=0; i<H; i++){
            if(dfm[i][i] == 0){
                int piv;
                for(piv=i+1; piv<H; piv++) if(dfm[piv][i] != 0) break;
                if(piv == H) return 0;
                std::swap(dfm[i], dfm[piv]);
                ret *= -1;
            }            
            for(int j=i+1; j<H; j++) dfm[j] -= dfm[i] * (dfm[j][i] / dfm[i][i]) ;
            ret *= dfm[i][i];
        }
        return ret;
    }

    matrix<T> &operator=(const matrix<T> &a){
        table = a.table;
        return *this;
    }
    matrix<T> &operator+=(const matrix<T> &a){
        this->table += a.table;
        return *this;
    }
    matrix<T> &operator-=(const matrix<T> &a){
        this->table -= a.table;
        return *this;
    }
    matrix<T> &operator*=(const T &a){
        this->table *= a;
        return *this;
    }
    matrix<T> &operator*=(const matrix<T> &a){
        assert(this->W == a.H);
        matrix<T> a_t(a.transpose()), ret(this->H, a.W);
        for(int i=0; i<this->H; i++){
            for(int j=0; j<a.W; j++){
                ret[i][j] = (this->table[i] * a_t.table[j]).sum();
            }
        }
        std::swap(*this, ret);
        return *this;
    }
    matrix<T> &operator/=(const T &a){
        this->table /= a;
        return *this;
    }
    matrix<T> &operator%=(const T &a){
        for(int i=0; i<this->H; i++) this->table[i] %= a;
        return *this;
    }
    matrix<T> operator+(){ return *this; }
    matrix<T> operator-(){ return matrix<T>(*this) *= -1; }
    matrix<T> operator+(const matrix<T> &a){ return matrix<T>(*this) += a; }
    matrix<T> operator-(const matrix<T> &a){ return matrix<T>(*this) -= a; }
    template<typename S> matrix<T> operator*(const S &a){ return matrix<T>(*this) *= a; }
    matrix<T> operator/(const T &a){ return matrix<T>(*this) /= a; }
    matrix<T> operator%(const T &a){ return matrix<T>(*this) %= a; }

    std::valarray<T> &operator[](int h){ return table[h]; }

    friend std::istream &operator>>(std::istream &is, matrix<T> &mt){
        for(int i=0; i<mt.H; i++) is >> mt.table[i];
        return is;
    }

    void print() const {
        for(int i=0; i<H; i++){
            for(int j=0; j<W; j++){
                std::cout << table[i][j] << (j == W - 1 ? "" : " ");
            }
            std::cout << std::endl;
        }
    }

    static matrix<T> E(int N){
        matrix<T> ret(N, N);
        for(int i = 0; i < N; i++) ret[i][i] = 1;
        return ret;
    }
};

#endif