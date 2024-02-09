#pragma once

#include <cstdint>
#include <math.h>

namespace gandalfr {

using i8 = signed char;
using i16 = signed short int;
using i32 = signed int;
using i64 = signed long long int;
using i128 = __int128_t;

using u8 = unsigned char;
using u16 = unsigned short int;
using u32 = unsigned int;
using u64 = unsigned long long int;
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

} // namespace gandalfr
