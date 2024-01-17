#pragma once
#include <algorithm>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

template <typename T>
std::vector<f32> compress(const std::vector<T> &vec) {
    std::vector<f32> ret(vec.size());
    std::vector<T> w(vec);
    std::sort(w.begin(), w.end());
    w.erase(std::unique(w.begin(), w.end()), w.end());
    for (size_t i = 0; i < vec.size(); ++i) {
        ret[i] = (std::lower_bound(w.begin(), w.end(), static_cast<f32>(vec[i])) - w.begin());
    }
    return ret;
}
}
