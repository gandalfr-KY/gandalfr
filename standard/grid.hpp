#pragma once
#include <iostream>
#include <vector>

struct grid {

    static int H, W;

    static void set_table_size(int _H, int _W) {
        H = _H, W = _W;
    }

    long long h, w;

    bool is_valid() const {
        return (0 <= h && h < H && 0 <= w && w < W);
    }
    bool is_edge_cell() {
        return (h == 0 || h == H - 1 || w == 0 || w == W - 1);
    }

    grid operator+(const grid &other) const {
        return {h + other.h, w + other.w};
    }
    grid operator*(long long x) const { return {h * x, w * x}; }

    grid &operator+=(const grid &other) {
        h += other.h;
        w += other.w;
        return *this;
    }
    grid &operator*=(long long x) {
        h *= x;
        w *= x;
        return *this;
    }

    grid operator+() const { return *this; }
    grid operator-() const { return {-h, -w}; }

    bool operator<(const grid &other) const {
        if (h == other.h)
            return w < other.w;
        return h < other.h;
    }
    bool operator<=(const grid &other) const { return !(*this > other); }
    bool operator>(const grid &other) const { return other < *this; }
    bool operator>=(const grid &other) const { return !(*this < other); }
    bool operator==(const grid &other) const {
        return (h == other.h && w == other.w);
    }
    bool operator!=(const grid &other) const { return !(*this == other); }

    friend std::istream &operator>>(std::istream &is, grid &g) {
        is >> g.h >> g.w;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const grid &g) {
        os << g.h << " " << g.w;
        return os;
    }

    /*
     * | 8 4 5 |
     * | 3 0 1 |
     * | 7 2 6 |
     */
    static const std::vector<grid> around;

    std::vector<grid> around_cells() {
        std::vector<grid> ret(9);
        for (int i = 0; i < 9; ++i) ret[i] = *this + around[i];
        return ret;
    }

};

const std::vector<grid> grid::around = {{0, 0},  {0, 1},   {1, 0},
                                        {0, -1}, {-1, 0},  {-1, 1},
                                        {1, 1},  {-1, -1}, {1, -1}};
