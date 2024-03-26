#pragma once

#include <cstdint>
#include <math.h>

namespace gandalfr {

using i8 = __int8_t;
using i16 = __int16_t;
using i32 = __int32_t;
using i64 = __int64_t;
using i128 = __int128_t;

using u8 = __uint8_t;
using u16 = __uint16_t;
using u32 = __uint32_t;
using u64 = __uint64_t;
using u128 = __uint128_t;

constexpr i8 IMAX8 = INT8_MAX;
constexpr i16 IMAX16 = INT16_MAX;
constexpr i32 IMAX32 = INT32_MAX;
constexpr i64 IMAX64 = INT64_MAX;

constexpr i8 IMIN8 = INT8_MIN;
constexpr i16 IMIN16 = INT16_MIN;
constexpr i32 IMIN32 = INT32_MIN;
constexpr i64 IMIN64 = INT64_MIN;

constexpr u8 UMAX8 = UINT8_MAX;
constexpr u16 UMAX16 = UINT16_MAX;
constexpr u32 UMAX32 = UINT32_MAX;
constexpr u64 UMAX64 = UINT64_MAX;

constexpr i64 MOD998 = 998244353;
constexpr i64 MOD107 = 1000000007;

constexpr double PI = M_PI;

const i32 INF = 1001001001;
const i64 INFLL = 1001001001001001001;
#define rep(i, j, n) for(i64 i = (i64)(j); i < (i64)(n); i++)
#define rrep(i, j, n) for(i64 i = (i64)(n-1); i >= (i64)(j); i--)
#define all(a) (a).begin(),(a).end()
#define LF cout << endl
template<typename T> void print_debug(T t) { std::cerr << t << std::endl; }
template<typename First, typename... Rest> void print_debug(First parm1, Rest... parm) {
    std::cerr << parm1 << ", ", print_debug(parm...);
}
#define debug(...) { \
    std::cerr << #__VA_ARGS__ << ": "; \
    print_debug(__VA_ARGS__); \
}
template<typename T> inline bool chmax(T &a, const T& b) { return a < b && (a = b, true); }
template<typename T> inline bool chmin(T &a, const T& b) { return a > b && (a = b, true); }
template<typename Key, typename Value> inline bool map_chmax(std::map<Key, Value>& mp, const Key& a, const Value& b) {
    auto it = mp.find(a);
    return it == mp.end() ? (mp[a] = b, true) : chmax(it->second, b);
}
template<typename Key, typename Value> inline bool map_chmin(std::map<Key, Value>& mp, const Key& a, const Value& b) {
    auto it = mp.find(a);
    return it == mp.end() ? (mp[a] = b, true) : chmin(it->second, b);
}
void Yes(bool ok){ std::cout << (ok ? "Yes" : "No") << std::endl; }

} // namespace gandalfr
