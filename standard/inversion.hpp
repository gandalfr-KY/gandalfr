#ifndef INVERSION
#define INVERSION
#include "gandalfr/standard/compress.hpp"
#include "gandalfr/data_structure/binary_indexed_tree.hpp"
#include <string>

/* 転倒数 
 */
template<class T>
long long inversion(std::vector<T> vec){
    int N = vec.size();
    if(!N) return 0;
    std::vector<int> cmp = compress(vec, 1);
    binary_indexed_tree<long long> bit(*std::max_element(cmp.begin(), cmp.end()));
    long long ret = 0;
    for(int i=1; i<=N; i++){
        bit.add(cmp[i-1], 1);
        ret += i - bit.sum(cmp[i-1]);
    }
    return ret;
}


#endif