#ifndef MATRIX
#define MATRIX
#include <omp.h>
#include <valarray>
#include <vector>
#include <iostream>
#include <assert.h>
#include "gandalfr/graph/graph.hpp"

template<class T>
class matrix{
  private:
    int H, W;
    std::valarray<std::valarray<T>> table;

    friend const matrix<T> operator+(const matrix<T> &a){
        return a;
    }

    friend const matrix<T> operator-(const matrix<T> &a){
        return matrix<T>(a * -1);
    }
    
    friend const matrix<T> operator+(const matrix<T> &a, const matrix<T> &b){
        assert(a.H == b.H && a.W == b.W);
        return matrix<T>(a.table + b.table);
    }
    
    friend const matrix<T> operator-(const matrix<T> &a, const matrix<T> &b){
        assert(a.H == b.H && a.W == b.W);
        return matrix<T>(a.table - b.table);
    }
  
    friend const matrix<T> operator*(const matrix<T> &a, const T &b){
        return matrix<T>(a.table * b);
    }

    friend const matrix<T> operator*(const matrix<T> &a, const matrix<T> &b){
        assert(a.W == b.H);
        matrix<T> _b(b.transpose()), ret(a.H, b.W);
#pragma omp parallel for collapse(2)
        for(int i=0; i<a.H; i++){
            for(int j=0; j<b.W; j++){
                ret[i][j] = (a.table[i] * _b.table[j]).sum();
            }
        }
        return ret;
    }

    friend matrix<T> operator/(const matrix<T> &a, const T &b){
        return matrix<T>(a.table / b);
    }
    
    friend matrix<T> operator%(const matrix<T> &a, const T &b){
        matrix<T> ret(a);
        for(int i = 0; i < a.H; i++) for(int j = 0; j < a.W; j++)
            ret[i][j] %= b;
        return ret;
    }

  public:
    matrix(int _H, int _W, T val = 0) : H(_H), W(_W), table(std::valarray<T>(val, _W), _H) {}
    matrix(const std::vector<std::vector<T>> &vv) : H(vv.size()), W(vv[0].size()), table(std::valarray<T>(W), H) {
        for(int i=0; i<H; i++) for(int j=0; j<W; j++) table[i][j] = vv[i][j];
    }
    matrix(const std::valarray<std::valarray<T>> &vv) : H(vv.size()), W(vv[0].size()), table(vv) {}
    matrix(const matrix<T> &mt) : H(mt.H), W(mt.W), table(mt.table) {}
    // グラフ=>隣接行列
    template<bool is_directed>
    matrix(const internal::_base_graph<T, is_directed> &G, T invalid)
         : H(G.nodes()), W(G.nodes()), table(std::valarray<T>(invalid, W), H){
        for(const internal::_base_edge<T> &e : G.edge_set()){
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

    const matrix<T> &operator=(const matrix<T> &a){ table = a.table; return *this; }
    void operator+=(const matrix<T> &a){ *this = operator+(*this, a); }
    void operator-=(const matrix<T> &a){ *this = operator-(*this, a); }
    void operator*=(const T &a){ *this = operator*(*this, a); }
    void operator*=(const matrix<T> &a){ *this = operator*(*this, a); }
    void operator/=(const T &a){ *this = operator/(*this, a); }
    void operator%=(const T &a){ *this = operator%(*this, a); }

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
    
};


#endif