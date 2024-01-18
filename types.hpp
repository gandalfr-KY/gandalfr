#include <cstdint>

#define ENSURE_ARITHMETIC_TYPE(A) static_assert(std::is_arithmetic<A>::value);

namespace gandalfr {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;

}
