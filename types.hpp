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

constexpr i8 i8MAX = INT8_MAX;
constexpr i16 i16MAX = INT16_MAX;
constexpr i32 i32MAX = INT32_MAX;
constexpr i64 i64MAX = INT64_MAX;

constexpr i8 i8MIN = INT8_MIN;
constexpr i16 i16MIN = INT16_MIN;
constexpr i32 i32MIN = INT32_MIN;
constexpr i64 i64MIN = INT64_MIN;

constexpr u8 u8MAX = UINT8_MAX;
constexpr u16 u16MAX = UINT16_MAX;
constexpr u32 u32MAX = UINT32_MAX;
constexpr u64 u64MAX = UINT64_MAX;

constexpr i64 MOD998 = 998244353;
constexpr i64 MOD107 = 1000000007;

constexpr double PI = M_PI;
constexpr double eps = 1e-9;

const i32 INF = 1001001001;
const i64 INFLL = 1001001001001001001;
// j <= i < n で for
#define rep(i, j, n) for (i64 i = (i64)(j); i < (i64)(n); i++)
// j <= i < n で for (逆順)
#define revrep(i, j, n) for (i64 i = (i64)(n - 1); i >= (i64)(j); i--)
// T の空でない部分集合の列挙
#define subrep(S, T) for (i64 S = (i64)(T); S; S = (S - 1) & T)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define LF cout << endl
void Yes(bool ok) { std::cout << (ok ? "Yes" : "No") << std::endl; }

} // namespace gandalfr
