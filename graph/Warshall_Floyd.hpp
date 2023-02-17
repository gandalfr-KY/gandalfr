#ifndef WARSHALL_FLOYD
#define WARSHALL_FLOYD
#include "gandalfr/graph/graph.hpp"
#include "gandalfr/math/matrix/matrix.hpp"

template<class T>
matrix<T> warshall_floyd(const matrix<T> &mt, T invalid = -1) {
    int n = mt.size_H();
    matrix<T> ret(mt);
    for(int k = 0; k < n; k++){ // 経由する頂点
        for(int i = 0; i < n; i++) { // 始点
            if(ret[i][k] == invalid) continue;
            for(int j = 0; j < n; j++) { // 終点
                if(ret[k][j] == invalid) continue;
                if(ret[i][j] == invalid) ret[i][j] = ret[i][k] + ret[k][j];
                else ret[i][j] = std::min(ret[i][j], ret[i][k] + ret[k][j]);
            }
        }
    }
    return ret;
}

#endif