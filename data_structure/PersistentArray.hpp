#pragma once
#include <assert.h>
#include <iostream>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

template <typename T>
struct PersistentArray {
    struct Node {
        T _value;
        i32 _left = 0, _right = 0;
        Node() = default;
        Node(T value, i32 left, i32 right) : _value(value), _left(left), _right(right) {}
    };
    
    std::vector<Node> _data;
    std::vector<i32> _roots;

    PersistentArray() = default;
    PersistentArray(const std::vector<T>& A) {
        i32 N = A.size();
        _data.emplace_back(T(), 0, 0);
        _roots.push_back(1);
        i32 cur = 1;
        i32 loop_range = 1;
        while (cur <= N) {
            for (cur = loop_range; cur < std::min<i32>(loop_range << 1, N + 1); ++cur) {
                i32 l = cur << 1, r = (cur << 1) + 1;
                if (l > N) l = 0;
                if (r > N) r = 0;
                T v = cur <= N ? A[cur - 1] : T();
                _data.emplace_back(v, l, r);
            }
            loop_range <<= 1;
        }
        _roots.push_back(_data.size()); // 番兵
    }
    PersistentArray(i32 N) : PersistentArray(std::vector<T>(N)) {}
    PersistentArray(const PersistentArray &other) = default;
    PersistentArray(PersistentArray &&other) = default;
    PersistentArray &operator=(const PersistentArray &other) = default;
    PersistentArray &operator=(PersistentArray &&other) = default;

    i32 version() const {
        if (_roots.empty()) return 0;
        return (i32)_roots.size() - 1;
    }
    i32 size() const {
        if (_roots.empty()) return 0;
        return _roots[1] - 1;
    }

    void update(i32 t, i32 id, T value) {
        assert(0 <= t && t <= version());
        assert(0 <= id && id < size());
        ++id; // 0-index -> 1-index
        i32 hist_idx = _roots[t];
        i32 w = (i32)std::bit_width<u32>(id) - 2;
        while (w >= 0) {
            i32 v = _data[hist_idx]._value;
            i32 l, r;
            if (id & (1 << w)) {
                l = _data[hist_idx]._left;
                r = _data.size() + 1;
                hist_idx = _data[hist_idx]._right;
            } else {
                l = _data.size() + 1;
                r = _data[hist_idx]._right;
                hist_idx = _data[hist_idx]._left;
            }
            _data.emplace_back(v, l, r);
            --w;
        }
        _data.emplace_back(value, _data[hist_idx]._left, _data[hist_idx]._right);
        _roots.push_back(_data.size()); // 番兵
    }

    void update_batch(i32 t, std::vector<i32> ids, std::vector<T> values) {
        if (ids.empty()) {
            i32 idx = _roots[t];
            _data.emplace_back(_data[idx]);
            _roots.push_back(_data.size()); // 番兵
            return;
        }
        std::vector<i32> ord(ids.size());
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](i32 i, i32 j) { return ids[i] < ids[j]; });
        for (i32 i : ord) {
            i32 id = ids[i] + 1; // 0-index -> 1-index
            if (!(0 <= id-1 && id-1 < size())) {
                std::cerr << "id = " << id-1 << ", size = " << size() << std::endl;
            }
            assert(0 <= id-1 && id-1 < size());
            T value = values[i];
            i32 hist_idx = _roots[t];
            i32 cur_idx = _roots.back();
            i32 w = (i32)std::bit_width<u32>(id) - 2;
            while (cur_idx < (i32)_data.size()) {
                if (id & (1 << w)) {
                    if (_data[cur_idx]._right < _roots.back()) { // 次が過去のデータなら
                        _data[cur_idx]._right = _data.size();
                    }
                    cur_idx = _data[cur_idx]._right;
                    hist_idx = _data[hist_idx]._right;
                } else {
                    if (_data[cur_idx]._left < _roots.back()) {
                        _data[cur_idx]._left = _data.size();
                    }
                    cur_idx = _data[cur_idx]._left;
                    hist_idx = _data[hist_idx]._left;
                }
                --w;
            }
            while (w >= 0) {
                i32 v = _data[hist_idx]._value;
                i32 l, r;
                if (id & (1 << w)) {
                    l = _data[hist_idx]._left;
                    r = _data.size() + 1;
                    hist_idx = _data[hist_idx]._right;
                } else {
                    l = _data.size() + 1;
                    r = _data[hist_idx]._right;
                    hist_idx = _data[hist_idx]._left;
                }
                _data.emplace_back(v, l, r);
                --w;
            }
            _data.emplace_back(value, _data[hist_idx]._left, _data[hist_idx]._right);
        }
        _roots.push_back(_data.size()); // 番兵
    }

    T get(i32 t, i32 id) const {
        assert(0 <= t && t < version());
        assert(0 <= id && id < size());
        ++id; // 0-index -> 1-index
        i32 cur_idx = _roots[t];
        i32 w = (i32)std::bit_width<u32>(id) - 2;
        while (w >= 0) {
            if (id & (1 << w)) {
                cur_idx = _data[cur_idx]._right;
            } else {
                cur_idx = _data[cur_idx]._left;
            }
            --w;
        }
        return _data[cur_idx]._value;
    }

    void print() const {
        i32 N = size();
        for (i32 t = 0; t < version(); ++t) {
            for (i32 i = 0; i < N; ++i) {
                std::cout << get(t, i) << " ";
            }
            std::cout << std::endl;
        }
    }
};

} // namespace gandalfr
