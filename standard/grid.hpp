#ifndef GRID_STRUCTURE
#define GRID_STRUCTURE
#include <vector>
#include <ostream>

struct grid{
    long long h, w;
    inline const friend grid operator+(const grid &a, const grid &b) { return {a.h + b.h, a.w + b.w}; }
    inline const friend grid operator-(const grid &a, const grid &b) { return {a.h - b.h, a.w - b.w}; }
    inline const friend grid operator*(const grid &a, long long x) { return {a.h * x, a.w * x}; }
    inline const friend grid operator/(const grid &a, long long x) { return {a.h / x, a.w / x}; }
    inline const friend bool operator==(const grid &a, const grid &b) { return (a.h == b.h && a.w == b.w); }
    inline const friend bool operator!=(const grid &a, const grid &b) { return (a.h != b.h || a.w != b.w); }
    friend std::ostream &operator<<(std::ostream &os, const grid& p) {
        os << p.h << " " << p.w;
        return os;
    }
};

/*
 *------
 *| 7 3 4 |
 *| 2 # 0 |
 *| 6 1 5 |
 *-------
 */
const std::vector<grid> DG = {{ 0, 1},
                              { 1, 0},
                              { 0,-1},
                              {-1, 0},
                              {-1, 1},
                              { 1, 1},
                              {-1,-1},
                              { 1,-1}};

#endif