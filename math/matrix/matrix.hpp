#ifndef MATRIX
#define MATRIX
#include <valarray>
#include <vector>
#include <iostream>
#include <assert.h>

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
        for(int i=0; i<a.H; i++){
            for(int j=0; j<b.W; j++){
                ret[i][j] = (a.table[i] * _b.table[j]).sum();
            }
        }
        return ret;
    }

    friend matrix<T> operator/(const matrix<T> &a, const T &b){
        matrix<T> ret(a);
        for(int i=0; i<ret.size_H(); i++) ret.table[i] /= b;
        return ret;
    }
    
    friend matrix<T> operator%(const matrix<T> &a, const T &b){
        matrix<T> ret(a);
        for(int i=0; i<ret.size_H(); i++) ret.table[i] %= b;
        return ret;
    }

  public:
    matrix(int _H, int _W, T val = 0) : H(_H), W(_W), table(std::valarray<T>(val, _W), _H) {}
    matrix(const std::vector<std::vector<T>> &vv) : H(vv.size()), W(vv[0].size()) {
        for(int i=0; i<H; i++) for(int j=0; j<W; j++) table[i][j] = vv[i][j];
    }
    matrix(const std::valarray<std::valarray<T>> &vv) : H(vv.size()), W(vv[0].size()), table(vv) {}
    matrix(const matrix<T> &mt) : H(mt.H), W(mt.W), table(mt.table) {}

    int size_H() const { return H; }
    int size_W() const { return W; }

    matrix<T> transpose() const{
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
            for(int j=i+1; j<H; j++) dfm[j] -= dfm[i] / dfm[i][i] * dfm[j][i];
            ret *= dfm[i][i];
        }
        return ret;
    }

    const matrix<T> &operator=(const matrix<T> &a){ table = a.table; return table; }
    void operator+=(const matrix<T> &a){ *this = operator+(*this, a); }
    void operator-=(const matrix<T> &a){ *this = operator-(*this, a); }
    template<class U>
    void operator*=(const U &a){ *this = operator*(*this, a); }
    void operator/=(const T &a){ *this = operator/(*this, a); }
    void operator%=(const T &a){ *this = operator%(*this, a); }

    std::valarray<T> &operator[](int h){ return table[h]; }

    friend std::istream &operator>>(std::istream &is, matrix<T> &mt){
        for(int i=0; i<mt.size_H(); i++) is >> mt.table[i];
        return is;
    }

    void print(){
        for(int i=0; i<H; i++){
            for(int j=0; j<W; j++){
                std::cout << table[i][j] << (j == W - 1 ? "" : " ");
            }
            std::cout << std::endl;
        }
    }
    
};


#endif