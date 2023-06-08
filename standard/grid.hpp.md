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
  bundledCode: "#line 1 \"standard/grid.hpp\"\n\n\n#include <vector>\n#include <iostream>\n\
    \nstruct grid{\n    long long h, w;\n    \n    bool is_valid(int H, int W) const{\
    \ return (0 <= h && h < H && 0 <= w && w < W); }\n\n    inline friend grid operator+(const\
    \ grid &a, const grid &b) { return {a.h + b.h, a.w + b.w}; }\n    inline friend\
    \ grid operator-(const grid &a, const grid &b) { return {a.h - b.h, a.w - b.w};\
    \ }\n    inline friend grid operator*(const grid &a, long long x) { return {a.h\
    \ * x, a.w * x}; }\n    inline friend grid operator/(const grid &a, long long\
    \ x) { return {a.h / x, a.w / x}; }\n    inline friend bool operator==(const grid\
    \ &a, const grid &b) { return (a.h == b.h && a.w == b.w); }\n    inline friend\
    \ bool operator!=(const grid &a, const grid &b) { return (a.h != b.h || a.w !=\
    \ b.w); }\n    void operator+=(const grid &a) { h += a.h, w += a.w; }\n    void\
    \ operator-=(const grid &a) { h -= a.h, w -= a.w; }\n    void operator*=(long\
    \ long a) { h *= a, w *= a; }\n    void operator/=(long long a) { h /= a, w /=\
    \ a; }\n    void operator%=(long long a) { h %= a, w %= a; }\n    inline const\
    \ friend grid operator+(const grid &a) { return {a.h, a.w}; }\n    inline const\
    \ friend grid operator-(const grid &a) { return {-a.h, -a.w}; }\n    friend bool\
    \ operator<(const grid &a, const grid &b){\n        if(a.h == b.h) return a.w\
    \ < b.w;\n        return a.h < b.h;\n    }\n    friend bool operator<=(const grid\
    \ &a, const grid &b){\n        if(a.h == b.h) return a.w <= b.w;\n        return\
    \ a.h < b.h;\n    }\n    friend bool operator>(const grid &a, const grid &b){\n\
    \        if(a.h == b.h) return a.w > b.w;\n        return a.h > b.h;\n    }\n\
    \    friend bool operator>=(const grid &a, const grid &b){\n        if(a.h ==\
    \ b.h) return a.w >= b.w;\n        return a.h > b.h;\n    }\n    friend std::istream\
    \ &operator>>(std::istream &is, grid &g){\n        is >> g.h >> g.w;\n       \
    \ return is;\n    }\n    friend std::ostream &operator<<(std::ostream &os, const\
    \ grid& g) {\n        os << g.h << \" \" << g.w;\n        return os;\n    }\n\
    };\n\n/*\n *------\n *| 8 4 5 |\n *| 3 0 1 |\n *| 7 2 6 |\n *-------\n */\nconst\
    \ std::vector<grid> around = {{0, 0}, {0, 1}, {1, 0}, {0,-1}, {-1, 0},\n     \
    \                         {-1, 1}, {1, 1}, {-1, -1}, {1, -1}};\n\n\n\n"
  code: "#ifndef GRID_STRUCTURE\n#define GRID_STRUCTURE\n#include <vector>\n#include\
    \ <iostream>\n\nstruct grid{\n    long long h, w;\n    \n    bool is_valid(int\
    \ H, int W) const{ return (0 <= h && h < H && 0 <= w && w < W); }\n\n    inline\
    \ friend grid operator+(const grid &a, const grid &b) { return {a.h + b.h, a.w\
    \ + b.w}; }\n    inline friend grid operator-(const grid &a, const grid &b) {\
    \ return {a.h - b.h, a.w - b.w}; }\n    inline friend grid operator*(const grid\
    \ &a, long long x) { return {a.h * x, a.w * x}; }\n    inline friend grid operator/(const\
    \ grid &a, long long x) { return {a.h / x, a.w / x}; }\n    inline friend bool\
    \ operator==(const grid &a, const grid &b) { return (a.h == b.h && a.w == b.w);\
    \ }\n    inline friend bool operator!=(const grid &a, const grid &b) { return\
    \ (a.h != b.h || a.w != b.w); }\n    void operator+=(const grid &a) { h += a.h,\
    \ w += a.w; }\n    void operator-=(const grid &a) { h -= a.h, w -= a.w; }\n  \
    \  void operator*=(long long a) { h *= a, w *= a; }\n    void operator/=(long\
    \ long a) { h /= a, w /= a; }\n    void operator%=(long long a) { h %= a, w %=\
    \ a; }\n    inline const friend grid operator+(const grid &a) { return {a.h, a.w};\
    \ }\n    inline const friend grid operator-(const grid &a) { return {-a.h, -a.w};\
    \ }\n    friend bool operator<(const grid &a, const grid &b){\n        if(a.h\
    \ == b.h) return a.w < b.w;\n        return a.h < b.h;\n    }\n    friend bool\
    \ operator<=(const grid &a, const grid &b){\n        if(a.h == b.h) return a.w\
    \ <= b.w;\n        return a.h < b.h;\n    }\n    friend bool operator>(const grid\
    \ &a, const grid &b){\n        if(a.h == b.h) return a.w > b.w;\n        return\
    \ a.h > b.h;\n    }\n    friend bool operator>=(const grid &a, const grid &b){\n\
    \        if(a.h == b.h) return a.w >= b.w;\n        return a.h > b.h;\n    }\n\
    \    friend std::istream &operator>>(std::istream &is, grid &g){\n        is >>\
    \ g.h >> g.w;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const grid& g) {\n        os << g.h << \" \" << g.w;\n        return os;\n\
    \    }\n};\n\n/*\n *------\n *| 8 4 5 |\n *| 3 0 1 |\n *| 7 2 6 |\n *-------\n\
    \ */\nconst std::vector<grid> around = {{0, 0}, {0, 1}, {1, 0}, {0,-1}, {-1, 0},\n\
    \                              {-1, 1}, {1, 1}, {-1, -1}, {1, -1}};\n\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: standard/grid.hpp
  requiredBy: []
  timestamp: '2023-05-25 14:50:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: standard/grid.hpp
layout: document
redirect_from:
- /library/standard/grid.hpp
- /library/standard/grid.hpp.html
title: standard/grid.hpp
---
