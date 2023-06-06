#ifndef INVERSION
#define INVERSION
#include "compress.hpp"
#include "../data_structure/binary_indexed_tree.hpp"
#include <string>

template<class T>
long long inversion(typename std::vector<T>::const_iterator begin, typename std::vector<T>::const_iterator end){
    int N = std::distance(begin, end);
    if(!N) return 0;
    std::vector<T> vec(begin, end);  // vectorを作成
    std::vector<int> cmp = compress(vec, 0);
    binary_indexed_tree<long long> bit(*std::max_element(cmp.begin(), cmp.end()));
    long long ret = 0;
    for(int i = 0; i < N; i++){
        bit.add(cmp[i], 1);
        ret += i - bit.get(cmp[i]) + 1;
    }
    return ret;
}

#endif