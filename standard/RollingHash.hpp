#pragma once
#include <random>
#include <string>
#include <vector>

#include "../math/utility.hpp"
#include "../types.hpp"

namespace gandalfr {

namespace impl {

// r := p の原始根
// return r^k s.t. r^k > MAX_ELM and gcd(p - 1, k) = 1
// https://trap.jp/post/1036/
template <i32 p, i32 MAX_ELM> constexpr i32 determinBase() {
    constexpr i32 r = atcoder::internal::primitive_root<p>;
    i64 b = r;
    for (i32 k = 1;
         b <= MAX_ELM || atcoder::internal::inv_gcd(p - 1, k).first != 1;
         k += 2) {
        b = b * r % p;
        b = b * r % p;
    }
    return b;
}

} // namespace impl

struct RHCode {
    static constexpr i32 P1 = 998244353;
    static constexpr i32 P2 = 1000000007;
    static constexpr i32 P3 = 1000000009;
    static constexpr i32 B1 = impl::determinBase<P1, UMAX8>();
    static constexpr i32 B2 = impl::determinBase<P2, UMAX8>();
    static constexpr i32 B3 = impl::determinBase<P3, UMAX8>();

    i32 sz = 0;
    Mint<P1> code1{0};
    Mint<P2> code2{0};
    Mint<P3> code3{0};

    RHCode() = default;
    RHCode(const RHCode &other) = default;
    RHCode(const std::string &str) : sz(str.size()) {
        for (i32 i = 0; i < sz; ++i) {
            code1 += powMod<P1, B1>(sz - i - 1) * str[i];
            code2 += powMod<P2, B2>(sz - i - 1) * str[i];
            code3 += powMod<P3, B3>(sz - i - 1) * str[i];
        }
    }
    RHCode(i8 c) : sz(1), code1(c), code2(c), code3(c) {}

    RHCode &operator+=(const RHCode &other) {
        code1 = code1 * powMod<P1, B1>(other.sz) + other.code1;
        code2 = code2 * powMod<P2, B2>(other.sz) + other.code2;
        code3 = code3 * powMod<P3, B3>(other.sz) + other.code3;
        sz += other.sz;
        return *this;
    }
    RHCode operator+(const RHCode &other) const {
        return static_cast<RHCode>(*this) += other;
    }
    bool operator==(const RHCode &other) const {
        return sz == other.sz && code1 == other.code1 && code2 == other.code2 &&
               code3 == other.code3;
    }
    bool operator!=(const RHCode &other) const { return !operator==(other); }
};

class RollingHash {
  public:
    std::vector<RHCode> hs;

  public:
    RollingHash() = default;
    RollingHash(const std::string &s) : hs(s.size() + 1) {
        for (u32 i = 0; i < s.size(); i++) {
            hs[i + 1] = hs[i] + RHCode(s[i]);
        }
    }

    i32 size() const { return hs.back().sz; }

    RollingHash &operator+=(const RollingHash &other) {
        RHCode bc = hs.back();
        hs.reserve(size() + other.size());
        for (i32 i = 1; i <= other.size(); ++i) {
            hs.push_back(bc + other.hs[i]);
        }
        return *this;
    }

    RollingHash operator+(const RollingHash &other) const {
        return static_cast<RollingHash>(*this) += other;
    }

    // [l, r)
    RHCode getCode(i32 l, i32 r) const {
        RHCode ret;
        ret.code1 =
            hs[r].code1 - hs[l].code1 * powMod<RHCode::P1, RHCode::B1>(r - l);
        ret.code2 =
            hs[r].code2 - hs[l].code2 * powMod<RHCode::P2, RHCode::B2>(r - l);
        ret.code3 =
            hs[r].code3 - hs[l].code3 * powMod<RHCode::P3, RHCode::B3>(r - l);
        ret.sz = r - l;
        return ret;
    }
};
} // namespace gandalfr
