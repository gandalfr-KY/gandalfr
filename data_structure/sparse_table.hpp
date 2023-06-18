#pragma once
#include <functional>
#include <vector>

/**
 * @brief 結合則・冪等性を満たす演算の更新無し区間クエリ処理
 */
template <class T> class sparse_table {
  private:
    const std::function<T(T, T)> op;
    std::vector<std::vector<T>> table;
    std::vector<short> log_table; // log_table[n] := 2^k < n である最大の k

  public:
    sparse_table(const std::function<T(T, T)> &f) : op(f) {}

    // 要素の配列 vec で初期化
    void init(const std::vector<T> &vec) {
        table = {vec};
        log_table.clear();

        for (int i = 0; (1 << i) < table[i].size(); i++) {
            table.push_back({});
            for (int j = 0; j + (1 << i) < table[i].size(); j++) {
                table[i + 1].push_back(op(table[i][j], table[i][j + (1 << i)]));
            }
        }

        log_table.resize(vec.size() + 1, 0);
        for (int i = 2; i <= vec.size(); i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }
    }

    /**
     * @brief [l, r) の演算結果を得る
     * @attention l >= r のとき未定義
     */
    T get(int l, int r) {
        int k = log_table[r - l];
        return op(table[k][l], table[k][r - (1 << k)]);
    }
};

template <typename T> struct RmQ_sparse_table : public sparse_table<T> {
    RmQ_sparse_table()
        : RmQ_sparse_table<T>::sparse_table(
              [](T a, T b) { return (a < b ? a : b); }) {}
};

template <typename T> struct RMQ_sparse_table : public sparse_table<T> {
    RMQ_sparse_table()
        : RMQ_sparse_table<T>::sparse_table(
              [](T a, T b) { return (a > b ? a : b); }) {}
};
