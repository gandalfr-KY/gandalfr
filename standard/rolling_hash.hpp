#ifndef ROLLING_HASH
#define ROLLING_HASH
#include <string>
#include <vector>
#include <random>

/**
 * @brief rolling_hashアルゴリズムで文字列を管理するクラス
 */
class rolling_hash{
private:
    unsigned long long _base;
    const unsigned long long _mod = (1LL<<61) - 1;
	std::vector<unsigned long long> hashes, bases;
    static inline const std::vector<unsigned long long> base_list{
        1809535154732661841LL,
        1884190988654199289LL,
        1743269039721525290LL,
        443670500607027996LL,
        1847920912542467715LL,
        854073078368186965LL,
        1223509603385983965LL,
        1417510665238831134LL,
        1078954822254450931LL,
        544731273123194097LL,
        628194563995444860LL,
        2068028567818163032LL,
        382415649034687899LL,
        1278119205153488676LL,
        1191116173253440671LL,
        1896252179888216214LL,
        1559071116560504239LL,
        924438638735228819LL,
        1857807495571573189LL,
        307827764609342932LL,
        152462581942784977LL
    };

public:
	rolling_hash(const std::string &s) : hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, base_list.size() - 1);
        _base = base_list[distr(gen)]; // generate numbers

		bases[0] = 1;
		for(int i = 0; i < (int)s.size(); i++){
			hashes[i + 1] = ((__uint128_t)hashes[i] * _base + s[i]) % _mod;
			bases[i + 1] = ((__uint128_t)bases[i] * _base) % _mod;
		}
	}

    /**
     * @brief 基数、mod を手動で設定するとき
     */
	rolling_hash(const std::string &s, unsigned long long b, unsigned long long m)
        : _base(b), _mod(m), hashes(s.size() + 1, 0), bases(s.size() + 1, 0) {
		bases[0] = 1;
		for(int i = 0; i < (int)s.size(); i++){
			hashes[i + 1] = ((__uint128_t)hashes[i] * _base + s[i]) % _mod;
			bases[i + 1] = ((__uint128_t)bases[i] * _base) % _mod;
		}
	}

	/**
     * @brief 半開区間を指定
     * @return string[l, r) のハッシュ値
     */
	unsigned long long get(int l, int r){
		return (hashes[r] + _mod - ((__uint128_t)hashes[l] * bases[r - l]) % _mod) % _mod;
	}

	/**
     * @brief 文字列を結合してハッシュ値を計算
     * @return get(_l, _r) == r_hash なる string[_l, _r) に対して、[_l, _r) + [l, r) のハッシュ値
     */
    unsigned long long concat(__uint128_t r_hash, int l, int r){
        return ((__uint128_t)r_hash * bases[r - l] + get(l, r)) % _mod;
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