#ifndef DIVIDE_INTEGER
#define DIVIDE_INTEGER
#include <vector>
#include <assert.h>

namespace internal{
    void _divide_integer(std::vector<int> &lst, std::vector<std::vector<int>> &ans, int sum, int size){
        if(size == 0) return;
        if(size == 1){
            lst.push_back(sum);
            ans.push_back(lst);
            lst.pop_back();
            return;
        }
        for(int i = 0; i <= sum; i++){
            lst.push_back(i);
            _divide_integer(lst, ans, sum - i, size - 1);
            lst.pop_back();
        }
    }
}

// 総和が sum になるような長さ size の lower_limit 以上の整数のリストを全探索する
std::vector<std::vector<int>> divide_integer(int sum, int size, int lower_limit = 0){
    assert(lower_limit >= 0);
    std::vector<int> tmp;
    std::vector<std::vector<int>> ret;
    internal::_divide_integer(tmp, ret, sum - lower_limit * size, size);
    for(auto &v : ret) for(auto &x : v) x += lower_limit;
    return ret;
}

#endif