#pragma once

#include "gandalfr/types.hpp"

namespace gandalfr {

bool getBit(u32 b, u32 p) { return (b >> p) & 1; }

bool getBit64(u64 b, u32 p) { return (b >> p) & 1; }

bool setOne(u32 &b, u32 p) {
    bool ret = (getBit(b, p) == 0);
    b |= (1 << p);
    return ret;
}

bool setOne64(u64 &b, u32 p) {
    bool ret = (getBit64(b, p) == 0);
    b |= (1 << p);
    return ret;
}

bool setZero(u32 &b, u32 p) {
    bool ret = (getBit(b, p) == 1);
    b &= ~(1 << p);
    return ret;
}

bool setZero64(u64 &b, u32 p) {
    bool ret = (getBit64(b, p) == 1);
    b &= ~(1 << p);
    return ret;
}

// 先頭 p ビットが 1
u32 allOne(u32 p) { return (1U << p) - 1; }

// 先頭 p ビットが 1
u64 allOne64(u32 p) { return (1ULL << p) - 1; }

u32 popCount(u32 b) { return __builtin_popcount(b); }

u32 popCount64(u64 b) { return __builtin_popcountll(b); }

// 先頭から p 番目のビットが 1
u32 singleBit(i32 p) { return 1U << p; }

// 先頭から p 番目のビットが 1
u64 singleBit64(i32 p) { return 1ULL << p; }

} // namespace gandalfr
