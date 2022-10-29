#ifndef FACTORS_TO_DIVISORS
#define FACTORS_TO_DIVISORS
#include <vector>
#include <algorithm>
#include <utility>

// 素因数分解 => 約数列挙
void _dfs_for_facs_to_divs(const std::vector<std::pair<long long, int>> &facs, std::vector<long long> &ret, int cu, long long val=1){
    if(cu == facs.size()){
        ret.push_back(val);
        return;
    }
    long long mag = 1;
    for(int i=0; i<=facs[cu].second; i++){
        _dfs_for_facs_to_divs(facs, ret, cu+1, val*mag);
        mag *= facs[cu].first;
    }
}

// factors_to_divisors({}) => return 1
std::vector<long long> factors_to_divisors(const std::vector<std::pair<long long, int>> &facs){
    std::vector<long long> ret;
    _dfs_for_facs_to_divs(facs, ret, 0);
    std::sort(ret.begin(), ret.end());
    return ret;
}

#endif