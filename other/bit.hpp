#pragma once

#include "../types.hpp"

namespace gandalfr {

inline bool getBit(u64 b, u32 p) { return (b >> p) & 1; }

// 先頭から p 番目のビットに値 f をセット
inline void setBit(u32 &b, u32 p, bool f) {
    if (f) {
        b |= 1UL << p;
    } else {
        b &= ~(1UL << p);
    }
}

// 先頭から p 番目のビットに値 f をセット
inline void setBit(u64 &b, u32 p, bool f) {
    if (f) {
        b |= 1ULL << p;
    } else {
        b &= ~(1ULL << p);
    }
}

// 先頭から p 番目のビットが 1
inline u64 singleBit(i32 p) { return 1ULL << p; }

// 先頭 p ビットが 1
inline u64 leadingBit(u32 p) { return singleBit(p) - 1; }

} // namespace gandalfr
