#pragma once

#include <cstdint>
#include <math.h>

#define ENSURE_ARITHMETIC_TYPE(A) static_assert(std::is_arithmetic<A>::value);

namespace gandalfr {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
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
