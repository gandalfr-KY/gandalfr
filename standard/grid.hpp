#ifndef GRID_STRUCTURE
#define GRID_STRUCTURE
#include <vector>
#include <iostream>

struct grid{
    long long h, w;

    bool is_valid(int H, int W){
        return (0 <= h && h < H && 0 <= w && w < W);
    }

    inline const friend grid operator+(const grid &a, const grid &b) { return {a.h + b.h, a.w + b.w}; }
    inline const friend grid operator-(const grid &a, const grid &b) { return {a.h - b.h, a.w - b.w}; }
    inline const friend grid operator*(const grid &a, long long x) { return {a.h * x, a.w * x}; }
    inline const friend grid operator/(const grid &a, long long x) { return {a.h / x, a.w / x}; }
    inline const friend bool operator==(const grid &a, const grid &b) { return (a.h == b.h && a.w == b.w); }
    inline const friend bool operator!=(const grid &a, const grid &b) { return (a.h != b.h || a.w != b.w); }
    friend bool operator<(const grid &a, const grid &b){
        if(a.h == b.h) return a.w < b.w;
        return a.h < b.h;
    }
    friend bool operator<=(const grid &a, const grid &b){
        if(a.h == b.h) return a.w <= b.w;
        return a.h < b.h;
    }
    friend bool operator>(const grid &a, const grid &b){
        if(a.h == b.h) return a.w > b.w;
        return a.h > b.h;
    }
    friend bool operator>=(const grid &a, const grid &b){
        if(a.h == b.h) return a.w >= b.w;
        return a.h > b.h;
    }
    friend std::istream &operator>>(std::istream &is, grid &g){
        is >> g.h >> g.w;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const grid& g) {
        os << g.h << " " << g.w;
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
const std::vector<grid> around = {{ 0, 1}, { 1, 0}, { 0,-1}, {-1, 0},
                              {-1, 1}, { 1, 1}, {-1,-1}, { 1,-1}};


#endif