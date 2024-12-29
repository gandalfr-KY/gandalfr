#pragma once

#include <iostream>
#include <vector>

#include "../types.hpp"

namespace gandalfr {

struct Grid {
    i64 h = 0, w = 0;
    Grid() = default;
    Grid(i64 h, i64 w) : h(h), w(w) {}
    Grid(i64 idx) {
        auto [_h, _w] = std::lldiv(idx, Grid::_W);
        h = _h, w = _w;
    }

    i64 getIdx() { return h * _W + w; }
    bool isValid() const { return (0 <= h && h < _H && 0 <= w && w < _W); }

    bool goUp(i64 d = 1) {
        Grid nxt = *this;
        nxt.h -= d;
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goDown(i64 d = 1) {
        Grid nxt = *this;
        nxt.h += d;
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goLeft(i64 d = 1) {
        Grid nxt = *this;
        nxt.w -= d;
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }
    bool goRight(i64 d = 1) {
        Grid nxt = *this;
        nxt.w += d;
        if (nxt.isValid()) {
            *this = nxt;
            return true;
        }
        return false;
    }

    /**
     * 周囲 8 マスの位置を得る
     * 範囲外の座標はユーザが弾く方針で
     * | 7 3 4 |
     * | 2 x 0 |
     * | 6 1 5 |
     */
    std::vector<Grid> getAround(i64 d = 1) {
        std::vector<Grid> around = {{0, d},  {d, 0}, {0, -d},  {-d, 0},
                                    {-d, d}, {d, d}, {-d, -d}, {d, -d}};
        for (auto &g : around) {
            g.h += this->h, g.w += this->w;
        }
        return around;
    }

    std::strong_ordering operator<=>(const Grid &other) const {
        if (auto cmp = h <=> other.h; cmp != 0)
            return cmp;
        return w <=> other.w;
    }

    bool operator==(const Grid &other) const = default;

    Grid& operator+=(const Grid &other) {
        this->h += other.h;
        this->w += other.w;
        return *this;
    }

    Grid operator+(const Grid &other) {
        return (Grid)*this += other;
    }

    friend std::ostream &operator<<(std::ostream &os, const Grid &a) {
        os << a.h << ' ' << a.w;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Grid &a) {
        is >> a.h >> a.w;
        return is;
    }

    static void setSize(i64 H, i64 W) {
        _H = H;
        _W = W;
    }

  private:
    static inline i64 _H = 0, _W = 0;
};
} // namespace gandalfr
