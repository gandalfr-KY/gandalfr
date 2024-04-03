#pragma once
#include <functional>
#include <vector>

#include "gandalfr/types.hpp"

namespace gandalfr {

/**
 * @brief 結合則・冪等性を満たす演算の更新無し区間クエリ処理
 */
template <class S, S (*op)(S, S), S (*e)()> class SparseTable {
  private:
    std::vector<std::vector<S>> table;
    std::vector<i32> log_table; // log_table[n] := 2^k < n である最大の k

  public:
    SparseTable() = default;
    SparseTable(const std::vector<S> &vec) { init(vec); }

    // 要素の配列 vec で初期化
    void init(const std::vector<S> &vec) {
        table = {vec};
        for (u32 i = 0; (1UL << i) < table[i].size(); i++) {
            table.push_back({});
            for (u32 j = 0; j + (1 << i) < table[i].size(); j++) {
                table[i + 1].push_back(op(table[i][j], table[i][j + (1 << i)]));
            }
        }
        log_table.assign(vec.size() + 1, 0);
        for (i32 i = 2; i <= (i32)vec.size(); i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }
    }

    S get(i32 l, i32 r) {
        if (l == r)
            return e();
        i32 k = log_table[r - l];
        return op(table[k][l], table[k][r - (1 << k)]);
    }
};
} // namespace gandalfr
