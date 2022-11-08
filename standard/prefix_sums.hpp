#ifndef PREFIX_SUMS
#define PREFIX_SUMS
#include <vector>

/* 長さ v.size() + 1 の累積和vectorを返す
 * Σv[l, r) = prf[r] - prf[l] が成立
 */
template<class T>
std::vector<T> prefix_sums(const std::vector<T> &v){
    std::vector<T> ret = {0};
    T acm = 0;
    for(T x : v){
        acm += x;
        ret.push_back(acm);
    }
    return ret;
}

#endif