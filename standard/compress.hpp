#ifndef COMPRESS
#define COMPRESS
#include <vector>
#include <algorithm>

template<class T>
std::vector<int> compress(std::vector<T> &v, int a = 0){
    int N = v.size();
    std::vector<T> w = v;
    std::vector<int> ret(N);
    std::sort(w.begin(), w.end());
    w.erase(std::unique(w.begin(), w.end()), w.end());
    for(int i=0; i<N; i++) ret[i] = std::lower_bound(w.begin(), w.end(), v[i]) - w.begin() + a;
    return ret;
}

#endif