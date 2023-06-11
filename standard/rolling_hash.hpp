#ifndef ROLLING_HASH
#define ROLLING_HASH
#include <string>
#include <vector>

/**
 * @brief rolling_hashアルゴリズムで文字列を管理するクラス
 */
class rolling_hash{
private:
    const __uint128_t _base = 10007, _mod = ((__uint128_t)1<<61) - 1;
	std::vector<__uint128_t> hashes, bases; 

public:
	rolling_hash(const std::string &s) : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {
		bases[0] = 1;
		for(int i = 0; i < (int)s.size(); i++){
			hashes[i + 1] = (hashes[i] * _base + s[i]) % _mod;
			bases[i + 1] = (bases[i] * _base) % _mod;
		}
	}

	/**
     * @brief 半開区間を指定
     * @return string[l, r) のハッシュ値
     */
	__uint128_t get(int l, int r){
		return (hashes[r] + _mod - (hashes[l] * bases[r - l]) % _mod) % _mod;
	}

	/**
     * @brief 文字列を結合してハッシュ値を計算
     * @return get(_l, _r) == r_hash なる string[_l, _r) に対して、[_l, _r) + [l, r) のハッシュ値
     */
    __uint128_t concat(__uint128_t r_hash, int l, int r){
        return (r_hash * bases[r - l] + get(l, r)) % _mod;
	}

    /**
     * @return string[l1, r1), string[l2, r2) の最長共通接頭辞の長さ
     */
    int longest_common_prefix(int l1, int r1, int l2, int r2){
        int ok = 0, ng = std::min(r1 - l1, r2 - l2) + 1;
        while(std::abs(ok - ng) > 1){
            int mid = (ok + ng) / 2;
            if(get(l1, l1 + mid) == get(l2, l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

#endif