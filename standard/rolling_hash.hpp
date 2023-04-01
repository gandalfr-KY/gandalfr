#include <string>
#include <vector>

// verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7318906#1

class rolling_hash{
  private:
    const int len;
	const __uint128_t _base = 10007, _mod = ((__uint128_t)1<<61) - 1;
	std::vector<__uint128_t> hashes, bases; 

  public:
	rolling_hash(const std::string &s) : len(s.size()), hashes(len + 1, 0), bases(len + 1, 0)  {
		bases[0] = 1;
		for(int i = 0; i < len; i++){
			hashes[i + 1] = (hashes[i] * _base + s[i]) % _mod;
			bases[i + 1] = (bases[i] * _base) % _mod;
		}
	}

	/* s[l, r) のハッシュ値を計算
     * O(1)
     */
	__uint128_t get(int l, int r){
		return (hashes[r] + _mod - (hashes[l] * bases[r-l]) % _mod) % _mod;
	}

    /* s[l1, r1), s[l2, r2) の最長共通接頭辞
     * O(logN)
     */
    int longest_common_prefix(int l1, int r1, int l2, int r2){
        // [ok, ng)
        int ok = 0, ng = std::min(r1 - l1, r2 - l2) + 1;
        while(abs(ok - ng) > 1){
            int mid = (ok + ng) / 2;
            if(get(l1, l1 + mid) == get(l2, l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }

};