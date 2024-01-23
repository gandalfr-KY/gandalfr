#pragma once
#include <deque>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>

#include "atcoder/modint.hpp"

///////////////////// output /////////////////////

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (int i = 0; i < (int)v.size(); i++)
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &st) {
    for (const T &x : st) {
        std::cout << x << " ";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {
    for (const T &x : st) {
        std::cout << x << " ";
    }
    return os;
}
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << p.first << ' ' << p.second;
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, std::queue<T> q) {
    while (!q.empty()) {
        os << q.front();
        q.pop();
    }
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &dq) {
    for (const T &x : dq) {
        std::cout << x << " ";
    }
    return os;
}
template <typename Tp, typename Sequence, typename Compare>
std::ostream &operator<<(std::ostream &os,
                         std::priority_queue<Tp, Sequence, Compare> q) {
    while (!q.empty()) {
        os << q.top();
        q.pop();
    }
    return os;
}

///////////////////// input /////////////////////

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &in : v)
        is >> in;
    return is;
}
template <typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}
