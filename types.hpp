#include <cstdint>

#define ENSURE_ARITHMETIC_TYPE(A) static_assert(std::is_arithmetic<A>::value);

namespace gandalfr {

using f8 = int_fast8_t;
using f16 = int_fast16_t;
using f32 = int_fast32_t;
using f64 = int_fast64_t;

}
