#ifndef WARSHALL_FLOYD
#define WARSHALL_FLOYD
#include "../math/matrix/matrix.hpp"

template<class T>
matrix<T> Warshall_Floyd(matrix<T> mt) {
    int N = mt.size_H();
    for(int k = 0; k < N; k++){ // 経由する頂点
        for(int i = 0; i < N; i++) { // 始点
            for(int j = 0; j < N; j++) { // 終点
                mt[i][j] = std::min(mt[i][j], mt[i][k] + mt[k][j]);
            }
        }
    }
    return mt;
}

#endif