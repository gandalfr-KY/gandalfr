---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"standard/grid.hpp\"\n#include <iostream>\n#include <vector>\n\
    \nstruct grid {\n    long long h, w;\n\n    bool is_valid(int H, int W) const\
    \ {\n        return (0 <= h && h < H && 0 <= w && w < W);\n    }\n    bool is_valid(int\
    \ bH, int eH, int bW, int eW) const {\n        return (bH <= h && h < eH && bW\
    \ <= w && w < eW);\n    }\n\n    grid operator+(const grid &other) const {\n \
    \       return {h + other.h, w + other.w};\n    }\n    grid operator*(long long\
    \ x) const { return {h * x, w * x}; }\n\n    grid &operator+=(const grid &other)\
    \ {\n        h += other.h;\n        w += other.w;\n        return *this;\n   \
    \ }\n    grid &operator*=(long long x) {\n        h *= x;\n        w *= x;\n \
    \       return *this;\n    }\n\n    grid operator+() const { return *this; }\n\
    \    grid operator-() const { return {-h, -w}; }\n\n    bool operator<(const grid\
    \ &other) const {\n        if (h == other.h)\n            return w < other.w;\n\
    \        return h < other.h;\n    }\n    bool operator<=(const grid &other) const\
    \ { return !(*this > other); }\n    bool operator>(const grid &other) const {\
    \ return other < *this; }\n    bool operator>=(const grid &other) const { return\
    \ !(*this < other); }\n    bool operator==(const grid &other) const {\n      \
    \  return (h == other.h && w == other.w);\n    }\n    bool operator!=(const grid\
    \ &other) const { return !(*this == other); }\n\n    friend std::istream &operator>>(std::istream\
    \ &is, grid &g) {\n        is >> g.h >> g.w;\n        return is;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const grid &g) {\n        os << g.h\
    \ << \" \" << g.w;\n        return os;\n    }\n};\n\n/*\n * | 8 4 5 |\n * | 3\
    \ 0 1 |\n * | 7 2 6 |\n */\nconst std::vector<grid> around = {{0, 0},  {0, 1},\
    \ {1, 0},   {0, -1}, {-1, 0},\n                                  {-1, 1}, {1,\
    \ 1}, {-1, -1}, {1, -1}};\n"
  code: "#pragma once\n#include <iostream>\n#include <vector>\n\nstruct grid {\n \
    \   long long h, w;\n\n    bool is_valid(int H, int W) const {\n        return\
    \ (0 <= h && h < H && 0 <= w && w < W);\n    }\n    bool is_valid(int bH, int\
    \ eH, int bW, int eW) const {\n        return (bH <= h && h < eH && bW <= w &&\
    \ w < eW);\n    }\n\n    grid operator+(const grid &other) const {\n        return\
    \ {h + other.h, w + other.w};\n    }\n    grid operator*(long long x) const {\
    \ return {h * x, w * x}; }\n\n    grid &operator+=(const grid &other) {\n    \
    \    h += other.h;\n        w += other.w;\n        return *this;\n    }\n    grid\
    \ &operator*=(long long x) {\n        h *= x;\n        w *= x;\n        return\
    \ *this;\n    }\n\n    grid operator+() const { return *this; }\n    grid operator-()\
    \ const { return {-h, -w}; }\n\n    bool operator<(const grid &other) const {\n\
    \        if (h == other.h)\n            return w < other.w;\n        return h\
    \ < other.h;\n    }\n    bool operator<=(const grid &other) const { return !(*this\
    \ > other); }\n    bool operator>(const grid &other) const { return other < *this;\
    \ }\n    bool operator>=(const grid &other) const { return !(*this < other); }\n\
    \    bool operator==(const grid &other) const {\n        return (h == other.h\
    \ && w == other.w);\n    }\n    bool operator!=(const grid &other) const { return\
    \ !(*this == other); }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ grid &g) {\n        is >> g.h >> g.w;\n        return is;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const grid &g) {\n        os << g.h\
    \ << \" \" << g.w;\n        return os;\n    }\n};\n\n/*\n * | 8 4 5 |\n * | 3\
    \ 0 1 |\n * | 7 2 6 |\n */\nconst std::vector<grid> around = {{0, 0},  {0, 1},\
    \ {1, 0},   {0, -1}, {-1, 0},\n                                  {-1, 1}, {1,\
    \ 1}, {-1, -1}, {1, -1}};\n"
  dependsOn: []
  isVerificationFile: false
  path: standard/grid.hpp
  requiredBy: []
  timestamp: '2023-09-02 19:34:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/grid.hpp
layout: document
redirect_from:
- /library/standard/grid.hpp
- /library/standard/grid.hpp.html
title: standard/grid.hpp
---
