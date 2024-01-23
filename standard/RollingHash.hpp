#pragma once
#include <random>
#include <string>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

/**
 * @brief rolling_hashアルゴリズムで文字列を管理するクラス。
 * @attention 複数のインスタンスを生成しても、基数は共有される。
 */
template <u64 b = 1809535154732661841LL> class RollingHash {
  private:
    static constexpr u64 m = (1LL << 61) - 1;
    std::vector<unsigned long long> hashes, bases;

  public:
    RollingHash(const std::string &s)
        : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {
        bases[0] = 1;
        for (int i = 0; i < (int)s.size(); i++) {
            bases[i + 1] = ((u128)bases[i] * b) % m;
            hashes[i + 1] = ((u128)bases[i] * s[i] + hashes[i]) % m;
        }
        std::cout << std::endl;
        for (auto bs : bases) {
            std::cout << bs << " ";
        }
        std::cout << std::endl;
        for (auto hs : hashes) {
            std::cout << hs << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief 半開区間を指定
     * @return string[l, r) のハッシュ値
     */
    unsigned long long get(int l, int r) { return (hashes[r] - hashes[l]); }

    /**
     * @brief r_hash == get(_l, _r) なるハッシュ値を、string([_l, _r) + [l, r))
     * のハッシュ値に更新。
     */
    void concat(unsigned long long &r_hash, int l, int r) {
        r_hash = ((u128)r_hash * bases[r - l] + get(l, r)) % m;
    }

    /**
     * @return string[l1, r1), string[l2, r2) の最長共通接頭辞の長さ
     */
    int longest_common_prefix(int l1, int r1, int l2, int r2) {
        int ok = 0, ng = std::min(r1 - l1, r2 - l2) + 1;
        while (std::abs(ok - ng) > 1) {
            int mid = (ok + ng) / 2;
            if (get(l1, l1 + mid) == get(l2, l2 + mid))
                ok = mid;
            else
                ng = mid;
        }
        return ok;
    }
};
} // namespace gandalfr
