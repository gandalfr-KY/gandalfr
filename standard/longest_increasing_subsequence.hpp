#ifndef LONGEST_INCREASINNG_SUBSEQUENCE
#define LONGEST_INCREASINNG_SUBSEQUENCE
#include <vector>
#include <set>
#include <algorithm>

/* 最長部分増加列の長さを返す
 * strict == true ? 狭義増加 : 広義増加
 */
template<class T>
int longest_increasing_subsequence(const std::vector<T> &v, bool strict = false){
    std::vector<T> dp;
    auto it = dp.begin();
    for(const T &x : v){    
        if(strict) it = std::lower_bound(dp.begin(), dp.end(), x);
        else it = std::upper_bound(dp.begin(), dp.end(), x);
        if(it != dp.end()) *it = x;
        else dp.push_back(x);
    }
    return dp.size();
}

#endif